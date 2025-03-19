#include "memory_monitor.h"
#include <fstream>
#include <sstream>

MemoryMonitor::MemoryMonitor() {
}

double MemoryMonitor::getMemoryUsage() {
	std::ifstream file("/proc/meminfo");
	std::string line;
	long totalMem = 0;
	long freeMem = 0;
	long availableMem = 0;

	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::istringstream ss(line);
			std::string key;
			long value;
			ss >> key >> value;

			if (key == "MemTotal:") {
				totalMem = value;
			}
			else if (key == "MemAvailable:") {
				availableMem = value;
				break;
			}
		}
	}

	return 100.0 * (1.0 - ((double)availableMem / totalMem));
}
