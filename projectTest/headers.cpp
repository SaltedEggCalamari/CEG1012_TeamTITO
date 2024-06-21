/* Custom inclusions */
#include "headers.h"


/* Library inclusions */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>


/* Friend functions */
bool operator==(const Shuttle& lhs, const Passenger& rhs){
    if(lhs.destination == rhs.destination && lhs.arrival_time == rhs.arrival_time) {return true;}
    else {return false;}
}

bool operator<(const Shuttle& lhs, const Passenger& rhs){
    if(lhs.destination < rhs.destination && lhs.arrival_time == rhs.arrival_time) {return true;}
    else {return false;}
}

bool operator>(const Shuttle& lhs, const Passenger& rhs){
    if(lhs.destination > rhs.destination && lhs.arrival_time == rhs.arrival_time) {return true;}
    else {return false;}    
}


/* Time formatting function */
int timeToMinutes(const std::string& time) {
    std::istringstream ss(time);
    int hours, minutes;
    char colon, am_pm;
    ss >> hours >> colon >> minutes >> am_pm >> am_pm;
    
    if (hours == 12) hours = 0; // handle 12 AM and 12 PM cases
    if (am_pm == 'p' || am_pm == 'P') hours += 12; // convert PM to 24-hour format
    
    return hours * 60 + minutes;
}


/* RoutePlanner functions */
vector<Passenger> RoutePlanner::import_passenger(const string& passengerFile){
    vector<Passenger> passengers;

    ifstream file(passengerFile);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, destination, time;
        getline(iss, id, ',');
        getline(iss, destination, ',');
        getline(iss, time, ',');
        passengers.emplace_back(Passenger(id, destination, time));
    }

    return passengers;
}

vector<Shuttle> RoutePlanner::import_shuttle(const string& shuttleFile){
    vector<Shuttle> shuttles;

    ifstream file(shuttleFile);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, destination, time;
        getline(iss, id, ',');
        getline(iss, destination, ',');
        getline(iss, time, ',');
        shuttles.emplace_back(Shuttle(id, destination, time));
    }

    return shuttles;
}

vector<ScheduleEntry> RoutePlanner::compute_schedule(vector<Shuttle> shuttles, vector<Passenger> passengers){
    
    /* Sorting algorithm */
    std::sort(shuttles.begin(), shuttles.end(), [](const Shuttle& a, const Shuttle& b) {
        if (a.get_destination() == b.get_destination()) {                                     // Check if charging points are the same
            return timeToMinutes(a.get_arrival_time()) < timeToMinutes(b.get_arrival_time()); // Compare by time of arrival if same
        }
        return a.get_destination() < b.get_destination();                                     // Otherwise, compare by charging point
    });

    std::sort(passengers.begin(), passengers.end(), [](const Passenger& a, const Passenger& b) {    
        if (a.get_destination() == b.get_destination()) {                                           // Check if destinations are the same
            return timeToMinutes(a.get_arrival_time()) < timeToMinutes(b.get_arrival_time()); // If so, compare by time of arrival
        }
        return a.get_destination() < b.get_destination();                                           // Otherwise, compare by destination
    });
    
    /* Matching algorithm */
    size_t index_s = 0, index_p = 0;                                                // Initialise pointers for vectors
    int pair_id = 1;                                                                // Initialise id for ScheduleEntry

    vector<ScheduleEntry> schedule_vector;                                             // Instantiate vector to compile pairs

    while (index_s < shuttles.size() && index_p < passengers.size())                // Loop ends when either index exceeds vector size
    {
        if(shuttles[index_s] == passengers[index_p]){                               // Refer to friend operator overload function
            schedule_vector.emplace_back(ScheduleEntry(pair_id));                      // Instantiates new entry into back of vector
            schedule_vector.back().set_pair(shuttles[index_s], passengers[index_p]);   // Set objects as pair in ScheduleEntry
            pair_id++;                                                              // Increments id for next pair

            shuttles[index_s].set_assigned(true);                                   // Updates shuttle and passenger to reflect new assigned status
            passengers[index_p].set_assigned(true);

            auto it_s = shuttles.begin() + index_s; shuttles.erase(it_s);           // Creates iterator for shuttle and passenger indexes
            auto it_p = passengers.begin() + index_p; passengers.erase(it_p);       // then erases them from the vector
            index_s=0; index_p=0;                                                   // Restart search index from 0
        } 
        else if(shuttles[index_s] > passengers[index_p]) {index_p++;}               // Match not found, continue search
        else if(shuttles[index_s] < passengers[index_p]) {index_s++;}               // by incrementing smaller index
    }

    return schedule_vector;                                                         // Returns vector of schedule entries
}

