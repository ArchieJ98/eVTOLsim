#include <random>
#include <cmath>
#include <iostream>

#include "Vehicle_Instance.h"

using namespace std;

/**
 * @brief Constructs a vehicle instance with initial state based on the vehicle type.
 * 
 * @param vehicleType Reference to the Vehicle definition used to initialize this instance.
 */
VehicleInstance::VehicleInstance(const Vehicle &vehicleType) : vehicle_type(vehicleType),
                                                               current_Battery(vehicleType.battery_Capacity),
                                                               actualCruiseSpeed(vehicleType.cruiseSpeed),
                                                               total_flightTime(0),
                                                               total_chargingTime(0),
                                                               fault_Count(0),
                                                               distanceFlown(0),
                                                               passengerMiles(0),
                                                               gen(random_device{}()) {}

/**
 * @brief Simulates the vehicle flying for a given time increment.
 * 
 * Updates current session flight time, distance, and passenger miles while reducing battery accordingly.
 * If battery is insufficient, performs a partial flight.
 * 
 * @param time_increment Time step in hours to simulate flight.
 */
void VehicleInstance::fly(double time_increment)
{
    double distance = actualCruiseSpeed  * time_increment;   // distance = speed * time

    double battery_used = (distance * vehicle_type.energy_PerMile);   // to calculte amount of battery used

    if(current_Battery >= battery_used)
    {
        current_Battery -= battery_used;
    
        session_FlightTime += time_increment;
        session_Distance += distance;
        session_PassengerMiles += static_cast<int>(vehicle_type.passenger_Count * distance);
    }
    else
    {
        // Partial flight scenario

        double maxDistance = (current_Battery) / vehicle_type.energy_PerMile;
        double remainder_flightTime = maxDistance / actualCruiseSpeed;
        
        session_FlightTime += remainder_flightTime;
        session_Distance += maxDistance;
        session_PassengerMiles += static_cast<int>(vehicle_type.passenger_Count * maxDistance);

        current_Battery = 0; 
    }
}

/**
 * @brief Transfers current session flight parameters to total stats and resets session values.
 */
void VehicleInstance::finalize_FlightSession()
{
    if (session_FlightTime > 0)
    {
        total_flightTime += session_FlightTime;
        distanceFlown += session_Distance;
        passengerMiles += static_cast<int>(session_PassengerMiles);

        // Restting values
        session_FlightTime = 0;
        session_Distance = 0;
        session_PassengerMiles = 0;
    }
}

/**
 * @brief Simulates charging the vehicle for a given time increment.
 * 
 * Adds energy based on charge rate.
 * 
 * @param time_increment Time step in hours to simulate charging.
 */
void VehicleInstance::charge(double time_increment)
{
    double charge_Rate = vehicle_type.battery_Capacity / vehicle_type.timeTo_Charge;
    double battery_added = charge_Rate * time_increment;
    double battery_atArrival = current_Battery;

    current_Battery += battery_added;

    // Caps battery level at maximum
    if(current_Battery > vehicle_type.battery_Capacity)
    {
        current_Battery = vehicle_type.battery_Capacity;
    }

    if (battery_added > 1e-6)
    {
        total_chargingTime += time_increment * ((current_Battery - battery_atArrival) / battery_added);
    }
    
 
}

/**
 * @brief Simulates fault occurance.
 * 
 * @param time_increment Time step in hours to evaluate fault probability.
 * @return true if a fault occurs; false otherwise.
 */
bool VehicleInstance::simulate_Fault(double time_increment)
{
    double fault_Probability  = vehicle_type.fault_Probability * time_increment;

    if(dis(gen) < fault_Probability )
    {
        fault_Count++;

        return true;
    }
    return false;
}

/**
 * @brief Checks if the battery is fully depleted.
 * 
 * @return true if battery is empty; false otherwise.
 */
bool VehicleInstance::charge_depleted() const
{
    return current_Battery <= 0.0;
}

/**
 * @brief Checks if the battery is fully charged.
 * 
 * @return true if battery is at full capacity; false otherwise.
 */
bool VehicleInstance::charge_completed() const
{
    return fabs(current_Battery - vehicle_type.battery_Capacity) < 1e-6;  // Small epsilon tolerance added to account for floating-point precision
}