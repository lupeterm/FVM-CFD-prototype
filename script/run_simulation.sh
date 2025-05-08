#!/bin/bash

# Ensure the script exits on any error
set -e

# Define paths
BUILD_DIR="./build/app"
SCRIPT_DIR="./script"
VALIDATION_DIR="./validation"
CASE_DIR="./cases/heat-conduction/2D-heat-conduction-on-a-10-by-10-mesh"
ASSEMBLY_METHOD="batchedFace"
VENV_DIR="./venv"

# Create a Python virtual environment if it doesn't exist
if [ ! -d "$VENV_DIR" ]; then
  echo "Creating Python virtual environment..."
  python3 -m venv $VENV_DIR
  echo "Virtual environment created at $VENV_DIR"
fi

# Activate the virtual environment
source $VENV_DIR/bin/activate

# Install matplotlib if not already installed
if ! python3 -c "import matplotlib" &> /dev/null; then
  echo "Installing matplotlib in the virtual environment..."
  pip install matplotlib
  echo "matplotlib installed successfully."
fi

# Run the heatConduction executable
echo "Running heat conduction simulation..."
$BUILD_DIR/heatConduction $CASE_DIR $ASSEMBLY_METHOD

# Run the Python plotting script
echo "Generating plot..."
python3 $SCRIPT_DIR/plot_results.py $CASE_DIR/results.txt $VALIDATION_DIR/analytical-sol.txt

echo "Plotting of the simulation results and analytical solution completed successfully."

# Deactivate the virtual environment
deactivate
