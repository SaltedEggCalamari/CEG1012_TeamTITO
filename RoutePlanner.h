#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

#include "Shuttle.h"
#include "Passenger.h"
#include "ScheduleEntry.h"

#pragma once
class RoutePlanner
{
private:
	vector<ScheduleEntry> ScheduleEntry;
	//idt need schedule entry id?

public:
	void readDataFiles(const std::string& shuttleFile, const std::string& passengerFile);
	void compute_schedule();
	void display_info();
	void saveSchedule(const std::string& outputFile);
};








