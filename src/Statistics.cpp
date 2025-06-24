#include "Statistics.h"
using namespace std;

#include <iostream>
#include <iomanip>

void Statistics::log_Flight(const string &vehicle_type, double flight_time, double distance, int passengers)
{
    Stats &s = StatMap[vehicle_type];
    s.total_FlightTime += flight_time;
    s.total_Distance += distance;
    s.total_PassengerMiles += static_cast<int>(distance * passengers);
    s.flight_count++; 
}

void Statistics::log_Charge(const string &vehicle_type, double charge_time)
{
    Stats &s = StatMap[vehicle_type];
    s.total_ChargingTime += charge_time;

    //Assuming multiple charges scenario
    s.charge_count++;
}

void Statistics::log_Faults(const string &vehicle_type)
{
    StatMap[vehicle_type].total_Faults++;
}

void Statistics::print_Stats()
{
    cout << "\n--- Simulation Summary ---\n";

    for(const auto &vehicle: StatMap)
    {
        const string &type = vehicle.first;
        const Stats &s = vehicle.second;

        cout << "\nVehicle Type: " << type << endl;
        cout << "Average Flight Time per Flight = " << s.avg_FlightTime() << endl;
        cout << "Average Distance per Flight    = " << s.avg_Distance()<< endl;
        cout << "Average Charge Time per Session= " << s.avg_ChargeTime() << endl;
        cout << "Total Passenger Miles          = " << s.total_PassengerMiles << endl;
        cout << "Total Faults                   = " << s.total_Faults << endl;
        cout << "Number of Flights              = " << s.flight_count << endl;
        cout << "Number of times charged        = " << s.charge_count << endl;

    }
}