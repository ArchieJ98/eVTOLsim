# eVTOL_Simulation

eVTOL_sim functions as a simulation tool designed to evaluate the behaviour of electric vertical takeoff and landing otherwise known as eVTOL vehicles. The simulator allows users to analyze eVTOLs through evaluations of flight dynamics together with control systems and electrical performance.

## Features

- **Language**: The tool operates through a complete implementation of C++ that guarantees high efficiency along with cross-platform compatibility
- **Modular setup**: Enables straightforward incorporation of flight dynamics and additional company types
- **Multi-Vehicle Simulation**: Simulates 20 vehicles across 5 different company types
- **Realistic Flight Modeling**: Tracks battery consumption, distance flown, and passenger miles
- **Fault Simulation**: Simulates faults to mimic real time scenarios with performance degradation
- **Charging Management**: Queue-based charging system with configurable charger count
- **Comprehensive Statistics**: Detailed logging of flight times, distances, charging sessions, and faults
- **Extensible Architecture**: Easily customizable design for unit testing

## Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- Standard C++ libraries (no external dependencies)

## Building the Project

### Using GCC/Clang (Linux/macOS):
```bash
g++ -std=c++17 -Wall -Wextra -I headers -o sim src/*.cpp
```

### Using Git clone (Windows CMD):
```cmd
git clone https://github.com/ArchieJ98/eVTOLsim.git
cd eVTOLsim
```

```cmd
mkdir build
cd build
g++ ..\src\*.cpp -I ..\headers -o sim.exe -std=c++17
```

## Usage

### Running the Simulation
For Linux:

```bash
./sim
```
For Windows:

```cmd
sim.exe
```

### Running Tests
```cmd
# Compile and run individual test files
g++ -std=c++17 -I headers test/Simulation_Test.cpp src/Vehicle.cpp src/ChargerManager.cpp src/Vehicle_Instance.cpp src/Simulation.cpp src/Statistics.cpp -o test_sim
./test_sim
```
### On Windows:
```cmd
sim.exe
```
### On Linux:

```bash
./sim

## Simulation Components

### Core Classes

|| Class             | Purpose                  | Key Features                            |
|------------------|--------------------------|------------------------------------------|
| **Vehicle**       | Static vehicle config    | Speed, battery capacity, fault probability |
| **VehicleInstance** | Dynamic vehicle state | Current battery, flight time, faults, distance |
| **ChargerManager** | Charging mgmt           | Queue system, charger allocation         |
| **Statistics**    | Data aggregation         | Flight/charge logging, performance metrics |
| **Simulation**    | Main orchestrator        | Time progression, vehicle coordination   |


### Vehicle Types (Pre-configured)

| Company | Cruise Speed (mph) | Battery (kWh) | Charge Time (hrs) | Energy/Mile (kWh) | Passengers | Fault Rate |
|---------|--------------------|---------------|-------------------|-------------------|------------|------------|
| Alpha   | 120                | 320           | 0.6               | 1.6               | 4          | 25%        |
| Bravo   | 100                | 100           | 0.2               | 1.5               | 5          | 10%        |
| Charlie | 160                | 220           | 0.8               | 2.2               | 3          | 50%        |
| Delta   | 90                 | 120           | 0.62              | 0.8               | 2          | 22%        |
| Echo    | 30                 | 150           | 0.3               | 5.8               | 2          | 61%        |


## How It Works

### 1. Initialization Phase
- Creates 5 vehicle type definitions with different performance characteristics
- Randomly instantiates 20 vehicles from these types
- Initializes charging infrastructure (3 chargers by default)

### 2. Simulation Loop
- **Flight Phase**: Vehicles fly until battery depletion, consuming energy based on speed and distance
- **Fault Detection**: Random faults occur based on probability, degrading cruise speed by a fraction
- **Charging Phase**: Depleted vehicles request charging, queued if necessary
- **Statistics Logging**: All events are logged for analysis

### 3. Output Generation
- Console summary with per vehicle type statistics
- Detailed re-writable fault log with timestamps and degradation tracking to a text file

## Output Examples

### Console Summary
```
--- Simulation Summary ---

