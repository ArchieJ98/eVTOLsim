#include "Simulation.h"
#include "Vehicle_Instance.h"

#include <iostream>
#include <random>
#include <unordered_map>
#include <fstream>

using namespace std;

/**
 * @brief Constructor for Simulation class.
 * 
 * Initializes default simulation parameters and binds the ChargerManager to the shared Statistics.
 */
Simulation::Simulation():chargers(stats, 3),sim_time(3.0), current_time(0.0), time_Increment(0.5){}

void Simulation::vehicle_Init()
{
    //Hardcoding the vehicle types and its configurartions as per the given document
    vehicle_Types.emplace_back(Vehicle("Alpha Company", 120, 320, 0.6, 1.6, 4, 0.25));
    vehicle_Types.emplace_back(Vehicle("Bravo Company", 100, 100, 0.2, 1.5, 5, 0.10));
    vehicle_Types.emplace_back(Vehicle("Charlie Company", 160, 220, 0.8, 2.2, 3, 0.5));
    vehicle_Types.emplace_back(Vehicle("Delta Company", 90, 120, 0.62, 0.8, 2, 0.22));
    vehicle_Types.emplace_back(Vehicle("Echo Company", 30, 150, 0.3, 5.8,  2, 0.61));

    map<string, int> type_count;

    mt19937 gen(random_device{}());
    uniform_int_distribution<>dist(0, vehicle_Types.size() -1);

    // Initializes the 20 vehicles required for simulation
    for(int i=0; i<20; ++i)
    {
        const Vehicle &v= vehicle_Types[dist(gen)];
        vehicles.emplace_back(v);
        type_count[v.name]++;
    }

    // cout << "--Vehicle Type Distribution--" << endl;

    // for(const auto&[type, count]: type_count)
    // {
    //     cout << "Type: " << type << " Count = " << count << endl;
    // }
    // cout << "............................................................." << endl;
}

/**
 * @brief Returns the total duration of the simulation.
 * 
 * @return double Total simulated time in hours.
 */
double Simulation::get_SimTime() const {
    return sim_time;
}

/**
 * @brief Returns the current simulation time.
 * 
 * @return double Current simulation time in hours.
 */
double Simulation::get_CurrentTime() const {
    return current_time;
}

/**
 * @brief Returns the number of vehicle instances in the simulation.
 * 
 * @return int Count of simulated vehicles.
 */

int Simulation::get_VehicleCount() const {
    return vehicles.size();
}

/**
 * @brief Gets a pointer to a specific vehicle instance.
 * 
 * @param index Index of the desired vehicle.
 * @return VehicleInstance* Pointer to the vehicle.
 */
VehicleInstance* Simulation::get_VehiclePointer(int index) {
    if (index >= 0 && index < vehicles.size())
        return &vehicles[index];

    return nullptr;
}

/**
 * @brief Returns reference to the charger manager.
 * 
 * @return ChargerManager& Used to access or test queue state.
 */
ChargerManager& Simulation::get_Chargers() {
    return chargers;
}

/**
 * @brief Runs a partial simulation for a specified duration.
 * 
 * @param duration Time in hours for which the simulation should advance.
 */
