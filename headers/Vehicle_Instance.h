#pragma once
#include <string>
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
        void simulateFault(double time_increment);
        bool charge_depleted();                     //check if the battery is depleted
        bool charge_completed();                    //checks if the battery is fully charged

};