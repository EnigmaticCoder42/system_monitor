#include <iostream>
#include <thread>
#include <chrono>
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "process_monitor.h"

void displaySystemMonitor() {
	CpuMonitor cpuMonitor;
	MemoryMonitor memoryMonitor;
	ProcessMonitor processMonitor;

	while (true) {
		double cpuUsage = cpuMonitor.getCpuUsage();
		double memUsage = memoryMonitor.getMemoryUsage();
		std::vector<ProcessInfo> topProcesses = processMonitor.getTopProcesses();

		// Clears terminal for a live update effect
		system("clear");

		std::cout << "===== System Monitor =====\n";
		std::cout << "CPU Usage: " << cpuUsage << "%\n";
		std::cout << "Memory Usage: " << memUsage << "%\n\n";

		std::cout << "Top Processes:\n";
		std::cout << "PID\tNAME\tCPU USAGE\tMEMORY (KB)\n";
		for (const auto& p : topProcesses) {
			std::cout << p.pid << "\t" << p.name << "\t" << p.cpuUsage << "\t" << p.memoryUsage << "\n";
		}

		std::cout << "\nPress Cmd + C to terminate\n";

		// Refresh every second
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

int main() {
	displaySystemMonitor();
	return 0;
}
