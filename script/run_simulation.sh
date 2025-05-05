#!/bin/bash

# Ensure the script exits on any error
set -e

# Define paths
BUILD_DIR="./build/app"
SCRIPT_DIR="./script"
VALIDATION_DIR="./validation"
CASE_DIR="./cases/heat-conduction/2D-heat-conduction-on-a-10-by-10-mesh"
ASSEMBLY_METHOD="face"

# Run the heatConduction executable
echo "Running heat conduction simulation..."
$BUILD_DIR/heatConduction $CASE_DIR $ASSEMBLY_METHOD

# Generate the analytical solution
# echo "Calculating analytical solution..."
# python3 $SCRIPT_DIR/analytical_sol.py

# Run the Python plotting script
echo "Generating plot..."
python3 $SCRIPT_DIR/plot_results.py $CASE_DIR/results.txt $VALIDATION_DIR/analytical-sol.txt

echo "Plotting of the simulation results and analytical solution completed successfully."
