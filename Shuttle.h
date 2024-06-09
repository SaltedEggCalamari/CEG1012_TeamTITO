#include <string>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
class Shuttle
{
private:
	string shuttle_id;
	string charging_point;
	string time_of_arrival;

public:
	Shuttle(string s_id, string cp, string toa) {
		shuttle_id = s_id;
		 charging_point = cp;
		 time_of_arrival = toa;
	}
};

