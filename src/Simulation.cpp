#include "Simulation.h"

#include <iostream>
#include <random>
using namespace std;

Simulation::Simulation():chargers(3),sim_time(3.0), current_time(0.0), time_Increment(0.5){}

void Simulation::vehicle_Init()
{
    //Hardcoding the vehicle types and its configurartions
    vehicle_Types.push_back(Vehicle("Alpha Company", 120, 320, 0.6, 1.6, 4, 0.25));
    vehicle_Types.push_back(Vehicle("Bravo Company", 100, 100, 0.2, 1.5, 5, 0.10));
    vehicle_Types.push_back(Vehicle("Charlie Company", 160, 220, 0.8, 2.2, 3, 0.5));
    vehicle_Types.push_back(Vehicle("Delta Company", 90, 120, 0.62, 0.8, 2, 0.22));
    vehicle_Types.push_back(Vehicle("Echo Company", 30, 150, 0.3, 5.8,  2, 0.61));

    map<string, int> type_count;

    mt19937 gen(random_device{}());
    uniform_int_distribution<>dist(0, vehicle_Types.size() -1);

    for(int i=0; i<20; ++i)
    {
        const Vehicle &v= vehicle_Types[dist(gen)];
        vehicles.emplace_back(v);
        type_count[v.name]++;
    }

    cout << "--Vehicle Type Distribution--" << endl;

    for(const auto&[type, count]: type_count)
    {
        cout << "Type: " << type << " Count = " << count << endl;
    }
    cout << "............................................................." << endl;
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