#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <string>
#include <chrono>

class BatteryMonitor
{
private:
    static constexpr int LOW_BATTERY_THRESHOLD = 40;
    static constexpr int HIGH_BATTERY_THRESHOLD = 60;
    static constexpr int CHECK_INTERVAL_SECONDS = 300;
    static constexpr int MAX_NOTIFICATIONS = 2;

    bool notificationsEnabled = true;
    int notificationCount = 0;

    std::string executeCommand(const std::string &cmd) const;
    void sendNotification(const std::string &message) const;
    bool isCharging() const;
    int getBatteryLevel() const;

    bool shouldNotify(int batteryLevel, bool charging) const;
    void resetNotificationState(int batteryLevel);

public:
    void monitor();
};

#endif // BATTERY_MONITOR_H