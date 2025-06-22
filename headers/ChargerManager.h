#pragma once

#include <queue>
#include <vector>

#include "Vehicle_Instance.h"

class ChargerManager{
    private:
        int maxChargers;
        std::queue<VehicleInstance*> waiting_Queue;
        std::vector<VehicleInstance*> charging_Vehicles;

    public:
        ChargerManager(int chargers_Available =3);

        void charge_Request(VehicleInstance* v);    //Requests when battery is depleted
        void charge_Update(double time_increment);  //Progresses the charging
        bool charger_Availability() const;          //Checks if a charger is free

};