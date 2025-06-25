#include "ChargerManager.h"
#include <iomanip>
#include <iostream>
using namespace std;

ChargerManager::ChargerManager(int availableChargers): maxChargers(availableChargers){}

bool ChargerManager::charger_Availability() const
{
    return charging_Vehicles.size() < maxChargers;
}

void ChargerManager::charge_Request(VehicleInstance *v)
{
    if(charger_Availability())
    {
        charging_Vehicles.push_back(v);
    }
    else{
        waiting_Queue.push(v);
    }
}

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
    }

    charging_Vehicles = stillCharging;
    
    while(!waiting_Queue.empty() && charger_Availability())
    {
        VehicleInstance *next = waiting_Queue.front();
        waiting_Queue.pop();
        charging_Vehicles.push_back(next);
    }


    // cout << "--- Charging Vehicles ---" << endl;
    // for (VehicleInstance* v : charging_Vehicles)
    // {
    //     cout << "Vehicle: " << v->vehicle_type.name 
    //          << ", Battery: " << v->currentBattery << "/" 
    //          << v->vehicle_type.batteryCapacity << endl;
    // }
    
}