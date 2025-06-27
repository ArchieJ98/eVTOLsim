#include <iostream>
#include <cassert>

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
#define ASSERT_TRUE(condition, message)\
        if(!(condition)){\
            cout << "FAIL" << message << endl; \
        } \
        else{ \
            cout << "PASS" << message << endl; \
        } \


/**
 * @brief Tests flying a vehicle with a full battery.
 *
 * Checks whether the battery depletes, distance increases, and passenger miles are logged
 * correctly after one unit of flight.
 */
void test_FlyWithFullBattery() {
    Vehicle v("TestFly", 100.0, 100.0, 1.0, 1.0, 4, 0.0);
    VehicleInstance vi(v);
    double time_increment = 0.5;

    vi.fly(time_increment);
    vi.finalize_FlightSession();
    
    ASSERT_TRUE(vi.current_Battery < v.battery_Capacity, "\tBattery should decrease after flight");
    ASSERT_TRUE(vi.distanceFlown > 0, "\tDistance should increase after flight");
    ASSERT_TRUE(vi.passengerMiles > 0, "\tPassenger miles should increase after flight");
}

/**
 * @brief Tests flying with a partially filled battery.
 *
 * Simulates a flight with insufficient battery for full duration, ensuring partial flight behavior
 * is correctly handled and flight parameters are updated.
 */
void test_FlyWithPartialBattery() {
    Vehicle v("PartialFly", 100.0, 10.0, 1.0, 2.0, 4, 0.0);
    VehicleInstance vi(v);
    double time_increment = 1.0;

    vi.current_Battery = 5.0;  // manually setting low battery
    vi.fly(time_increment);
    vi.finalize_FlightSession();

    ASSERT_TRUE(vi.current_Battery == 0.0, "\tBattery should be depleted after partial flight");  //fabs(vi.current_Battery) < 1e-6
    ASSERT_TRUE(vi.distanceFlown > 0, "\tDistance should increase after partial flight");
    ASSERT_TRUE(vi.passengerMiles > 0, "\tPassenger miles should still be logged");
}

/**
 * @brief Tests if charging from 0 battery level increases battery.
 *
 * Verifies charging logic starts properly when the battery is fully depleted.
 */
void test_ChargeFromZeroBattery() {
    Vehicle v("ChargeTest", 100.0, 50.0, 1.0, 1.0, 4, 0.0);
    VehicleInstance vi(v);
    double time_increment = 0.5;

    vi.current_Battery = 0.0;
    vi.charge(time_increment);

    ASSERT_TRUE(vi.current_Battery > 0.0, "\tBattery should increase after charging from 0");
}

/**
 * @brief Test that battery does not exceed capacity after charging.
 *
 * Ensures the vehicle's battery is capped at its defined maximum capacity.
 */
void test_ChargeStopsAtCapacity() {
    Vehicle v("ChargeLimit", 100.0, 50.0, 1.0, 1.0, 4, 0.0);
    VehicleInstance vi(v);
    double time_increment = 2.0;

    vi.current_Battery = 49.0;   
    vi.charge(time_increment);

    ASSERT_TRUE(vi.current_Battery <= v.battery_Capacity, "\tBattery should not exceed capacity");    //v.battery_Capacity + 1e-6
}

/**
 * @brief Test fault simulation with maximum probability.
 *
 * Simulates faults over multiple steps with 100% fault rate to confirm fault registration.
 */
void test_FaultSimulationHighProbability() {
    Vehicle v("Faulty", 100.0, 100.0, 1.0, 1.0, 4, 1.0);  // 100% fault rate
    VehicleInstance vi(v);
    double time_increment = 1.0;
    int initialFaults = vi.fault_Count;

    for (int i = 0; i < 10; ++i) 
    {
        vi.simulate_Fault(time_increment);
    }

    ASSERT_TRUE(vi.fault_Count > initialFaults, "\tFaults should occur when fault_Probability is 1.0");
}

/**
 * @brief Main function to run all related unit tests.
 *
 * Executes all defined test functions and prints pass/fail messages.
 * 
 * @return int Exit status of the test run.
 */
int main()
{
    cout << "--- Running Unit Tests ---\\n" << endl;
    test_FlyWithFullBattery();
    test_FlyWithPartialBattery();
    test_ChargeFromZeroBattery();
    test_ChargeStopsAtCapacity();
    test_FaultSimulationHighProbability();
    cout << "\\n--- All Tests Completed ---" << endl;
    return 0;
}