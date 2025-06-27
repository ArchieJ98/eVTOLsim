#pragma once

#include <vector>
#include <string>

#include "Vehicle.h"
#include "Vehicle_Instance.h"
#include "Statistics.h"
#include "ChargerManager.h"

/**
 * @brief Class which facilitates simulation
 * 
 * The Simulation class manages vehicle initialization, simulates flight and charging behavior,
 * tracks time progression, and aggregates statistics. It also interacts with the ChargerManager
 * to manage charging queues and vehicle states.
 */
class Simulation{
    private:
        std::vector<Vehicle> vehicle_Types;     // Definitions of different vehicle companies or types
        std::vector<VehicleInstance> vehicles;  // All instances of vehicles present in the simulation
        ChargerManager chargers;                // Manages charger availability and queueing
        Statistics stats;                       // Tracks and aggregates simulation statistics

        double sim_time;                        // Simulation duration
        double current_time;                    // Keeps track of current time during the simulation
        double time_Increment;                  // Value by witch time increases in the simulation

    public:
        Simulation();                           // Constructor function with default parameters
        void vehicle_Init();                    // Initializes vehicle definitions and creates corresponding instances
        void run_Sim();                         // Runs the full simulation
        
        // Getter methods for testing
        double get_SimTime() const;                              // Getter function to get simulation time
        double get_CurrentTime() const;                          // Getter function to get current time in simulation
        int get_VehicleCount() const;                            // Getter function to get vehicle count
        VehicleInstance* get_VehiclePointer(int index);          // Getter function to get the vehicle pointer at index
        ChargerManager& get_Chargers();                          // Getter functions to get the charger states
        const Statistics& getStats() const { return stats; }    // Getter function to get stats of a particular vehicle

        void run_PartialSimulation(double duration);             // Runs simulation for a partial time
        void request_ChargingForVehicle(VehicleInstance* v);     // Requests charging for a specific vehicle
        
};