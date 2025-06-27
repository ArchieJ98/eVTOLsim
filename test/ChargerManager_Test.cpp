#include <iostream>
#include <vector>
#include <cassert>

#include "Vehicle.h"
#include "Vehicle_Instance.h"
#include "ChargerManager.h"
#include "Statistics.h"

using namespace std;

/**
 * @brief Asserts a condition and prints the result.
 * 
 * @param condition Boolean expression to evaluate.
 * @param message Message to display alongside pass/fail status.
 */
#define ASSERT_TRUE(condition, message) \
    if (!(condition)) { \
        cout << "FAIL " << message << endl; \
    } else { \
        cout << "PASS " << message << endl; \
    } \

/**
 * @brief Tests adding a vehicle to the charger when one is available.
 * 
 * Ensures that a vehicle is added directly to the charger without waiting in queue.
 */
void test_AddToCharging_WhenAvailable() {
    Statistics stats;
    ChargerManager manager(stats, 2);
    Vehicle v("TestVehicle", 100, 100, 1, 1, 4, 0.0);
    VehicleInstance* v1 = new VehicleInstance(v);

    manager.charge_Request(v1);
    manager.charge_Update(1.0);

    ASSERT_TRUE(manager.charger_Availability() == true, "\tCharger should still have capacity");

    delete v1;
}

/**
 * @brief Tests adding a vehicle to the queue when chargers are full.
 * 
 * Ensures that the second vehicle waits in the queue if all chargers are occupied.
 */
void test_AddToQueue_WhenFull() {
    Statistics stats;
    ChargerManager manager(stats, 1);
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

/**
 * @brief Tests automatic promotion from queue after a charger is freed.
 * 
 * Confirms that a vehicle in the queue is moved to an available charger once a slot opens up.
 */
void test_PromotionFrom_Queue() {
    Statistics stats;
    ChargerManager manager(stats, 1);
    Vehicle v("TestVehicle", 100, 100, 0.1, 1, 4, 0.0);
    VehicleInstance* v1 = new VehicleInstance(v);
    VehicleInstance* v2 = new VehicleInstance(v);

    manager.charge_Request(v1);
    manager.charge_Request(v2);
    manager.charge_Update(0.1);
    
    ASSERT_TRUE(manager.charger_Availability() == false, "\tSecond vehicle should be promoted after first finishes");

    delete v1;
    delete v2;
}

/**
 * @brief Tests that charging slots are not overfilled.
 * 
 * Verifies that the number of charging vehicles never exceeds the max charger count.
 */
void test_NoOverfill_BeyondCapacity() {
    Statistics stats;
    ChargerManager manager(stats, 3);
    Vehicle v("TestVehicle", 100, 100, 1, 1, 4, 0.0);
    VehicleInstance* v1 = new VehicleInstance(v);
    VehicleInstance* v2 = new VehicleInstance(v);
    VehicleInstance* v3 = new VehicleInstance(v);
    VehicleInstance* v4 = new VehicleInstance(v);

    manager.charge_Request(v1);
    manager.charge_Request(v2);
    manager.charge_Request(v3);  
    manager.charge_Request(v4); // should go to queue

    ASSERT_TRUE(manager.charger_Availability() == false, "\tOnly 3 vehicles can charge at a time");
    delete v1;
    delete v2;
    delete v3;
    delete v4;
}

/**
 * @brief Tests that duplicate charge requests are ignored.
 * 
 * Ensures that the same vehicle is not added multiple times to the charging list or queue.
 */
void test_DuplicateChargeRequest_Ignored() {
    Statistics stats;
    ChargerManager manager(stats, 2);
    Vehicle v("DupVehicle", 100, 100, 1, 1, 4, 0.0);
    VehicleInstance* vi = new VehicleInstance(v);

    manager.charge_Request(vi);
    manager.charge_Request(vi); // Second request should be ignored
    manager.charge_Update(1.0);

    ASSERT_TRUE(stats.get_ChargerCount("DupVehicle") <= 1, "\tDuplicate charge request should be ignored");

    delete vi;
}

/**
 * @brief Main function to run all ChargerManager related unit tests.
 * 
 * Executes all defined tests and prints their results to the console.
 * 
 * @return int Exit status.
 */
int main() {
    cout << "--- ChargerManager Unit Tests ---\n" << endl;
    test_AddToCharging_WhenAvailable();
    test_AddToQueue_WhenFull();
    test_PromotionFrom_Queue();
    test_NoOverfill_BeyondCapacity();
    test_DuplicateChargeRequest_Ignored();
    cout << "\n--- All ChargerManager Tests Completed ---" << endl;
    return 0;
}
