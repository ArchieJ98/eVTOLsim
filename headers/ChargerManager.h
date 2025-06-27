#pragma once

#include <queue>
#include <vector>
#include <unordered_set>

#include "Vehicle_Instance.h"
#include "Statistics.h"

/**
 * @brief Manages the scheduling and allocation of charging resources for electric vehicles.
 * 
 * Handles both active charging and the waiting queue. Vehicles requests
 * a charger through this manager, which decides whether to allow charging immediately
 * or queue the vehicle until a charger is available.
 */
class ChargerManager{
    private:
        int maxChargers;                                        // Maximum number of chargers available
        std::queue<VehicleInstance*> waiting_Queue;             // Queue to store vehicles waiting for a charger
        std::vector<VehicleInstance*> charging_Vehicles;        // List of vehicles currently being charged
        std::unordered_set<VehicleInstance*> known_Vehicles;    // Tracks vehicles being charged or queued

        Statistics& stats;                                      // Reference to the global Statistics object

    public:
         
        ChargerManager(Statistics& statsRef, int chargers_Available = 3);   // Constructor function for class ChargerManager

        void charge_Request(VehicleInstance* v);                            //  Requests charger when battery is depleted
        void charge_Update(double time_increment);                          // Progresses the charging and updates charging and waiting queue
        bool charger_Availability() const;                                  // Checks if a charger is free
        void reset();                                                       // Resets internal queues and charger state.
};