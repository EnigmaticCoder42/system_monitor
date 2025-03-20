#include "process_monitor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <vector>
#include <algorithm>

std::vector<ProcessInfo> ProcessMonitor::getTopProcesses(int count) {
    std::vector<ProcessInfo> processes;
    DIR* dir = opendir("/proc");
    struct dirent* entry;

    if (dir == nullptr) {
        std::cerr << "Failed to open /proc directory\n";
        return processes;
    }

    while ((entry = readdir(dir)) != nullptr) {
        // Skip non-numeric directories
        if (!isdigit(entry->d_name[0]))
            continue;

        int pid = atoi(entry->d_name);
        std::string statFile = "/proc/" + std::to_string(pid) + "/stat";
        std::ifstream file(statFile);

        if (!file.is_open())
            continue;

        std::string line;
        std::getline(file, line);
        std::istringstream ss(line);
        std::string name;
        long utime, stime, vsize;
        ss >> pid >> name;

        for (int i = 2; i < 14; ++i)
            ss.ignore(256, ' '); // Skip fields
        ss >> utime >> stime;

        for (int i = 16; i < 23; ++i)
            ss.ignore(256, ' '); // Skip more fields
        ss >> vsize;

        double cpuUsage = utime + stime; // CPU time in jiffies
        processes.push_back({pid, name, cpuUsage, vsize / 1024}); // Convert memory to KB
    }

    closedir(dir);

    // Sort by CPU usage
    std::sort(processes.begin(), processes.end(), [](const ProcessInfo& a, const ProcessInfo& b) {
        return a.cpuUsage > b.cpuUsage;
    });

    if (processes.size() > count)
        processes.resize(count);

    return processes;
}