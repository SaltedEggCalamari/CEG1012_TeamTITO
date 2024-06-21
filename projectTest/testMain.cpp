#include "headers.h"
#include "headers.cpp"

#include <iostream>
#include <string>
#include <fstream>


int main(){
    std::string shuttleFilePath, passengerFilePath;
    std::cout << "Enter the path to the shuttle data file: ";
    std::cin >> shuttleFilePath;
    std::cout << "Enter the path to the passenger data file: ";
    std::cin >> passengerFilePath;

    RoutePlanner planner;
    vector<ScheduleEntry> schedule;
    vector<Passenger> passengers;
    vector<Shuttle> shuttles;

    passengers = planner.import_passenger(passengerFilePath);
    shuttles = planner.import_shuttle(shuttleFilePath);
    
    int option=0;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Create passenger\n";
        std::cout << "2. Create shuttle\n";
        std::cout << "3. Delete passenger\n";
        std::cout << "4. Delete shuttle\n";
        std::cout << "5. Update Passenger\n";
        std::cout << "6. Update Shuttle\n";
        std::cout << "7. Compute Schedule\n";
        std::cout << "8. Show all\n";
        std::cout << "9. Export Schedule\n";
        std::cout << "10. Assess Passenger\n";
        std::cout << "11. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                std::cout << "Creating new passenger...\n";

                string id, d, t;
                std::cout << "Enter passenger id: ";
                std::cin >> id;
                std::cout << "Enter destination: ";
                std::cin >> d;
                std::cout << "Enter arrival time: ";
                std::cin >> t;
                passengers.emplace_back(Passenger(id, d, t));

                break;
            }
            
            case 2:{
                std::cout << "Creating new shuttle\n";

                string id, d, t;
                std::cout << "Enter shuttle id: ";
                std::cin >> id;
                std::cout << "Enter destination: ";
                std::cin >> d;
                std::cout << "Enter arrival time: ";
                std::cin >> t;
                shuttles.emplace_back(Shuttle(id, d, t));

                break;
            }            

            case 3:{
                std::cout << "Deleting passenger...\n";

                string id;
                bool deleteSuccess = false;
                std::cout << "Enter passenger id: ";
                std::cin >> id;

                for(size_t i=0; i<passengers.size(); i++){
                    if(passengers[i].get_passenger_id() == id){
                        auto it = passengers.begin() + i;
                        passengers.erase(it);
                        deleteSuccess = true;
                        break;
                    }
                }

                if(deleteSuccess == true){
                    std::cout << "Passenger successfully deleted!\n";
                } else if(deleteSuccess == false){
                    std::cout << "Passenger not found!\n";
                }
            
                break;
            }

            case 4: {
                std::cout << "Deleting shuttle...\n";

                string id;
                bool deleteSuccess = false;
                std::cout << "Enter shuttle id: ";
                std::cin >> id;

                for(size_t i=0; i<shuttles.size(); i++){
                    if(shuttles[i].get_shuttle_id() == id){
                        auto it = shuttles.begin() + i;
                        shuttles.erase(it);
                        deleteSuccess = true;
                        break;
                    }
                }

                if(deleteSuccess == true){
                    std::cout << "Shuttle successfully deleted!\n";
                } else if(deleteSuccess == false){
                    std::cout << "Shuttle not found!\n";
                }
            
                break;
                
            }

            case 5: {
                std::cout << "Updating passenger...\n";

                string id, d, t;
                bool updateSuccess = false;
                std::cout << "Enter passenger id: ";
                std::cin >> id;

                for(size_t i=0; i<passengers.size(); i++){
                    if(passengers[i].get_passenger_id() == id){
                        std::cout << "(Leave blank to remain unchanged): ";
                        std::cout << "Enter destination: ";
                        std::cin >> d;
                        std::cout << "Enter arrival time: ";
                        std::cin >> t;

                        if(d != ""){passengers[i].set_destination(d);}
                        if(t != ""){passengers[i].set_arrival_time(t);}

                        updateSuccess = true;
                        break;
                    }
                }

                if(updateSuccess == true){
                    std::cout << "Passenger successfully updated!\n";
                } else if(updateSuccess == false){
                    std::cout << "Passenger not found!\n";
                }

                break;
            }

            case 6: {
                std::cout << "Updating shuttle...\n";

                string id, d, t;
                bool updateSuccess = false;
                std::cout << "Enter shuttle id: ";
                std::cin >> id;

                for(size_t i=0; i<shuttles.size(); i++){
                    if(shuttles[i].get_shuttle_id() == id){
                        std::cout << "(Leave blank to remain unchanged): ";
                        std::cout << "Enter destination: ";
                        std::cin >> d;
                        std::cout << "Enter arrival time: ";
                        std::cin >> t;

                        if(d != ""){shuttles[i].set_destination(d);}
                        if(t != ""){shuttles[i].set_arrival_time(t);}

                        updateSuccess = true;
                        break;
                    }
                }

                if(updateSuccess == true){
                    std::cout << "Shuttle successfully updated!\n";
                } else if(updateSuccess == false){
                    std::cout << "Shuttle not found!\n";
                }

                break;
            }
            
            case 7: {
                std::cout << "Computing schedule...\n";

                schedule = planner.compute_schedule(shuttles, passengers);

                if(schedule.size() == 0){
                    std::cout << "Schedule is empty" << endl;
                } else{
                    std::cout << "Schedule successfully created!" << endl;
                }

                break;
            }

            case 8: {
                std::cout << "Showing all...\n";

                planner.show_all(schedule, passengers, shuttles);

                break;
            }

            case 9: {
                std::cout << "Exporting schedule...\n";

                std::string filename;
                std::cout << "Enter filename to save schedule: ";
                std::cin >> filename;
                
                planner.export_schedule(filename, schedule);

                break;
            }

            case 10: {
                std::cout << "Assessing passengers...\n";
                
                planner.assess_passengers(passengers);

                break;
            }
            
            case 11: {
                std::cout << "Exiting Route Planner...\n";
                break;
            }
        }
    } while (option != 11);

    return 0;
}
  
