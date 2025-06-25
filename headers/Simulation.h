#pragma once

#include <vector>
#include <string>
#include "Vehicle.h"
#include "Vehicle_Instance.h"
#include "Statistics.h"
#include "ChargerManager.h"

class Simulation{
    private:
        std::vector<Vehicle> vehicle_Types;
        std::vector<VehicleInstance> vehicles;
        ChargerManager chargers;
        Statistics stats;

        double sim_time;        //Total time taken to simulate
        double current_time;    //Keeps track of current time during the simulation
        double time_Increment;  //Value by witch time increases in the simulation

    public:
        Simulation();
        void vehicle_Init();   //Load vehicle definitions and create instances
        void run_Sim();        // Begins the Simulation
        
        // Getter methods for testing
        double getSimTime() const;
        double getCurrentTime() const;
        int getVehicleCount() const;
        VehicleInstance* getVehiclePointer(int index);
        ChargerManager& getChargers();
        void runPartialSimulation(double duration);
        void requestChargingForVehicle(VehicleInstance* v);
};