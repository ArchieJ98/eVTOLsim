#pragma once

#include <string>

/**
 * @brief Defines the static configuration of a vehicle type.
 * 
 * This class holds configuration data such as speed, battery specs, energy use,
 * and fault probability, which are shared across all instances of a given type.
 */

class Vehicle{
    public:
        const std::string name;     // Name of the vehicle company
        double cruiseSpeed;         // Vehicle cruise speed in miles per hour
        double battery_Capacity;     // Battery capacity in KWh
        double timeTo_Charge;        // Time taken to fully charge the battery in hours
        double energy_PerMile;       // Energy consumption per mile in kWh
        int passenger_Count;         // Number of passengers carried per trip
        double fault_Probability;    // Probability of a fault occuring
        
        Vehicle(std::string name, double cruiseSpeed, double battery_Capacity, double timeTo_Charge, double energy_PerMile, int passenger_Count, double fault_Probability);   // Constructor to initialize vehicle properties
};

