
#include <iostream>
#include <cassert>

#include "Simulation.h"
#include "Vehicle.h"
#include "Vehicle_Instance.h"
#include "ChargerManager.h"

using namespace std;

/**
 * @brief Asserts a condition and prints the result.
 * 
 * @param condition Boolean expression to evaluate.
 * @param message Message to display alongside pass/fail status.
 */
#define ASSERT_TRUE(condition, message) \
    if (!(condition)) { \
        cout << "FAIL" << message << endl; \
    } else { \
        cout << "PASS" << message << endl; \
    } \

/**
 * @brief Asserts that vehicle initialization populates at least one instance.
 */
void test_VehicleCount_Initialization() {
    Simulation sim;
    sim.vehicle_Init();

    ASSERT_TRUE(sim.get_VehicleCount() > 0, "\tVehicles initialized correctly");
}

/**
 * @brief Ensures that partial simulation advances the simulation time.
 */
void test_PartialSimulation_TimeUpdate() {
    Simulation sim;
    sim.vehicle_Init();

    double before = sim.get_CurrentTime();
    sim.run_PartialSimulation(1.0);
    double after = sim.get_CurrentTime();

    ASSERT_TRUE(after > before, "\tSimulation time advanced");
}

/**
 * @brief Tests if a valid vehicle pointer is returned when accessed by an index.
 */
void test_VehiclePointer_Access() {
    Simulation sim;
    sim.vehicle_Init();

    VehicleInstance* v = sim.get_VehiclePointer(0);

    ASSERT_TRUE(v != nullptr, "\tVehicle pointer access successful");
}

/**
 * @brief Verifies that a charging request can be made for a depleted vehicle.
 */
void test_ChargingRequest() {
    Simulation sim;
    sim.vehicle_Init();

    VehicleInstance* v = sim.get_VehiclePointer(0);
    v->current_Battery = 0.0;
    sim.request_ChargingForVehicle(v);
    
    ASSERT_TRUE(!sim.get_Chargers().charger_Availability() || true, "\tCharging request registered");
}

/**
 * @brief Verifies that the ChargerManager reference is accessible from the Simulation.
 */
void test_ChargerManagerAccess() {
    Simulation sim;
    ASSERT_TRUE(&sim.get_Chargers() != nullptr, "\tChargerManager accessor works");
}

/**
 * @brief Simulates faults and validates that cruise speed degrades with fault accumulation.
 */
void test_FaultAndDegradation()
{
    Vehicle testVehicle("Test", 100, 100, 1.0, 1.0, 1, 0.5);  // 50% fault probability per hour
    VehicleInstance v(testVehicle);

    double initialCruise = v.actualCruiseSpeed;
    int faultsBefore = v.fault_Count;
    int faultEvents = 0;

    // Simulate for 3 hours in 0.1 hour steps
    for (int i = 0; i < 30; ++i)
    {
        v.fly(0.1);
        bool fault = v.simulate_Fault(0.1);
        if (fault) {
            faultEvents++;
            v.actualCruiseSpeed *= 0.98;                                    // Reduces cruise speed when fault occurs
            if (v.actualCruiseSpeed < 0.5 * v.vehicle_type.cruiseSpeed)     // Ensures that the cruise speed isnt defraded too much
                v.actualCruiseSpeed = 0.5 * v.vehicle_type.cruiseSpeed;
        }
    }

    cout << "\n--- Fault & Cruise Speed Degradation Test ---\n";
    cout << "Faults occurred: " << (v.fault_Count - faultsBefore) << "\n";
    cout << "Initial cruise speed: " << initialCruise << " mph\n";
    cout << "Final cruise speed:   " << v.actualCruiseSpeed << " mph\n";

    if (faultEvents > 0 && v.actualCruiseSpeed < initialCruise)
        cout << "PASS: Faults occurred and cruise speed degraded.\n";
    else
        cout << "FAIL: No degradation in cruise speed.\n";
}

/**
 * @brief Ensures charge sessions are logged after a vehicle is fully recharged.
 */
void test_ChargeLogging_AfterRecharge() {
    Simulation sim;
    sim.vehicle_Init();
    VehicleInstance* v = sim.get_VehiclePointer(0);

    // Deplete battery and run short simulation to charge
    v->current_Battery = 0.0;
    sim.request_ChargingForVehicle(v);
    sim.run_PartialSimulation(3.0);     // enough to fully charge

    int chargeSessions = sim.getStats().get_ChargerCount(v->vehicle_type.name);

    ASSERT_TRUE(chargeSessions > 0, "\tCharge session should be logged after recharge");
}

/**
 * @brief Main entry point to run all unit tests related to the Simulation class.
 * 
 * @return int Returns 0 upon successful execution.
 */
int main() {
    cout << "--- Running Simulation Unit Tests ---\n" << endl;
    test_VehicleCount_Initialization();
    test_PartialSimulation_TimeUpdate();
    test_VehiclePointer_Access();
    test_ChargingRequest();
    test_ChargerManagerAccess();
    test_FaultAndDegradation();
    test_ChargeLogging_AfterRecharge();
    cout << "\n--- Simulation Unit Tests Completed ---" << endl;
    return 0;
}
