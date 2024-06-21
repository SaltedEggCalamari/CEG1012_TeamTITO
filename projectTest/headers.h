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
	string arrival_time;
    bool assigned;

public:
	Passenger(){
		passenger_id = "";
		destination = "";
		arrival_time = "";
		assigned = false;
	}
	Passenger(string p_id, string dest, string t) {
		passenger_id = p_id;
		destination = dest;
		arrival_time = t;
        assigned = false;
	}
    
	void show_info(){
		cout << "id: " << passenger_id
			<< "\nDestination: " << destination
			<< "\nArrival Time: " << arrival_time
			<< "\nAssigned?: " << assigned << endl;        
	}
	
	void set_destination(string input){
		destination = input;
	}
	void set_arrival_time(string input){
		arrival_time = input;
	}
	void set_assigned(bool input){
		if(input == true){assigned = true;}
		else {assigned = false;}
	}

	std::string get_passenger_id() const { return passenger_id; }
	std::string get_arrival_time() const { return arrival_time; }
	std::string get_destination() const { return destination; }
	
	friend bool operator==(const Shuttle& lhs, const Passenger& rhs);
	friend bool operator<(const Shuttle& lhs, const Passenger& rhs);
	friend bool operator>(const Shuttle& lhs, const Passenger& rhs);	
};

class Shuttle
{
private:
	string shuttle_id;
	string destination;
	string arrival_time;
    bool assigned;

public:
	Shuttle() {
        shuttle_id = "";
		destination = "";
		arrival_time = "";
        assigned = false;
	}
	Shuttle(string s_id, string dest, string t) {
        shuttle_id = s_id;
		destination = dest;
		arrival_time = t;
        assigned = false;
	}
    
	void show_info(){
		cout << "id: " << shuttle_id
			<< "\nDestination: " << destination
			<< "\nArrival Time: " << arrival_time
			<< "\nAssigned?: " << assigned << endl;        
	}
    
	void set_destination(string input){
		destination = input;
	}
	void set_arrival_time(string input){
		arrival_time = input;
	}
	void set_assigned(bool input){
		if(input == true) {assigned = true;}
		else {assigned = false;}
	}

	std::string get_shuttle_id() const { return shuttle_id; }
	std::string get_arrival_time() const { return arrival_time; }
	std::string get_destination() const { return destination; }

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
	ScheduleEntry(int id){schedule_entry_id = id;}
	
	void set_pair(const Shuttle&, const Passenger&){
		this->shuttle = shuttle;
		this->passenger = passenger;
	}
    void edit_shuttle(const Shuttle&){
		this->shuttle = shuttle;
	}
	void edit_passenger(const Passenger&){
		this->passenger = passenger;
	}
    void show_pair(){
		cout << "Entry ID: " << this->schedule_entry_id;
		cout << "\nShuttle info: " << endl;
		this->shuttle.show_info();
		cout << "Passenger info: " << endl;
		this->passenger.show_info();
	}

	int get_entry_id(){return this->schedule_entry_id;}
	Shuttle get_shuttle(){return this->shuttle;}
	Passenger get_passenger(){return this->passenger;}
};

class RoutePlanner
{
public:
	vector<Passenger> import_passenger(const string&);
	vector<Shuttle> import_shuttle(const string&);
	vector<ScheduleEntry> compute_schedule(const vector<Shuttle>, const vector<Passenger>);
	void show_all(vector<ScheduleEntry>, vector<Passenger>, vector<Shuttle>);
	void export_schedule(const string&, vector<ScheduleEntry>);

	void assess_passengers(vector<Passenger>);
};














