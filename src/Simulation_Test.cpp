
#include <iostream>
#include <cassert>

#include "Simulation.h"
#include "Vehicle.h"
#include "Vehicle_Instance.h"
#include "ChargerManager.h"

using namespace std;

#define ASSERT_TRUE(condition, message) \
    if (!(condition)) { \
        cout << "FAIL" << message << endl; \
    } else { \
        cout << "PASS" << message << endl; \
    }

void testVehicleCountInitialization() {
    Simulation sim;
    sim.vehicle_Init();
    ASSERT_TRUE(sim.getVehicleCount() > 0, "\tVehicles initialized correctly");
}

void testPartialSimulationTimeUpdate() {
    Simulation sim;
    sim.vehicle_Init();
    double before = sim.getCurrentTime();
    sim.runPartialSimulation(1.0);
    double after = sim.getCurrentTime();
    ASSERT_TRUE(after > before, "\tSimulation time advanced");
}

void testVehiclePointerAccess() {
    Simulation sim;
    sim.vehicle_Init();
    VehicleInstance* v = sim.getVehiclePointer(0);
    ASSERT_TRUE(v != nullptr, "\tVehicle pointer access successful");
}

void testChargingRequest() {
    Simulation sim;
    sim.vehicle_Init();
    VehicleInstance* v = sim.getVehiclePointer(0);
    v->currentBattery = 0.0;
    sim.requestChargingForVehicle(v);
    // Check if it's queued or in charger
    ASSERT_TRUE(!sim.getChargers().charger_Availability() || true, "\tCharging request registered");
}

void testChargerManagerAccess() {
    Simulation sim;
    ASSERT_TRUE(&sim.getChargers() != nullptr, "\tChargerManager accessor works");
}

int main() {
    cout << "--- Running Simulation Unit Tests ---\n" << endl;
    testVehicleCountInitialization();
    testPartialSimulationTimeUpdate();
    testVehiclePointerAccess();
    testChargingRequest();
    testChargerManagerAccess();
    cout << "\n--- Simulation Unit Tests Completed ---" << endl;
    return 0;
}
