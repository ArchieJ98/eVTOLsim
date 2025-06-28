#include "ChargerManager.h"

#include <iomanip>
#include <iostream>

using namespace std;

/**
 * @brief Constructs a ChargerManager with maximum chargers available and a reference to the stats logger.
 * 
 * @param statsRef Reference to the Statistics object for logging charging sessions.
 * @param chargers_Available Number of available charging stations (default maximum = 3).
 */
ChargerManager::ChargerManager(Statistics& statsRef, int chargers_Available)
    : stats(statsRef), maxChargers(chargers_Available) {}

/**
 * @brief Checks if a charger is available.
 * 
 * @return true if available, false otherwise.
 */
bool ChargerManager::charger_Availability() const
{
    return charging_Vehicles.size() < maxChargers;
}

/**
 * @brief Handles a vehicle’s request to charge.
 * 
 * If a charger is available, the vehicle is added to the active chargers list;
 * otherwise, it is queued.
 * 
 * @param v Pointer to the VehicleInstance requesting a charge.
 */
void ChargerManager::charge_Request(VehicleInstance *v)
{
    // Prevent duplicates
    if (known_Vehicles.count(v) > 0)
        return;

    known_Vehicles.insert(v);

    if(charger_Availability())
    {
        charging_Vehicles.push_back(v);
    }
    else{
        waiting_Queue.push(v);
    }
}

/**
 * @brief Updates the state of all charging vehicles for a given time step and progresses charging.
 * 
 * Vehicles that finish charging are removed and logged and vehicles from the queue
 * are promoted if slots become available.
 * 
 * @param time_increment Time in hours to simulate charging progression.
 */
void ChargerManager::charge_Update(double time_increment)
{
    vector<VehicleInstance*> stillCharging;

    for(VehicleInstance *v: charging_Vehicles)
    {
        v->charge(time_increment);

        if(!v->charge_completed())
        {
            stillCharging.push_back(v);
        }
        else{
            stats.log_Charge(v->vehicle_type.name, time_increment);
            known_Vehicles.erase(v);                                   // If finished charging then remove from tracking set
        }
    }

    charging_Vehicles = stillCharging;                                 // Updates the vector for vehicles still needing charging
    
    while(!waiting_Queue.empty() && charger_Availability())
    {
        VehicleInstance *next = waiting_Queue.front();
        waiting_Queue.pop();
        charging_Vehicles.push_back(next);
    }
    
}

/**
 * @brief Resets the charger manager by clearing the queue, charging list, and known vehicle tracker.
 */
void ChargerManager::reset() 
{
    charging_Vehicles.clear();
    while (!waiting_Queue.empty()) waiting_Queue.pop();
    known_Vehicles.clear();
}