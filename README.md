# N-Queens Solver using Simulated Annealing

A C++ implementation of the classic N-Queens problem solved using the **Simulated Annealing** metaheuristic algorithm.

## Overview

This project tackles the N-Queens puzzle, where the goal is to place N queens on an N×N chessboard such that no two queens threaten each other. The solver uses simulated annealing—a probabilistic optimization technique inspired by metallurgical annealing—to find valid board configurations.

## Key Features

- **Simulated Annealing Algorithm**: Probabilistic approach with temperature-based acceptance of suboptimal solutions
- **Efficient Conflict Detection**: Counts row, column, and diagonal conflicts
- **Configurable Parameters**: 
  - Initial temperature (default: 1000.0)
  - Cooling rate (default: 0.9995)
  - Minimum temperature (default: 0.0001)
  - Maximum iterations (default: 500,000)
- **Multiple Runs**: Executes 30 runs to measure success rate
- **Visual Output**: Prints both array representation and ASCII chessboard

## How It Works

1. **Initialization**: Randomly places queens on the board
2. **Neighbor Generation**: Randomly moves a queen to a new row
3. **Acceptance Criterion**: Accepts better solutions always; accepts worse solutions with probability based on temperature
4. **Temperature Decay**: Gradually lowers temperature to reduce acceptance of worse solutions
5. **Termination**: Stops when temperature reaches minimum or max iterations exceeded

## Build & Run

```bash
mkdir build && cd build
cmake ..
make
./n-queens-solver
```

## Results

Runs 30 independent trials on a 100×100 board and reports:
- Success rate (% of runs achieving 0 conflicts)
- Best overall number of conflicts found
- Visualization of the best solution

## Files

- `baseline.cpp` - Main implementation with NQueens class
- `CMakeLists.txt` - Build configuration