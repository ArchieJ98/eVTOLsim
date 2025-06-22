#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle(string name, double cruiseSpeed, double batteryCapacity, double timeToCharge,
        double energyPerMile, int passengerCount, double faultProbability)
        : name(name),
          cruiseSpeed(cruiseSpeed),
          batteryCapacity(batteryCapacity), 
          timeToCharge(timeToCharge), 
          energyPerMile(energyPerMile), 
          passengerCount(passengerCount), 
          faultProbability(faultProbability) {}


