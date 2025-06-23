#include <iostream>
#include <cassert>

#include "Vehicle.h"
#include "Vehicle_Instance.h"
#include "ChargerManager.h"

using namespace std;

#define ASSERT_TRUE(condition, message)\
        if(!(condition)){\
            cout << "FAIL" << message << endl; \
        } \
        else{ \
            cout << "PASS" << message << endl; \
        } \

void testFlyWithFullBattery() {
    Vehicle v("TestFly", 100.0, 100.0, 1.0, 1.0, 4, 0.0);
    VehicleInstance vi(v);
    double time_increment = 0.5;

    vi.fly(time_increment);
    
    ASSERT_TRUE(vi.currentBattery < v.batteryCapacity, "\tBattery should decrease after flight");
    ASSERT_TRUE(vi.distanceFlown > 0, "\tDistance should increase after flight");
    ASSERT_TRUE(vi.passengerMiles > 0, "\tPassenger miles should increase after flight");
}

void testFlyWithPartialBattery() {
    Vehicle v("PartialFly", 100.0, 10.0, 1.0, 2.0, 4, 0.0);
    VehicleInstance vi(v);
    vi.currentBattery = 5.0;  // manually setting low battery
    double time_increment = 1.0;
    vi.fly(time_increment);

    ASSERT_TRUE(vi.currentBattery == 0.0, "\tBattery should be depleted after partial flight");
    ASSERT_TRUE(vi.distanceFlown > 0, "\tDistance should increase after partial flight");
    ASSERT_TRUE(vi.passengerMiles > 0, "\tPassenger miles should still be logged");
}

void testChargeFromZeroBattery() {
    Vehicle v("ChargeTest", 100.0, 50.0, 1.0, 1.0, 4, 0.0);
    VehicleInstance vi(v);
    vi.currentBattery = 0.0;
    double time_increment = 0.5;
    vi.charge(time_increment);

    ASSERT_TRUE(vi.currentBattery > 0.0, "\tBattery should increase after charging from 0");
}

void testChargeStopsAtCapacity() {
    Vehicle v("ChargeLimit", 100.0, 50.0, 1.0, 1.0, 4, 0.0);
    VehicleInstance vi(v);
    vi.currentBattery = 49.0;
    double time_increment = 2.0;
    vi.charge(time_increment);

    ASSERT_TRUE(vi.currentBattery >= v.batteryCapacity, "\tBattery should not exceed capacity");
}

void testFaultSimulationHighProbability() {
    Vehicle v("Faulty", 100.0, 100.0, 1.0, 1.0, 4, 1.0);  // 100% fault rate
    VehicleInstance vi(v);
    double time_increment = 1.0;
    int initialFaults = vi.faultCount;
    for (int i = 0; i < 10; ++i) {
        vi.simulateFault(time_increment);
    }

    ASSERT_TRUE(vi.faultCount > initialFaults, "\tFaults should occur when faultProbability is 1.0");
}

int main()
{
    cout << "--- Running Unit Tests ---\\n" << endl;
    testFlyWithFullBattery();
    testFlyWithPartialBattery();
    testChargeFromZeroBattery();
    testChargeStopsAtCapacity();
    testFaultSimulationHighProbability();
    cout << "\\n--- All Tests Completed ---" << endl;
    return 0;
}