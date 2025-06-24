#pragma once
#include <string>
#include <random>

#include "Vehicle.h"

class VehicleInstance{
    

    public:
        Vehicle vehicle_type;
        double currentBattery;           // Current battery level (kWh)
        double total_flightTime;          // Total time spent flying (hours)
        double total_chargingTime;        // Total time spent charging (hours)
        int faultCount;                  // Total faults encountered
        double distanceFlown;            // Total distance flown (miles)
        int passengerMiles;

        VehicleInstance(const Vehicle &vehicleType);

        void fly(double time_increment);
        void charge(double time_increment);
        void simulate_Fault(double time_increment);
        bool charge_depleted() const;                     //check if the battery is depleted
        bool charge_completed() const;                    //checks if the battery is fully charged

    private:
        std::mt19937 gen;
        std::uniform_real_distribution<> dis{0.0, 1.0};

};