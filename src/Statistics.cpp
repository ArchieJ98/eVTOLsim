#include "Statistics.h"

#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Logs flight parameters for a given vehicle type.
 * 
 * @param vehicle_type Name of the vehicle type.
 * @param flight_time Duration of the flight in hours.
 * @param distance Distance flown during the flight in miles.
 * @param passengers Number of passengers on the flight.
 */
void Statistics::log_Flight(const string &vehicle_type, double flight_time, double distance, int passengers)
{
    Stats &s = StatMap[vehicle_type];

    s.total_FlightTime += flight_time;
    s.total_Distance += distance;
    s.total_PassengerMiles += static_cast<int>(distance * passengers);
    s.flight_count++; 
}

/**
 * @brief Logs a charging session for a given vehicle type.
 * 
 * @param vehicle_type Name of the vehicle type.
 * @param charge_time Duration of the charging session in hours.
 */
void Statistics::log_Charge(const string &vehicle_type, double charge_time)
{
    Stats &s = StatMap[vehicle_type];

    s.total_ChargingTime += charge_time;
    s.charge_count++;
}

/**
 * @brief Logs a fault occurrence for a given vehicle type.
 * 
 * @param vehicle_type Name of the vehicle type.
 */
void Statistics::log_Faults(const string &vehicle_type)
{
    StatMap[vehicle_type].total_Faults++;
}

/**
 * @brief Retrieves the number of charging sessions for a specific vehicle type.
 * 
 * @param type Name of the vehicle type.
 * @return int Number of charging sessions recorded, or 0 if type not found.
 */
int Statistics::get_ChargerCount(const std::string& type) const 
{
    auto it = StatMap.find(type);

    if (it != StatMap.end()) 
    {
        return it->second.charge_count;
    }
    return 0;
}

/**
 * @brief Retrieves the total number of faults for a specific vehicle type.
 * 
 * @param type Name of the vehicle type.
 * @return int Total faults recorded, or 0 if type not found.
 */
int Statistics::get_fault_Count(const std::string& type) const 
{
    auto it = StatMap.find(type);

    if (it != StatMap.end()) return it->second.total_Faults;
    return 0;
}

/**
 * @brief Prints a summary of simulation statistics for all vehicle types.
 * 
 */
void Statistics::print_Stats()
{
    cout << "\n--- Simulation Summary ---\n";

    for(const auto &vehicle: StatMap)
    {
        const string &type = vehicle.first;
        const Stats &s = vehicle.second;

        cout << "\nVehicle Type: " << type << endl;
        cout << "Average Flight Time per Flight = " << s.avg_FlightTime() << " hrs"  << endl;
        cout << "Average Distance per Flight    = " << s.avg_Distance() << " miles" << endl;
        cout << "Average Charge Time per Session= " << s.avg_ChargeTime() << " hrs" << endl;
        cout << "Total Passenger Miles          = " << s.total_PassengerMiles << " miles" << endl;
        cout << "Total Faults                   = " << s.total_Faults << endl;
    }
}