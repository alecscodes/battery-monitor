#include "battery_monitor.h"
#include <iostream>
#include <exception>

int main()
{
    try
    {
        BatteryMonitor monitor;
        monitor.monitor();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}