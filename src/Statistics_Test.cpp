#include <iostream>

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
        cout << "FAIL" << message << endl; \
    } else { \
        cout << "PASS" << message << endl; \
    } \

/**
 * @brief Verifies all initial values in Stats are zero.
 */
void test_InitialValuesZero() {
    Stats s;
    ASSERT_TRUE(s.total_Distance == 0, "\tTotal distance should be 0 initially");
    ASSERT_TRUE(s.total_FlightTime == 0, "\tTotal flight time should be 0 initially");
    ASSERT_TRUE(s.total_ChargingTime == 0, "\tTotal charge time should be 0 initially");
    ASSERT_TRUE(s.total_PassengerMiles == 0, "\tTotal passenger miles should be 0 initially");
    ASSERT_TRUE(s.total_Faults == 0, "\tTotal faults should be 0 initially");
    ASSERT_TRUE(s.flight_count == 0, "\tFlight count should be 0 initially");
    ASSERT_TRUE(s.charge_count == 0, "\tCharge count should be 0 initially");
}

/**
 * @brief Tests if average flight time is computed correctly.
 */
void test_AverageFlightTime() {
    Stats s;

    s.total_FlightTime = 10.0;
    s.flight_count = 5;

    ASSERT_TRUE(s.avg_FlightTime() == 2.0, "\tAverage flight time should be 2.0");
}

/**
 * @brief Tests if average distance per flight is computed correctly.
 */
void test_AverageDistance() {
    Stats s;

    s.total_Distance = 250;
    s.flight_count = 5;

    ASSERT_TRUE(s.avg_Distance() == 50.0, "\tAverage distance should be 50.0");
}

/**
 * @brief Tests if average charge time per session is computed correctly.
 */
void test_AverageChargeTime() {
    Stats s;

    s.total_ChargingTime = 15;
    s.charge_count = 3;

    ASSERT_TRUE(s.avg_ChargeTime() == 5.0, "\tAverage charge time should be 5.0");
}

/**
 * @brief Ensures that averages return 0.0 when division by zero is avoided.
 */
void test_DivisionByZero_InAverages() {
    Stats s;

    ASSERT_TRUE(s.avg_FlightTime() == 0.0, "\tAverage flight time should be 0 when flight count is 0");
    ASSERT_TRUE(s.avg_Distance() == 0.0, "\tAverage distance should be 0 when flight count is 0");
    ASSERT_TRUE(s.avg_ChargeTime() == 0.0, "\tAverage charge time should be 0 when charge count is 0");
}

/**
 * @brief Verifies that cumulative stats are tracked and aggregated correctly.
 */
void test_AggregatedStats() {
    Stats s;
    // Simulate two flight records
    s.total_FlightTime += 2.5;
    s.total_Distance += 100;
    s.total_PassengerMiles += 400;
    s.total_Faults += 1;
    s.flight_count += 1;

    s.total_FlightTime += 3.5;
    s.total_Distance += 200;
    s.total_PassengerMiles += 800;
    s.total_Faults += 1;
    s.flight_count += 1;

    // Simulate two charge records
    s.total_ChargingTime += 1.0;
    s.charge_count += 1;
    s.total_ChargingTime += 2.0;
    s.charge_count += 1;

    ASSERT_TRUE(s.total_Distance == 300, "\tTotal distance should be 300");
    ASSERT_TRUE(s.total_PassengerMiles == 1200, "\tTotal passenger miles should be 1200");
    ASSERT_TRUE(s.total_FlightTime == 6.0, "\tTotal flight time should be 6.0");
    ASSERT_TRUE(s.total_ChargingTime == 3.0, "\tTotal charge time should be 3.0");
    ASSERT_TRUE(s.total_Faults == 2, "\tTotal faults should be 2");
    ASSERT_TRUE(s.flight_count == 2, "\tFlight count should be 2");
    ASSERT_TRUE(s.charge_count == 2, "\tCharge count should be 2");
}

/**
 * @brief Verifies logging and accessor functions in Statistics.
 */
void test_StatisticsAccessors() {
    Statistics stats;

    stats.log_Charge("TestType", 1.0);
    stats.log_Charge("TestType", 2.0);
    stats.log_Faults("TestType");
    stats.log_Flight("TestType", 3.0, 150.0, 2);  // 300 passenger miles

    ASSERT_TRUE(stats.get_ChargerCount("TestType") == 2, "\tCharge count should be 2 for TestType");
}

/**
 * @brief Tests whether repeated fault logs are counted correctly.
 */
void test_LogFaults_IncrementsProperly() {
    Statistics stats;

    stats.log_Faults("Delta");
    stats.log_Faults("Delta");

    ASSERT_TRUE(stats.get_fault_Count("Delta") == 2, "\tFault count should be 2 for Delta");
}

/**
 * @brief Entry point to run all Statistics related unit tests.
 * 
 * @return int Exit status.
 */
int main() {
    cout << "--- Running Statistics Unit Tests ---" << endl;
    test_InitialValuesZero();
    test_AverageFlightTime();
    test_AverageDistance();
    test_AverageChargeTime();
    test_DivisionByZero_InAverages();
    test_AggregatedStats();
    test_StatisticsAccessors();
    test_LogFaults_IncrementsProperly();
    cout << "--- All Statistics Tests Completed ---" << endl;
    return 0;
}
