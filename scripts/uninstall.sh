#!/bin/bash

# Unload the .plist file
launchctl unload ~/Library/LaunchAgents/com.alecscodes.battery_monitor.plist

# Remove the .plist file
rm -f ~/Library/LaunchAgents/com.alecscodes.battery_monitor.plist

echo "Uninstall complete. The battery monitor will no longer run at startup."