Vehicle Type: Alpha Company
Average Flight Time per Flight = 1.67347 hrs
Average Distance per Flight    = 200 miles
Average Charge Time per Session= 0.55 hrs
Total Passenger Miles          = 5600 miles
Total Faults                   = 5

Vehicle Type: Bravo Company
Average Flight Time per Flight = 1.33333 hrs
Average Distance per Flight    = 133.333 miles
Average Charge Time per Session= 0.35 hrs
Total Passenger Miles          = 9995 miles
Total Faults                   = 0

Vehicle Type: Charlie Company
Average Flight Time per Flight = 1.26069 hrs
Average Distance per Flight    = 200 miles
Average Charge Time per Session= 0.635 hrs
Total Passenger Miles          = 7200 miles
Total Faults                   = 5

Vehicle Type: Delta Company
Average Flight Time per Flight = 1.68027 hrs
Average Distance per Flight    = 150 miles
Average Charge Time per Session= 0.56 hrs
Total Passenger Miles          = 300 miles
Total Faults                   = 2

Vehicle Type: Echo Company
Average Flight Time per Flight = 1.75366 hrs
Average Distance per Flight    = 51.7241 miles
Average Charge Time per Session= 0.4 hrs
Total Passenger Miles          = 927 miles
Total Faults                   = 6
```

### Fault Log (fault_log.txt)
```
[FAULT] Time: 0 | Vehicle Type: Alpha Company | Fault Count: 1 | Degradation: 117.6
[FAULT] Time: 0 | Vehicle Type: Charlie Company | Fault Count: 1 | Degradation: 156.8
[FAULT] Time: 0 | Vehicle Type: Alpha Company | Fault Count: 1 | Degradation: 117.6
[FAULT] Time: 0 | Vehicle Type: Echo Company | Fault Count: 1 | Degradation: 29.4
[FAULT] Time: 0 | Vehicle Type: Charlie Company | Fault Count: 1 | Degradation: 156.8
[FAULT] Time: 0.5 | Vehicle Type: Delta Company | Fault Count: 1 | Degradation: 88.2
[FAULT] Time: 0.5 | Vehicle Type: Echo Company | Fault Count: 1 | Degradation: 29.4
[FAULT] Time: 0.5 | Vehicle Type: Echo Company | Fault Count: 1 | Degradation: 29.4
[FAULT] Time: 1 | Vehicle Type: Charlie Company | Fault Count: 1 | Degradation: 156.8
[FAULT] Time: 1 | Vehicle Type: Echo Company | Fault Count: 2 | Degradation: 28.812
[FAULT] Time: 1 | Vehicle Type: Echo Company | Fault Count: 2 | Degradation: 28.812
[FAULT] Time: 1 | Vehicle Type: Charlie Company | Fault Count: 2 | Degradation: 153.664
[FAULT] Time: 1.5 | Vehicle Type: Alpha Company | Fault Count: 1 | Degradation: 117.6
[FAULT] Time: 1.5 | Vehicle Type: Echo Company | Fault Count: 3 | Degradation: 28.2358
[FAULT] Time: 2 | Vehicle Type: Alpha Company | Fault Count: 1 | Degradation: 117.6
[FAULT] Time: 2.5 | Vehicle Type: Delta Company | Fault Count: 2 | Degradation: 86.436
[FAULT] Time: 2.5 | Vehicle Type: Charlie Company | Fault Count: 1 | Degradation: 156.8
[FAULT] Time: 2.5 | Vehicle Type: Alpha Company | Fault Count: 1 | Degradation: 117.6
```

## Testing

The project includes comprehensive unit tests:

- **Simulation_Test.cpp**: Tests core simulation functionality
- **Statistics_Test.cpp**: Tests vehicle data aggregation and logging
- **ChargerManager_Test.cpp**: Tests charging queue management and updation
- **VehicleInstance_Test.cpp**: Tests individual vehicle behavior

## Customization

### Modifying Vehicle Types
Edit `src/Simulation.cpp` in the `vehicle_Init()` method:
```cpp
vehicle_Types.emplace_back(Vehicle("New Company", 150, 400, 0.5, 2.0, 6, 0.15));
```

### Adjusting Simulation Parameters
In `src/Simulation.cpp` constructor:
```cpp
Simulation::Simulation():chargers(stats, 5),sim_time(4.0), current_time(0.0), time_Increment(0.1){}
```

### Changing Charger Count
Modify the ChargerManager constructor call in `Simulation.cpp`:
```cpp
chargers(stats, 10)  // 10 chargers instead of 3
```

## 📁 Project Structure

```
eVTOL_Sim/
├── headers/                     # Header files
│   ├── Simulation.h             # Main simulation orchestrator
│   ├── Vehicle.h                # Vehicle type definitions
│   ├── Vehicle_Instance.h       # Individual vehicle instances
│   ├── ChargerManager.h         # Charging station management
│   └── Statistics.h             # Data aggregation and reporting
├── src/                         # Source files
│   ├── main.cpp                 # Entry point
│   ├── Simulation.cpp           # Simulation implementation
│   ├── Vehicle.cpp              # Vehicle type implementation
│   ├── Vehicle_Instance.cpp     # Vehicle instance logic
│   ├── ChargerManager.cpp       # Charging management
│   └── Statistics.cpp           # Statistics implementation
├── test/                        # Unit test files
│   ├── VehicleInstance_Test.cpp
│   ├── ChargerManager_Test.cpp
│   ├── Statistics_Test.cpp
│   └── Simulation_Test.cpp
├── CMakeLists.txt               # Build configuration
├── fault_log.txt                # Fault event log
├── sim.exe                      # Compiled executable (Windows)
└── README.md                    # Project documentation

