#pragma once

#include <map>
#include <string>

/**
 * @brief Aggregates statistics for a single vehicle type.
 * 
 * This struct accumulates total values like flight time, distance, charge time,
 * faults, and passenger miles. It also provides utility functions to compute
 * averages based on flight and charge counts.
 */
struct Stats{
    double total_FlightTime = 0.0;      // Cumulative flight time
    double total_Distance = 0.0;        // Cumulative distance flown
    double total_ChargingTime = 0.0;    // Cumulative charging time
    int total_Faults = 0;               // Total number of faults that has occured
    int total_PassengerMiles = 0;       // Total Passenger Miles accumulated
    int flight_count = 0;               // Number of flights logged
    int charge_count = 0;               // Number of charges logged

    /**
     * @brief Computes the average flight time per flight.
     * @return Average flight time, or 0 if no flights were logged.
     */
    double avg_FlightTime() const{
        return flight_count ? total_FlightTime/flight_count : 0;
    }

    /**
     * @brief Computes the average distance flown per flight.
     * @return Average flight distance, or 0 if no flights were logged.
     */
    double avg_Distance()const{
        return flight_count ? total_Distance/flight_count : 0;
    }

    /**
     * @brief Computes the average charging time per charge.
     * @return Average charging time, or 0 if no charges were logged.
     */
    double avg_ChargeTime()const{
        return charge_count ? total_ChargingTime/charge_count : 0;
    }
};

/**
 * @brief Tracks and logs operational statistics for all vehicle types.
 * 
 * This class maintains a mapping from vehicle type names to their
 * corresponding Stats structures. It supports logging of flight sessions,
 * charge events, and faults, and provides a summary printout for analysis.
 */
class Statistics{
    public:
        std::map<std::string, Stats> StatMap;                                                                   // Map from vehicle type to its corresponding statistics

        void log_Flight(const std::string &vehicle_type, double flight_time, double distance, int passengers);  // Logs flight data for a specific vehicle type.
        void log_Charge(const std::string &vehicle_type, double charge_time);                                   // Logs a charging event for a specific vehicle type.
        void log_Faults(const std::string &vehicle_type);                                                       // Logs a fault occurrence for a specific vehicle type.
        
        int get_ChargerCount(const std::string& type) const;                                                      // Getter function to get charger count for specific vehicle
        int get_fault_Count(const std::string& type) const;                                                       // Getter function to get fault count

        void print_Stats();                                                                                     // Prints statistics summary for all vehicle types.
};