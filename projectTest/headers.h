#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

/* Forward Declaration of friend operator overload functions */
class Passenger;
class Shuttle;
bool operator==(const Shuttle& lhs, const Passenger& rhs);
bool operator<(const Shuttle& lhs, const Passenger& rhs);
bool operator>(const Shuttle& lhs, const Passenger& rhs);


/* Class Declarations */
class Passenger
{
private:
	string passenger_id;
	string destination;
	string time_of_arrival;
    bool assigned;

public:
	Passenger(){
		passenger_id = "";
		destination = "";
		time_of_arrival = "";
		assigned = false;
	}
	Passenger(string p_id, string dest, string toa) {
		passenger_id = p_id;
		destination = dest;
		time_of_arrival = toa;
        assigned = false;
	}
    void get_info();
    void set_assigned(bool input);
	std::string get_time_of_arrival() const { return time_of_arrival; }
	std::string passenger_id() const { return passenger_id; }
	std::string get_destination() const { return destination; }
	
	friend bool operator==(const Shuttle& lhs, const Passenger& rhs);
	friend bool operator<(const Shuttle& lhs, const Passenger& rhs);
	friend bool operator>(const Shuttle& lhs, const Passenger& rhs);	
};

class Shuttle
{
private:
	string shuttle_id;
	string charging_point;
	string time_of_arrival;
    bool assigned;

public:
	Shuttle() {
        shuttle_id = "";
		charging_point = "";
		time_of_arrival = "";
        assigned = false;
	}
	Shuttle(string s_id, string cp, string toa) {
        shuttle_id = s_id;
		charging_point = cp;
		time_of_arrival = toa;
        assigned = false;
	}
    
	void get_info();
    void set_assigned(bool input);
	std::string get_time_of_arrival() const { return time_of_arrival; }
	std::string shuttle_id() const { return shuttle_id; }
	std::string get_charging_point() const { return charging_point; }

	friend bool operator==(const Shuttle& lhs, const Passenger& rhs);
	friend bool operator<(const Shuttle& lhs, const Passenger& rhs);
	friend bool operator>(const Shuttle& lhs, const Passenger& rhs);
};

class ScheduleEntry
{
private:
	int schedule_entry_id;
	Shuttle shuttle;
	Passenger passenger;

public:
	ScheduleEntry(int id){
		schedule_entry_id = id;
	}
	void set_pair(const Shuttle& shuttle, const Passenger& passenger);
    void edit_pair(const string& label, const Shuttle& updatedShuttle);
    void delete_pair(const string& label);
    void get_pair();
};

class RoutePlanner
{
private:
	vector<ScheduleEntry> schedule_entries;

public:
	void import_schedule(const string& shuttleFile, const string& passengerFile);
	vector<ScheduleEntry> RoutePlanner::compute_schedule(const vector<Shuttle>, const vector<Passenger>);
	void get_schedule();
	void export_schedule(const string& outputFile);
};















