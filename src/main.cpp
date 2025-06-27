#include <iostream>

#include "Simulation.h"

/**
 * @brief Main function to initialize vehicles and run the complete simulation.
 * 
 * Initializes the simulation environment, loads vehicle types and instances,
 * and runs the simulation loop until completion.
 * 
 * @return int Returns 0 upon successful execution.
 */
int main()
{
    Simulation sim;

    sim.vehicle_Init();     // Initializes vehicle instances with given configurations
    sim.run_Sim();          // Runs the simulation for 3 hours

    return 0;
}