void Simulation::run_PartialSimulation(double duration) {
    double end_time = current_time + duration;
    unordered_map<VehicleInstance*, bool> wasCharging;
    ofstream faultLogP("faultP_log.txt");               // Logging faults onto a text file

    chargers.reset();

    while (current_time < end_time) {
        for (auto& v : vehicles) {
            if (!v.charge_depleted()) {
                v.fly(time_Increment);

                bool faultOccurred = v.simulate_Fault(time_Increment);
                if (faultOccurred) {
                    stats.log_Faults(v.vehicle_type.name);
                    v.actualCruiseSpeed *= 0.98;                                    // If fault occurs then reduce cruise speed
                    if (v.actualCruiseSpeed < 0.5 * v.vehicle_type.cruiseSpeed)
                            v.actualCruiseSpeed = 0.5 * v.vehicle_type.cruiseSpeed;
                    faultLogP << "[FAULT] Time: " << current_time                   // Outputs the fault info to the file
                         << " | Vehicle Type: " << v.vehicle_type.name
                         << " | Fault Count: " << v.fault_Count
                         << " | Degradation: " << v.actualCruiseSpeed << "\n";
                }

                // Check if flight just ended
                if (v.charge_depleted() && v.session_FlightTime >= 0.0) 
                {
                    v.finalize_FlightSession();
                    stats.log_Flight(v.vehicle_type.name, v.total_flightTime, v.distanceFlown, v.vehicle_type.passenger_Count);

                    chargers.charge_Request(&v);
                    wasCharging[&v] = true; 
                }
            } else {
                chargers.charge_Request(&v);
                wasCharging[&v] = true;
            }
        }

        chargers.charge_Update(time_Increment);

        for (auto &v : vehicles) {
            if (v.charge_completed()) 
            {
                if (wasCharging[&v]) 
                {
                    stats.log_Charge(v.vehicle_type.name, v.total_chargingTime);
                    v.total_chargingTime = 0.0;
                    wasCharging[&v] = false;
                }
            } else if (!v.charge_depleted()) 
            {
                wasCharging[&v] = false;  // Not yet depleted, no action
            } else 
            {
                wasCharging[&v] = true;  // Mark as actively charging
            }
        }

        current_time += time_Increment;  // Progresses time in simulation by time step
    }
    faultLogP.close();
}

/**
 * @brief Manually initiates a charge request for a vehicle.
 * 
 * @param v Pointer to the vehicle instance requesting charge.
 */
void Simulation::request_ChargingForVehicle(VehicleInstance* v) {
    chargers.charge_Request(v);
}

/**
 * @brief Runs the full simulation loop until the simulation time is reached.
 * 
 * Tracks flight, faults, charging, and logs fault events to file.
 */
void Simulation::run_Sim()
{
    unordered_map<VehicleInstance*, bool> wasCharging;

    chargers.reset();

    ofstream faultLog("fault_log.txt");        // Logs faults onto a text file

    while(current_time < sim_time)
    {
        for(auto &v: vehicles)
        {
            if(!v.charge_depleted())
            {
                v.fly(time_Increment);

                bool faultOccurred = v.simulate_Fault(time_Increment);
                if (faultOccurred)
                {
                    stats.log_Faults(v.vehicle_type.name);
                    v.actualCruiseSpeed *= 0.98;                                        // Reduces cruise speed if fault occurs
                    if (v.actualCruiseSpeed < 0.5 * v.vehicle_type.cruiseSpeed)
                            v.actualCruiseSpeed = 0.5 * v.vehicle_type.cruiseSpeed;
                    faultLog  << "[FAULT] Time: " << current_time                       // Outputs fault info onto a file
                         << " | Vehicle Type: " << v.vehicle_type.name
                         << " | Fault Count: " << v.fault_Count
                         << " | Degradation: " << v.actualCruiseSpeed << "\n";
                }

                if (v.charge_depleted() && v.session_FlightTime >= 0.0) 
                {
                    v.finalize_FlightSession();
                    stats.log_Flight(v.vehicle_type.name, v.total_flightTime, v.distanceFlown, v.vehicle_type.passenger_Count);
                    chargers.charge_Request(&v);
                    wasCharging[&v] = true;
                }

            }
            else{
                chargers.charge_Request(&v); // Ensure request happens if depleted early
                wasCharging[&v] = true;
            }
            chargers.charge_Update(time_Increment);
        }
        

        // Post-charge logging
        for (auto &v : vehicles) {
            if (v.charge_completed()) 
            {
                if (wasCharging[&v]) 
                {
                    //cout << "[INFO] Vehicle fully charged: " << v.vehicle_type.name << endl;
                    stats.log_Charge(v.vehicle_type.name, v.total_chargingTime);
                    v.total_chargingTime = 0.0;
                    wasCharging[&v] = false;
                }
            } else if (!v.charge_depleted()) 
            {
                wasCharging[&v] = false;  // Not yet depleted, no action
            } else 
            {
                wasCharging[&v] = true;  // Mark as actively charging
            }
        }
             


        current_time += time_Increment;  // Progresses time in simulation by time step
    }

    stats.print_Stats();                // Prints simulation statistics onto terminal
    faultLog.close();                   
}