```

## Key Metrics Tracked

- **Flight Performance**: Time, distance, passenger miles per flight
- **Charging Efficiency**: Time spent charging, queue wait times
- **Reliability**: Fault frequency and performance degradation
- **Fleet Utilization**: Overall system throughput and efficiency

## Assumptions

1. Each vehicle starts the simulation with a fully-charged battery.
2. Each vehicle instantaneously reaches Cruise Speed.
3. Each vehicle is airborne for the full use of the battery, and is immediately in line for the charger 
   after running out of battery power.
4. Vehicles follow a fly -> charge -> fly pattern until the simulation time ends.
5. Each fault triggered will impact the cruising speed by a small fraction to show the impact of faults in the system

## TODO: Future Optimizations and Enhancements

1. Introduce Multithreading: Parallelizing vehicle flight and charging logic using threads, synchronizing access to shared resources like charger queue and stats using mutexes.
2. Dynamic configuration: Reading the vehicle configurations from a config file or input via command line.
3. Advanced Fault Handling: Introduce fault levels to show the level of impact of a fault on the system and customized faults and degradation for each parameter.
4. Time Scheduler: Using schedulers to model events like flight, fault occurrence, queue promotion, and charging.
5. Advanced logging: Data can be put into JSON packets and posted to a server where all faults and analysis are logged.
6. Add battery degradation: Battery degrades over time as all batteries do which will impact charge and ultimately flight performance.

## Troubleshooting

### Common Issues

**Compilation Errors:**
- Ensure C++17 support is enabled (`-std=c++17`)
- Check that all source files are included in compilation

**Runtime Issues:**
- Verify `fault_log.txt` has write permissions
- Check console output for error messages

**Test Failures:**
- Run individual test files to isolate issues
- Check that random number generation is working properly

For additional support, please check the test files for usage examples or create an issue with specific error details.