#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

#include <vector>
#include <string>

class CpuMonitor {
	public:
		CpuMonitor();
		double getCpuUsage(); // Returns CPU usage in percentage
	
	private:
		std::vector<long> prevCpuStats;
		std::vector<long> readCpuStats();
};

#endif

