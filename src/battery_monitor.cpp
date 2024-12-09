#include "battery_monitor.h"
#include <iostream>
#include <thread>
#include <cstdlib>
#include <stdexcept>

std::string BatteryMonitor::executeCommand(const std::string &cmd) const
{
    std::string result;
    char buffer[128];

    FILE *pipe = popen(cmd.c_str(), "r");
    if (!pipe)
    {
        throw std::runtime_error("Command execution failed");
    }

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

void BatteryMonitor::sendNotification(const std::string &message) const
{
    std::string cmd = "osascript -e 'display notification \"" +
                      message + "\" with title \"Battery Monitor\"'";
    system(cmd.c_str());
}

bool BatteryMonitor::isCharging() const
{
    try
    {
        return executeCommand("pmset -g batt | grep 'AC Power'").find("AC Power") != std::string::npos;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error checking charging status: " << e.what() << std::endl;
        return false;
    }
}

int BatteryMonitor::getBatteryLevel() const
{
    try
    {
        std::string result = executeCommand("pmset -g batt | grep -o '[0-9]*%' | tr -d '%'");
        return std::stoi(result);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading battery level: " << e.what() << std::endl;
        return -1;
    }
}

bool BatteryMonitor::shouldNotify(int batteryLevel, bool charging) const
{
    if (!notificationsEnabled)
        return false;
    return (batteryLevel <= LOW_BATTERY_THRESHOLD && !charging) ||
           (batteryLevel >= HIGH_BATTERY_THRESHOLD && charging);
}

void BatteryMonitor::resetNotificationState(int batteryLevel)
{
    if (batteryLevel > LOW_BATTERY_THRESHOLD && batteryLevel < HIGH_BATTERY_THRESHOLD)
    {
        notificationsEnabled = true;
        notificationCount = 0;
    }
}

void BatteryMonitor::monitor()
{
    while (true)
    {
        try
        {
            int batteryLevel = getBatteryLevel();
            bool charging = isCharging();

            resetNotificationState(batteryLevel);

            if (shouldNotify(batteryLevel, charging))
            {
                if (notificationCount < MAX_NOTIFICATIONS)
                {
                    sendNotification("Battery level is at " + std::to_string(batteryLevel) +
                                     "%. " + (charging ? "You can disconnect" : "Please connect") +
                                     " the charger.");
                    notificationCount++;
                }
                else
                {
                    notificationsEnabled = false;
                }
            }

            std::this_thread::sleep_for(std::chrono::seconds(CHECK_INTERVAL_SECONDS));
        }
        catch (const std::exception &e)
        {
            std::cerr << "Monitor error: " << e.what() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(60)); // Shorter retry on error
        }
    }
}

constexpr int BatteryMonitor::CHECK_INTERVAL_SECONDS;