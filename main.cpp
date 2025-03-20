#include <ncurses.h>
#include <thread>
#include <chrono>
#include "cpu_monitor.h"
#include "memory_monitor.h"
#include "process_monitor.h"

void displaySystemMonitor() {
	initscr();                // Initialize ncurses
	noecho();                 // Disable echoing of characters
	curs_set(0);              // Hide cursor
	nodelay(stdscr, TRUE);    // Non-blocking input
	keypad(stdscr, TRUE);     // Enable keyboard input

	CpuMonitor cpuMonitor;
	MemoryMonitor memoryMonitor;
	ProcessMonitor processMonitor;

	while (true) {
		clear(); // Clear screen before updating

		// Display CPU and Memory Usage
		mvprintw(1, 2, "===== System Monitor =====");
		mvprintw(3, 2, "CPU Usage:     %.2f%%", cpuMonitor.getCpuUsage());
		mvprintw(4, 2, "Memory Usage:  %.2f%%", memoryMonitor.getMemoryUsage());

		// Display Top Processes
		mvprintw(6, 2, "Top Processes:");
		mvprintw(7, 2, "PID   NAME        CPU USAGE   MEMORY (KB)");

		std::vector<ProcessInfo> topProcesses = processMonitor.getTopProcesses();
		int row = 8;
		
		for (const auto& p : topProcesses) {
			mvprintw(row++, 2, "%d   %-10s   %.2f      %ld", p.pid, p.name.c_str(), p.cpuUsage, p.memoryUsage);
		}

		mvprintw(row + 2, 2, "Press 'q' to quit.");

		refresh();
		
		// Handle user input
		int ch = getch();
		if (ch == 'q' || ch == 'Q') {
			break; // Exit on 'Q'
		}

		std::this_thread::sleep_for(std::chrono::seconds(1)); // Refresh rate
	}

	endwin(); // Restore terminal settings
}

int main() {
	displaySystemMonitor();
	return 0;
}
