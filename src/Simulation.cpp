#include "Simulation.h"

#include <iostream>
#include <random>
using namespace std;

Simulation::Simulation():chargers(3),sim_time(3.0), current_time(0.0), time_Increment(0.1){}

void Simulation::vehicle_Init()
{
    //Hardcoding the vehicle types and its configurartions
    vehicle_Types.push_back(Vehicle("JobyS4", 100, 80, 1.5, 0.8, 4, 0.01));
    vehicle_Types.push_back(Vehicle("CityAirbus", 90, 70, 1.2, 1.0, 4, 0.02));
    vehicle_Types.push_back(Vehicle("ArcherMaker", 110, 85, 1.8, 0.75, 5, 0.015));
    vehicle_Types.push_back(Vehicle("LiliumJet",   120, 75, 1.6, 0.9,  6, 0.018));
    vehicle_Types.push_back(Vehicle("WiskCora",     80, 65, 1.3, 1.1,  2, 0.025));

    mt19937 gen(random_device{}());
    uniform_int_distribution<>dist(0, vehicle_Types.size() -1);

    for(int i=0; i<20; ++i)
    {
        const Vehicle &v= vehicle_Types[dist(gen)];
        vehicles.emplace_back(v);
    }
}

void Simulation::run_Sim()
{
    while(current_time < sim_time)
    {
        for(auto &v: vehicles)
        {
            if(!v.charge_depleted())
            {
                v.fly(time_Increment);
                v.simulateFault(time_Increment);
                stats.logFlight(v.vehicle_type.name, time_Increment, v.vehicle_type.cruiseSpeed * time_Increment, v.vehicle_type.passengerCount);

            }
            else{
                chargers.charge_Request(&v);
            }
        }
        chargers.charge_Update(time_Increment);

        for(auto &v:vehicles)
        {
            if(!v.charge_depleted() && !v.charge_completed())
            {
                stats.logCharge(v.vehicle_type.name, time_Increment);
            }
        }
        current_time += time_Increment;
    }

    stats.printStats();
}