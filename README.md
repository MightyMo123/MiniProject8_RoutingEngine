# Mini Project 8 - Network Routing Engine

## Overview
This project implements a routing engine that reads a network from a text file, constructs a directed graph, and finds a bandwidth-feasible path from a source node to a destination node using Depth-First Search (DFS). The system ensures safe memory management using smart pointers.

## Objective
The goal of this project is to:
- Parse a network from a file
- Store it as a graph in memory
- Traverse the graph using DFS
- Find valid paths based on bandwidth constraints
- Demonstrate safe and efficient memory usage

## Data Format
The input file (`network.txt`) contains directed edges in the format:

u v bandwidth

Example:
0 1 100
0 2 50
1 2 30
1 3 80
2 3 60
2 4 40
3 4 90
3 5 70
4 5 120

## Features
- Graph construction using adjacency lists
- File parsing for dynamic network input
- DFS-based path finding
- Bandwidth constraint filtering
- Clean and safe memory management using `unique_ptr`
- Clear console output of graph and results

## Implementation Details

### Graph Structure
- Each node contains:
  - An ID
  - A list of outgoing edges
- Each edge contains:
  - Destination node
  - Bandwidth value

### Memory Management
- Nodes are stored using `unique_ptr` to ensure:
  - Automatic cleanup
  - No memory leaks
  - Clear ownership
- Edges are stored by value since they are small and efficient to copy

### DFS Algorithm
- Uses recursion to explore paths
- Tracks visited nodes to avoid cycles
- Only follows edges that satisfy the minimum bandwidth requirement
- Backtracks when a path is not valid

## How to Compile and Run

### Compile
```bash
g++ -Wall -Wextra -fsanitize=address -g -std=c++17 main.cpp -o main
