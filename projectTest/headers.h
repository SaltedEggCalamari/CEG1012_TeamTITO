#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

class Passenger
{
private:
	string passenger_id;
	string destination;
	string time_of_arrival;
    bool assigned;

public:
	Passenger(string p_id, string dest, string toa) {
		passenger_id = p_id;
		destination = dest;
		time_of_arrival = toa;
        assigned = false;
	}

    void get_info(){
        cout << "id: " << passenger_id
            << "\nDestination: " << destination
            << "\nTime of arrival: " << time_of_arrival
            << "\nAssigned?: " << assigned;        
    }

    void set_assigned(bool input){
        if(input == true){
            assigned = true;
        } else{
            assigned = false;
        }
    }
};

class Shuttle
{
private:
	string shuttle_id;
	string charging_point;
	string time_of_arrival;
    bool assigned;

public:
	Shuttle(string s_id, string cp, string toa) {
        shuttle_id = s_id;
		charging_point = cp;
		time_of_arrival = toa;
        assigned = false;
	}

    void get_info(){
        cout << "id: " << shuttle_id
            << "\nCharging point: " << charging_point
            << "\nTime of arrival: " << time_of_arrival
            << "\nAssigned?: " << assigned;        
    }

    void set_assigned(bool input);

};

class ScheduleEntry
{
private:
	string schedule_entry_id;
	Shuttle shuttle;
	Passenger passenger;

public:
	void set_pair(const Shuttle& shuttle);
    void edit_pair(const string& label, const Shuttle& updatedShuttle);
    void delete_pair(const string& label);
    void get_pair();
};

class RoutePlanner
{
private:
	vector<ScheduleEntry> ScheduleEntry;

public:
	void import_schedule(const string& shuttleFile, const string& passengerFile);
	void compute_schedule();
	void get_schedule();
	void export_schedule(const string& outputFile);
};
















