# eVTOL_Sim

A comprehensive C++ simulation framework for modeling electric vertical takeoff and landing (eVTOL) vehicle operations. This simulation tracks multiple vehicle types, their flight and charging cycles, fault occurrences, and aggregates operational statistics to help analyze eVTOL fleet performance and reliability.

## 🚁 Features

- **Multi-Vehicle Simulation**: Simulates 20 vehicles across 5 different company types
- **Realistic Flight Modeling**: Tracks battery consumption, distance flown, and passenger miles
- **Fault Simulation**: Models equipment failures with performance degradation
- **Charging Management**: Queue-based charging system with configurable charger count
- **Comprehensive Statistics**: Detailed reporting of flight times, distances, charging sessions, and faults
- **Extensible Architecture**: Modular design for easy customization and testing

## 📋 Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- Standard C++ libraries (no external dependencies)

## 🏗️ Building the Project

### Using GCC/Clang (Linux/macOS):
```bash
g++ -std=c++17 -Wall -Wextra -o sim.exe src/*.cpp
```

### Using MSVC (Windows):
```cmd
cl /std:c++17 /EHsc src\*.cpp /Fe:sim.exe
```

### Using CMake (if you prefer):
```bash
mkdir build && cd build
cmake ..
make
```

## 🚀 Usage

### Running the Simulation
```bash
./sim.exe
```

### Running Tests
```bash
# Compile and run individual test files
g++ -std=c++17 -o test_sim src/Simulation_Test.cpp src/*.cpp
./test_sim
```

## 📊 Simulation Components

### Core Classes

| Class | Purpose | Key Features |
|-------|---------|--------------|
| **Vehicle** | Static vehicle configuration | Speed, battery capacity, fault probability |
| **VehicleInstance** | Dynamic vehicle state | Current battery, flight time, faults, distance |
| **ChargerManager** | Charging station management | Queue system, charger allocation |
| **Statistics** | Data aggregation | Flight/charge logging, performance metrics |
| **Simulation** | Main orchestrator | Time progression, vehicle coordination |

### Vehicle Types (Pre-configured)

| Company | Cruise Speed (mph) | Battery (kWh) | Charge Time (hrs) | Energy/Mile (kWh) | Passengers | Fault Rate |
|---------|-------------------|---------------|-------------------|-------------------|------------|------------|
| Alpha | 120 | 320 | 0.6 | 1.6 | 4 | 25% |
| Bravo | 100 | 100 | 0.2 | 1.5 | 5 | 10% |
| Charlie | 160 | 220 | 0.8 | 2.2 | 3 | 50% |
| Delta | 90 | 120 | 0.62 | 0.8 | 2 | 22% |
| Echo | 30 | 150 | 0.3 | 5.8 | 2 | 61% |

## 🔧 How It Works

### 1. Initialization Phase
- Creates 5 vehicle type definitions with different performance characteristics
- Randomly instantiates 20 vehicles from these types
- Initializes charging infrastructure (3 chargers by default)

### 2. Simulation Loop
- **Flight Phase**: Vehicles fly until battery depletion, consuming energy based on speed and distance
- **Fault Detection**: Random faults occur based on probability, degrading cruise speed by 2%
- **Charging Phase**: Depleted vehicles request charging, queuing if necessary
- **Statistics Logging**: All events are logged for analysis

### 3. Output Generation
- Console summary with per-vehicle-type statistics
- Detailed fault log with timestamps and degradation tracking

## 📈 Output Examples

### Console Summary
```
--- Simulation Summary ---

Vehicle Type: Alpha Company
Average Flight Time per Flight = 0.375 hrs
Average Distance per Flight    = 45.0 miles
Average Charge Time per Session= 0.6 hrs
Total Passenger Miles          = 720 miles
Total Faults                   = 3

Vehicle Type: Bravo Company
Average Flight Time per Flight = 0.133 hrs
Average Distance per Flight    = 13.3 miles
Average Charge Time per Session= 0.2 hrs
Total Passenger Miles          = 665 miles
Total Faults                   = 1
...
```

### Fault Log (fault_log.txt)
```
[FAULT] Time: 0.6 | Vehicle Type: Alpha Company | Fault Count: 1 | Degradation: 117.6
[FAULT] Time: 1.2 | Vehicle Type: Echo Company | Fault Count: 3 | Degradation: 28.2358
[FAULT] Time: 1.8 | Vehicle Type: Charlie Company | Fault Count: 2 | Degradation: 153.664
```

## 🧪 Testing

The project includes comprehensive unit tests:

- **Simulation_Test.cpp**: Core simulation functionality
- **Statistics_Test.cpp**: Data aggregation and reporting
- **ChargerManager_Test.cpp**: Charging queue management
- **VehicleInstance_Test.cpp**: Individual vehicle behavior

Run tests to verify functionality:
```bash
g++ -std=c++17 -o test_suite src/*_Test.cpp src/*.cpp
./test_suite
```

## ⚙️ Customization

### Modifying Vehicle Types
Edit `src/Simulation.cpp` in the `vehicle_Init()` method:
```cpp
vehicle_Types.emplace_back(Vehicle("New Company", 150, 400, 0.5, 2.0, 6, 0.15));
```

### Adjusting Simulation Parameters
In `src/Simulation.cpp` constructor:
```cpp
Simulation::Simulation():chargers(stats, 5),sim_time(5.0), current_time(0.0), time_Increment(0.1){}
```

### Changing Charger Count
Modify the ChargerManager constructor call in `Simulation.cpp`:
```cpp
chargers(stats, 10)  // 10 chargers instead of 3
```

## 📁 Project Structure

```
eVTOL_Sim/
├── headers/                 # Header files
│   ├── Simulation.h        # Main simulation orchestrator
│   ├── Vehicle.h           # Vehicle type definitions
│   ├── Vehicle_Instance.h  # Individual vehicle instances
│   ├── ChargerManager.h    # Charging station management
│   └── Statistics.h        # Data aggregation and reporting
├── src/                    # Source files
│   ├── main.cpp           # Entry point
│   ├── Simulation.cpp     # Simulation implementation
│   ├── Vehicle.cpp        # Vehicle type implementation
│   ├── Vehicle_Instance.cpp # Vehicle instance logic
│   ├── ChargerManager.cpp # Charging management
│   ├── Statistics.cpp     # Statistics implementation
│   └── *_Test.cpp         # Unit test files
├── fault_log.txt          # Fault event log
├── sim.exe               # Compiled executable
└── README.md             # This file
```

## 🔍 Key Metrics Tracked

- **Flight Performance**: Time, distance, passenger miles per flight
- **Charging Efficiency**: Time spent charging, queue wait times
- **Reliability**: Fault frequency and performance degradation
- **Fleet Utilization**: Overall system throughput and efficiency

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Add tests for new functionality
4. Ensure all tests pass
5. Submit a pull request

## 📄 License

This project is for educational and research purposes. Feel free to use and modify for academic or commercial applications.

## 🆘 Troubleshooting

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