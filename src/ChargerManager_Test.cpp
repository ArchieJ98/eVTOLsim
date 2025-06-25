#include <iostream>
#include <vector>
#include <cassert>

#include "Vehicle.h"
#include "Vehicle_Instance.h"
#include "ChargerManager.h"

using namespace std;

#define ASSERT_TRUE(condition, message) \
    if (!(condition)) { \
        cout << "FAIL " << message << endl; \
    } else { \
        cout << "PASS " << message << endl; \
    }

void testAddToChargingWhenAvailable() {
    ChargerManager manager(2);
    Vehicle v("TestVehicle", 100, 100, 1, 1, 4, 0.0);
    VehicleInstance* v1 = new VehicleInstance(v);
    manager.charge_Request(v1);
    manager.charge_Update(1.0);
    ASSERT_TRUE(manager.charger_Availability() == true, "\tCharger should still have capacity");
    delete v1;
}

void testAddToQueueWhenFull() {
    ChargerManager manager(1);
    Vehicle v("TestVehicle", 100, 100, 1, 1, 4, 0.0);
    VehicleInstance* v1 = new VehicleInstance(v);
    VehicleInstance* v2 = new VehicleInstance(v);
    manager.charge_Request(v1);
    manager.charge_Request(v2);
    manager.charge_Update(1.0);
    ASSERT_TRUE(manager.charger_Availability() == false, "\tSecond vehicle should wait in queue");
    delete v1;
    delete v2;
}

void testPromotionFromQueue() {
    ChargerManager manager(1);
    Vehicle v("TestVehicle", 100, 100, 0.1, 1, 4, 0.0);
    VehicleInstance* v1 = new VehicleInstance(v);
    VehicleInstance* v2 = new VehicleInstance(v);
    manager.charge_Request(v1);
    manager.charge_Request(v2);

    manager.charge_Update(0.1);
    // v1 should be charged and removed, v2 promoted
    ASSERT_TRUE(manager.charger_Availability() == false, "\tSecond vehicle should be promoted after first finishes");
    delete v1;
    delete v2;
}

void testNoOverfillBeyondCapacity() {
    ChargerManager manager(2);
    Vehicle v("TestVehicle", 100, 100, 1, 1, 4, 0.0);
    VehicleInstance* v1 = new VehicleInstance(v);
    VehicleInstance* v2 = new VehicleInstance(v);
    VehicleInstance* v3 = new VehicleInstance(v);
    manager.charge_Request(v1);
    manager.charge_Request(v2);
    manager.charge_Request(v3);  // should go to queue
    ASSERT_TRUE(manager.charger_Availability() == false, "\tOnly 2 vehicles can charge at a time");
    delete v1;
    delete v2;
    delete v3;
}

int main() {
    cout << "--- ChargerManager Unit Tests ---\n" << endl;
    testAddToChargingWhenAvailable();
    testAddToQueueWhenFull();
    testPromotionFromQueue();
    testNoOverfillBeyondCapacity();
    cout << "\n--- All ChargerManager Tests Completed ---" << endl;
    return 0;
}
