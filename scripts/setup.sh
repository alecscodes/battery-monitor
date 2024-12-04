#!/bin/bash

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Check if make is installed
if ! command_exists make; then
    echo "Error: make is not installed. Please install make and try again."
    exit 1
fi

# Get the absolute path to the root directory of the project
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Build the project
mkdir -p "$ROOT_DIR/build"
cd "$ROOT_DIR/build"
cmake ..
make

# Replace the placeholder in the .plist file with the actual path to the built executable
sed "s|__EXECUTABLE_PATH__|$ROOT_DIR/build|g" "$ROOT_DIR/scripts/com.alecscodes.battery_monitor.plist" > ~/Library/LaunchAgents/com.alecscodes.battery_monitor.plist

# Load the .plist file
launchctl load ~/Library/LaunchAgents/com.alecscodes.battery_monitor.plist

echo "Setup complete. The battery monitor will run at startup."