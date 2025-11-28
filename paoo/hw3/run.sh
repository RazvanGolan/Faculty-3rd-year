#!/bin/bash

# Get the directory where the script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Create build directory inside the script directory
mkdir -p "$SCRIPT_DIR/build"

# Navigate to build directory
cd "$SCRIPT_DIR/build"

# Run CMake pointing to the script directory (where CMakeLists.txt is)
cmake ..

# Build the project
make

# Run the executable
echo "Running homework3..."
./homework3
