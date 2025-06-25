#include <iostream>
#include "Statistics.h"
using namespace std;

#define ASSERT_TRUE(condition, message) \
    if (!(condition)) { \
        cout << "FAIL" << message << endl; \
    } else { \
        cout << "PASS" << message << endl; \
    } \

void testInitialValuesZero() {
    Stats s;
    ASSERT_TRUE(s.total_Distance == 0, "\tTotal distance should be 0 initially");
    ASSERT_TRUE(s.total_FlightTime == 0, "\tTotal flight time should be 0 initially");
    ASSERT_TRUE(s.total_ChargingTime == 0, "\tTotal charge time should be 0 initially");
    ASSERT_TRUE(s.total_PassengerMiles == 0, "\tTotal passenger miles should be 0 initially");
    ASSERT_TRUE(s.total_Faults == 0, "\tTotal faults should be 0 initially");
    ASSERT_TRUE(s.flight_count == 0, "\tFlight count should be 0 initially");
    ASSERT_TRUE(s.charge_count == 0, "\tCharge count should be 0 initially");
}

void testAverageFlightTime() {
    Stats s;
    s.total_FlightTime = 10.0;
    s.flight_count = 5;
    ASSERT_TRUE(s.avg_FlightTime() == 2.0, "\tAverage flight time should be 2.0");
}

void testAverageDistance() {
    Stats s;
    s.total_Distance = 250;
    s.flight_count = 5;
    ASSERT_TRUE(s.avg_Distance() == 50.0, "\tAverage distance should be 50.0");
}

void testAverageChargeTime() {
    Stats s;
    s.total_ChargingTime = 15;
    s.charge_count = 3;
    ASSERT_TRUE(s.avg_ChargeTime() == 5.0, "\tAverage charge time should be 5.0");
}

void testDivisionByZeroInAverages() {
    Stats s;
    ASSERT_TRUE(s.avg_FlightTime() == 0.0, "\tAverage flight time should be 0 when flight count is 0");
    ASSERT_TRUE(s.avg_Distance() == 0.0, "\tAverage distance should be 0 when flight count is 0");
    ASSERT_TRUE(s.avg_ChargeTime() == 0.0, "\tAverage charge time should be 0 when charge count is 0");
}

void testAggregatedStats() {
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

int main() {
    cout << "--- Running Statistics Unit Tests ---" << endl;
    testInitialValuesZero();
    testAverageFlightTime();
    testAverageDistance();
    testAverageChargeTime();
    testDivisionByZeroInAverages();
    testAggregatedStats();
    cout << "--- All Statistics Tests Completed ---" << endl;
    return 0;
}