void RoutePlanner::show_all(vector<ScheduleEntry> schedule, vector<Passenger> u_passengers, vector<Shuttle> u_shuttles){
    int size_schedule=schedule.size(), size_passengers=u_passengers.size(), size_shuttles=u_shuttles.size();
    
    size_t index=0;
    cout << "\nSCHEDULE" << endl;
    cout << "Number of entries: " << size_schedule << endl;
    while(index < size_schedule){
        Shuttle s = schedule[index].get_shuttle();
        Passenger p = schedule[index].get_passenger();

        cout << "ID: " << schedule[index].get_entry_id() << " --> " << s.get_shuttle_id() << " and " << p.get_passenger_id();
    }

    index = 0;
    cout << "\n\nUNASSIGNED PASSENGERS" << endl;
    cout << "Number of entries: " << size_passengers << endl;
    while(index < size_shuttles){
        cout << "ID: " <<  u_passengers[index].get_passenger_id()
        << "\nGoing to " << u_passengers[index].get_destination() << " at " << u_passengers[index].get_arrival_time();
    }

    index = 0;
    cout << "\n\nUNASSIGNED SHUTTLES" << endl;
    cout << "Number of entries: " << size_shuttles << endl;
    while(index < size_passengers){
        cout << "ID: " <<  u_shuttles[index].get_shuttle_id()
        << "\nGoing to " << u_shuttles[index].get_destination() << " at " << u_shuttles[index].get_arrival_time();
    }

}

void RoutePlanner::export_schedule(const string& outputFile, vector<ScheduleEntry> entries){
    std::ofstream file(outputFile);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << outputFile << " for writing." << std::endl;
        return;
    }

    try {
        size_t index = 0;

        while(index < entries.size()){
            Shuttle s = entries[index].get_shuttle();
            Passenger p = entries[index].get_passenger();

            file << "Schedule ID    : " << entries[index].get_entry_id()
                << "\nShuttle ID    : " << s.get_shuttle_id()
                << "\nPassenger ID  : " << p.get_passenger_id()
                << "\nDestination   : " << s.get_destination()
                << "\nArrival Time  : " << s.get_arrival_time();            
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: Exception occurred while writing to file: " << e.what() << std::endl;
    }
}

void RoutePlanner::assess_passengers(vector<Passenger> passengers){
    map<string, int> destination_map;
    map<string, int> time_map;

    for(int i=0; i < passengers.size(); i++){
        string d = passengers[i].get_destination();
        string t = passengers[i].get_arrival_time();
        
        auto it_d = destination_map.find(d);
        if (it_d != destination_map.end()){
            destination_map[d] += 1;
        } else{
            destination_map.insert({d, 1});
        }

        auto it_t = time_map.find(t);
        if (it_t != time_map.end()){
            time_map[t] += 1;
        } else{
            time_map.insert({t, 1});
        }
    }

    string d_first, d_second, d_third;
    int x=0, y=0, z=0;
    for(const auto& pair: destination_map){
        if(pair.second > x){
            d_second = d_first;
            y = x;

            d_first = pair.first;
            x = pair.second;

        } else if(pair.second > y){
            d_third = d_second;
            z = y;

            d_second = pair.first;
            y = pair.second;
            
        } else if(pair.second > z){
            d_third = pair.first;
            z = pair.second;
        }
    }

    string t_first, t_second, t_third;
    x=0, y=0, z=0;
    for(const auto& pair: time_map){
        if(pair.second > x){
            t_second = t_first;
            y = x;

            t_first = pair.first;
            x = pair.second;

        } else if(pair.second > y){
            t_third = t_second;
            z = y;

            t_second = pair.first;
            y = pair.second;
            
        } else if(pair.second > z){
            t_third = pair.first;
            z = pair.second;
        }
    }

    cout << "Top 3 destinations:" << endl;
    cout << "1. " << d_first
        << "\n2. " << d_second
        << "\n3. " << d_third << endl;
    cout << "Top 3 timings:" << endl;
    cout << "1. " << t_first
        << "\n2. " << t_second
        << "\n3. " << t_third << endl;
}








