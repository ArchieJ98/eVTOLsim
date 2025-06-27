#include "Vehicle.h"
using namespace std;

/**
 * @brief Constructs a Vehicle with the given configuration parameters.
 * 
 * @param name             Name of the vehicle type
 * @param cruiseSpeed      Cruise speed in miles per hour
 * @param battery_Capacity  Total battery capacity in KWh
 * @param timeTo_Charge     Time required to fully charge the battery in hours
 * @param energy_PerMile    Energy consumed per mile in KWh
 * @param passenger_Count   Number of passengers carried per flight
 * @param fault_Probability Probability of encountering a fault per hour of flight
 */
Vehicle::Vehicle(string name, double cruiseSpeed, double battery_Capacity, double timeTo_Charge,
        double energy_PerMile, int passenger_Count, double fault_Probability)
        : name(name),
          cruiseSpeed(cruiseSpeed),
          battery_Capacity(battery_Capacity), 
          timeTo_Charge(timeTo_Charge), 
          energy_PerMile(energy_PerMile), 
          passenger_Count(passenger_Count), 
          fault_Probability(fault_Probability) {}


