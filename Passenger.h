#include <string>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

class Passenger
{
private:
	string passenger_id;
	string destination;
	string time_of_arrival;

public:
	Passenger(string p_id, string dest, string toa) {
		passenger_id = p_id;
		destination = dest;
		time_of_arrival = toa;
	}
};
