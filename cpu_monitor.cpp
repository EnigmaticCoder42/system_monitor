#include "cpu_monitor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

CpuMonitor::CpuMonitor() {
	prevCpuStats = readCpuStats();
}

std::vector<long> CpuMonitor::readCpuStats() {
	std::ifstream file("/proc/stat");
	std::string line;
	std::vector<long> stats;

	if (file.is_open()) {
		std::getline(file, line);
		std::istringstream ss(line);
		std::string cpuLabel;
		ss >> cpuLabel; // Ignore "cpu" label
		
		long value;
		while (ss >> value) {
			stats.push_back(value);
		}
	}

	return stats;
}

double CpuMonitor::getCpuUsage() {
	std::vector<long> newStats = readCpuStats();
	long idle = newStats[3] - prevCpuStats[3]; // Idle time difference
	long total = 0;
	long prevTotal = 0;

	for (size_t i = 0; i < newStats.size(); i++) {
		total += newStats[i];
		prevTotal += prevCpuStats[i];
	}

	double usage = 100.0 * (1.0 - ((double)idle / (total - prevTotal)));
	prevCpuStats = newStats;

	return usage;
}
