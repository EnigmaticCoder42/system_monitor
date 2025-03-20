#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H

#include <vector>
#include <string>

struct ProcessInfo {
    int pid;
    std::string name;
    double cpuUsage;
    long memoryUsage;
};

class ProcessMonitor {
    public:
    std::vector<ProcessInfo> getTopProcesses(int count = 5);
};

#endif