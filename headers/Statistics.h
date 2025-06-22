#pragma once

#include <map>
#include <string>

//Structure to hold each vehicle types stats
struct Stats{
    double total_FlightTime = 0.0;
    double total_Distance = 0.0;
    double total_ChargingTime = 0.0;
    int total_Faults = 0;
    int total_PassengerMiles = 0;
    int flight_count = 0;
    int charge_count = 0;
};

class Statistics{
    public:
        std::map<std::string, Stats> StatMap;

        void logFlight(const std::string &vehicle_type, double flight_time, double distance, int passengers);
        void logCharge(const std::string &vehicle_type, double charge_time);
        void logFaults(const std::string &vehicle_type);
        
        //Stats check
        void printStats();
};