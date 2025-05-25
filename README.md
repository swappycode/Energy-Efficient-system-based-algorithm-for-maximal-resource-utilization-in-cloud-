# Energy-Efficient Task Scheduling Using Whale Optimization Algorithm with DVFS

A metaheuristic optimization approach for minimizing energy consumption in cloud computing environments through intelligent task-to-VM assignment and Dynamic Voltage and Frequency Scaling (DVFS).

## Overview

This project implements the **Whale Optimization Algorithm (WOA)** combined with **Dynamic Voltage and Frequency Scaling (DVFS)** to solve the energy-efficient task scheduling problem in cloud data centers. The algorithm optimally assigns computational tasks to virtual machines while considering power consumption characteristics and CPU utilization patterns.

## Problem Statement

In cloud computing environments, energy consumption is a critical concern due to:
- High operational costs of data centers
- Environmental impact of excessive power usage
- Need for sustainable computing practices

Our solution addresses the **task-to-VM assignment problem** where:
- **Tasks** have varying CPU demands
- **Virtual Machines** have different capacities and power profiles
- **Objective**: Minimize total energy consumption while meeting task requirements

## Algorithm Features

### Whale Optimization Algorithm (WOA)
- **Bio-inspired metaheuristic** based on humpback whale hunting behavior
- **Encircling prey mechanism** for exploitation
- **Bubble-net feeding** for exploration
- **Search for prey** for global exploration

### Dynamic Voltage and Frequency Scaling (DVFS)
- **Adaptive power management** based on CPU utilization
- **Linear power model**: P = P_idle + (P_max - P_idle) × utilization
- **Frequency scaling factors** for energy optimization

## Dataset Description

### Tasks Dataset (`tasks.csv`)
- **100 computational tasks** with varying CPU demands
- CPU requirements ranging from 1 to 10 units
- Represents diverse workload characteristics

### Virtual Machines Dataset (`vms.csv`)
- **20 heterogeneous VMs** with different specifications
- **Attributes**:
  - `CPU_Capacity`: Processing capacity (52-116 units)
  - `Idle_Power`: Power consumption at idle state (80W)
  - `Max_Power`: Maximum power consumption (180W)
  - `DVFS_Factor`: Frequency scaling factor (0.72-1.0)

## How to Run

### Prerequisites
```bash
# Ensure you have a C++17 compatible compiler
g++ --version
```

### Steps

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/woa-dvfs-scheduling.git
   cd woa-dvfs-scheduling
   ```

2. **Compile the program**
   ```bash
   g++ -std=c++17 -O3 -o woa_dvfs woa_dvfs.cpp
   ```

3. **Run the optimization**
   ```bash
   ./woa_dvfs
   ```

### Expected Output
```
Optimal Energy: 1247.56
Assignments: 12 5 8 3 7 15 2 9 11 4 6 13 0 1 14 8 12 7 5 19 ...
```

## File Structure

```
├── woa_dvfs.cpp          # Main WOA-DVFS implementation
├── tasks.csv             # Task dataset with CPU demands
├── vms.csv              # VM specifications and power profiles
├── presentation.pdf      # Algorithm analysis and results
└── README.md            # This file
```

## Algorithm Details

### Energy Model
```cpp
Energy = Σ[P_idle × DVFS_factor + (P_max - P_idle) × DVFS_factor × utilization]
```

### WOA Parameters
- **Population Size**: 40 whales
- **Maximum Iterations**: 200
- **Search Space**: Continuous [0, m-1] where m = number of VMs

### Core Components
1. **Encircling prey** (exploitation)
2. **Spiral bubble-net feeding** (exploitation)
3. **Random search** (exploration)
4. **Constraint handling** for VM capacity limits

## Results

Check the `presentation.pdf` file for detailed performance analysis, comparison with other algorithms, and experimental results.

## Authors

- **Swappycode** - Algorithm implementation and research
- **Arvind singh** - Research and analysis
