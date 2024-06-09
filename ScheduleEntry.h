#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

#include "Shuttle.h"
#include "Passenger.h"


using namespace std;

#pragma once
class ScheduleEntry
{
private:
	string schedule_entry_id;
	vector<Shuttle> shuttle_list;
	vector<Passenger> passenger_list;

public:
	void add_shuttle(const Shuttle& shuttle);
    void edit_shuttle(const std::string& label, const Shuttle& updatedShuttle);
    void delete_shuttle(const std::string& label);
    void add_passenger(const Passenger& passenger);
    void edit_passenger(const std::string& id, const Passenger& updatedPassenger);
    void delete_passenger(const std::string& id);
    void saveShuttlesToFile(const std::string& filename);
    void savePassengersToFile(const std::string& filename);
};










