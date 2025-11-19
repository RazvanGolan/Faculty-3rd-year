#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Run CMake
cmake ../

# Build the project
make

# Run the executable
echo "Running homework2..."
./homework2
