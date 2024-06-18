/* Custom inclusions */
#include "headers.h"


/* Library inclusions */
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <vector>
#include <sstream>
#include <algorithm>


/* Passenger functions */
void Passenger::get_info(){
    cout << "id: " << passenger_id
        << "\nDestination: " << destination
        << "\nTime of arrival: " << time_of_arrival
        << "\nAssigned?: " << assigned;        
}

void Passenger::set_assigned(bool input){
    if(input == true){assigned = true;}
    else {assigned = false;}
}


/* Shuttle functions */
void Shuttle::get_info(){
    cout << "id: " << shuttle_id
        << "\nCharging point: " << charging_point
        << "\nTime of arrival: " << time_of_arrival
        << "\nAssigned?: " << assigned;        
}

void Shuttle::set_assigned(bool input){
    if(input == true) {assigned = true;}
    else {assigned = false;}
}

/*convert time string to format time*/
int timeToMinutes(const std::string& time) {
    std::istringstream ss(time);
    int hours, minutes;
    char colon, am_pm;
    ss >> hours >> colon >> minutes >> am_pm >> am_pm;
    
    if (hours == 12) hours = 0; // handle 12 AM and 12 PM cases
    if (am_pm == 'p' || am_pm == 'P') hours += 12; // convert PM to 24-hour format
    
    return hours * 60 + minutes;
}

/* Friend functions */
bool operator==(const Shuttle& lhs, const Passenger& rhs){
    if(lhs.charging_point == rhs.destination && lhs.time_of_arrival == rhs.time_of_arrival) {return true;}
    else {return false;}
}

bool operator<(const Shuttle& lhs, const Passenger& rhs){
    if(lhs.charging_point < rhs.destination && lhs.time_of_arrival == rhs.time_of_arrival) {return true;}
    else {return false;}
}

bool operator>(const Shuttle& lhs, const Passenger& rhs){
    if(lhs.charging_point > rhs.destination && lhs.time_of_arrival == rhs.time_of_arrival) {return true;}
    else {return false;}    
}




/* ScheduleEntry functions */
void ScheduleEntry::set_pair(const Shuttle& shuttle, const Passenger& passenger){

}

void ScheduleEntry::edit_pair(const string& label, const Shuttle& updatedShuttle){

}

void ScheduleEntry::delete_pair(const string& label){

}

void ScheduleEntry::get_pair(){

}


/* RoutePlanner functions */
void RoutePlanner::import_schedule(const string& shuttleFile, const string& passengerFile){

}

vector<ScheduleEntry> RoutePlanner::compute_schedule(vector<Shuttle> shuttles, vector<Passenger> passengers){
    
    /* Sorting algorithm */
    std::sort(shuttles.begin(), shuttles.end(), [](const Shuttle& a, const Shuttle& b) {
        if (a.get_charging_point() == b.get_charging_point()) {                                     // Check if charging points are the same
            return timeToMinutes(a.get_time_of_arrival()) < timeToMinutes(b.get_time_of_arrival()); // Compare by time of arrival if same
        }
        return a.get_charging_point() < b.get_charging_point();                                     // Otherwise, compare by charging point
    });

    std::sort(passengers.begin(), passengers.end(), [](const Passenger& a, const Passenger& b) {    
        if (a.get_destination() == b.get_destination()) {                                           // Check if destinations are the same
            return timeToMinutes(a.get_time_of_arrival()) < timeToMinutes(b.get_time_of_arrival()); // If so, compare by time of arrival
        }
        return a.get_destination() < b.get_destination();                                           // Otherwise, compare by destination
    });
    

    /* Matching algorithm */
    size_t index_s = 0, index_p = 0;                                                // Initialise pointers for vectors
    int pair_id = 1;                                                                // Initialise id for ScheduleEntry

    vector<ScheduleEntry> returnVector;                                             // Instantiate vector to compile pairs

    while (index_s < shuttles.size() && index_p < passengers.size())                // Loop ends when either index exceeds vector size
    {
        if(shuttles[index_s] == passengers[index_p]){                               // Refer to friend operator overload function
            returnVector.emplace_back(ScheduleEntry(pair_id));                      // Instantiates new entry into back of vector
            returnVector.back().set_pair(shuttles[index_s], passengers[index_p]);   // Set objects as pair in ScheduleEntry
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

    RoutePlanner::schedule_entries = returnVector;                                  // Updates RoutePlanner's data with vector of schedule entries

    return returnVector;                                                            // Returns vector of schedule entries
}

void RoutePlanner::get_schedule(){

}

void RoutePlanner::export_schedule(const string& outputFile){

}











