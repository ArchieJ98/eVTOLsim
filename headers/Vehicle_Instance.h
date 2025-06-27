#pragma once
#include <string>
#include <random>

#include "Vehicle.h"

/**
 * @brief Defines a single instance of a vehicle operating in the simulation.
 * 
 * Manages the runtime state of an individual vehicle, including
 * battery level, total flight/charging time, fault generation, and distance flown.
 * Random number generation is used to simulate faults.
 */
class VehicleInstance{
    

    public:
        Vehicle vehicle_type;              // Composite configuration of vehicle company
        double current_Battery;           // Current battery level(kWh)
        double total_flightTime;          // Total time spent flying(hours)
        double total_chargingTime;        // Total time spent charging(hours)
        int fault_Count;                  // Total faults encountered
        double distanceFlown;            // Total distance flown(miles)
        int passengerMiles;              // Total calculated Passenger Miles
        double actualCruiseSpeed;       // Updated cruise speed if fault occurs
        double session_FlightTime;       // Flight time for the current time increment session 
        double session_Distance;         // Distance flown in the current time increment session
        int session_PassengerMiles;      // Calculated Passenger Miles for current time-increment session

        VehicleInstance(const Vehicle &vehicleType);     // Constructor to initialize a vehicle instance from a vehicle type

        void fly(double time_increment);                   // Simulates flight and updates session parameters
        void charge(double time_increment);                // Simulates battery charging
        bool simulate_Fault(double time_increment);        // Simulates a fault and increments fault count if occured
        bool charge_depleted() const;                      // Checks if the battery is depleted
        bool charge_completed() const;                     // Checks if the battery is fully charged
        void finalize_FlightSession();                     // Updates total parameters with the current session parameters

    private:
        std::mt19937 gen;                                   // Random number gernerator engine for fault simulation
        std::uniform_real_distribution<> dis{0.0, 1.0};     // Distribution for fault probability

};