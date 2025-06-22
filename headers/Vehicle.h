#pragma once

#include <string>

class Vehicle{
    public:
        const std::string name;
        double cruiseSpeed;
        double batteryCapacity;
        double timeToCharge;
        double energyPerMile;
        int passengerCount;
        double faultProbability;

        Vehicle(std::string name, double cruiseSpeed, double batteryCapacity, double timeToCharge,
        double energyPerMile, int passengerCount, double faultProbability);
};

