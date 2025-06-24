#include <random>
#include <cmath>

#include "Vehicle_Instance.h"
using namespace std;

VehicleInstance::VehicleInstance(const Vehicle &vehicleType) : vehicle_type(vehicleType),
                                                               currentBattery(vehicleType.batteryCapacity),
                                                               total_flightTime(0),
                                                               total_chargingTime(0),
                                                               faultCount(0),
                                                               distanceFlown(0),
                                                               passengerMiles(0),
                                                               gen(std::random_device{}()) {}

void VehicleInstance::fly(double time_increment)
{
    double distance = vehicle_type.cruiseSpeed * time_increment;   //distance = speed * time

    double battery_used = distance * vehicle_type.energyPerMile;   //to calculte amopunt of battery used

    if(currentBattery >= battery_used)
    {
        currentBattery -= battery_used;
    
        total_flightTime += time_increment;
        distanceFlown += distance;
        passengerMiles += static_cast<int>(vehicle_type.passengerCount * distance); 
    }
    else
    {
        //partial flight scenario

        double maxDistance = currentBattery / vehicle_type.energyPerMile;
        double remainder_flightTime = maxDistance / vehicle_type.cruiseSpeed;

        total_flightTime += remainder_flightTime;
        distanceFlown += maxDistance;
        passengerMiles += static_cast<int>(vehicle_type.passengerCount * maxDistance);
        currentBattery = 0; 
    }
}

void VehicleInstance::charge(double time_increment)
{
    double chaargeRate = vehicle_type.batteryCapacity / vehicle_type.timeToCharge;
    double battery_added = chaargeRate * time_increment;

    double battery_atArrival = currentBattery;

    currentBattery += battery_added;
    if(currentBattery > vehicle_type.batteryCapacity)
    {
        currentBattery = vehicle_type.batteryCapacity;
    }

    total_chargingTime += time_increment * ((currentBattery - battery_atArrival) / battery_added); 
}

void VehicleInstance::simulate_Fault(double time_increment)
{
    double faultProbability  = vehicle_type.faultProbability * time_increment;

    if(dis(gen) < faultProbability )
    {
        faultCount++;
    }
}

bool VehicleInstance::charge_depleted() const
{
    return currentBattery <= 0.0;
}

bool VehicleInstance::charge_completed() const
{
    return currentBattery >= vehicle_type.batteryCapacity;
}