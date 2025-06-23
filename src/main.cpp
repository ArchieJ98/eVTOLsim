#include <iostream>

#include "Simulation.h"

int main()
{
    Simulation sim;
    sim.vehicle_Init();
    sim.run_Sim();

    return 0;
}