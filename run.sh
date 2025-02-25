#!/bin/bash
#echo $DISPLAY
#export DISPLAY=:0

# Build the project
mkdir -p build
cd build
cmake ..
make

# Run the executable
./SwayWifiManager
