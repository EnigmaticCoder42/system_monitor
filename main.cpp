#include <iostream>
#include <thread>
#include <chrono>
#include "cpu_monitor.h"
#include "memory_monitor.h"

int main() {
	CpuMonitor cpuMonitor;
	MemoryMonitor memoryMonitor;

	while (true) {
		double cpuUsage = cpuMonitor.getCpuUsage();
		double memUsage = memoryMonitor.getMemoryUsage();

		system("clear"); // Clears terminal for a live update effect
		std::cout << "===== System Monitor =====\n";
		std::cout << "CPU Usage: " << cpuUsage << "%\n";
		std::cout << "Memory Usage: " << memUsage << "%\n";
		std::cout << "\nPress Cmd + C to terminate\n";

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
