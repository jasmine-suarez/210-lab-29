// COMSC-210 | Lab 29 | Jasmine Suarez
// IDE used: VS Code

#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
// #include <cstdlib>
// #include <ctime>
using namespace std;

// Define a function to simulate one time period (hour) of changes
    // Parameters: map of gates, number of intervals
void simulate_time_period(map<string, array<list<string>, 3>> &airportMap, int hour) {
    cout << "\n --- HOUR " << hour << " ---" << endl;

    // iterate through gates
    for (auto &gatePair : airportMap) {
        string gateName = gatePair.first;
        auto &flightLists = gatePair.second;

        // TEST, CHANGE ARRIVING FLIGHT TO DEPARTING
        if (!flightLists[0].empty()) {
            string flight = flightLists[0].front();
            flightLists[0].pop_front();         // remove from arrivals
            flightLists[1].push_back(flight);   // add to departures
            cout << "Flight " << flight << " moved from arrivals to departures at " << gateName << endl;
        }
    }
}

int main() {
    // Initialize a map to store gate info, each associated with an array of lists
    // for arrivals, departures, and delays
    map<string, array<list<string>, 3>> airportMap;

    // TEST, DUMMY GATE AND FLIGHT
    airportMap["Gate A1"][0].push_back("AA123"); // [0] = arrivals list

    // Open an external file to read initial flight data and populate the map
        // If file doesn't open, print error and exit
    ifstream fin;
    fin.open("flights.txt");
    if (!fin.good()) {
        cout << "Error! File not found. Exiting program...\n";
        return 0;
    }

    // Read data from file and populate map
        // For each line, extract gate, flight number, and status
        // Insert flight into list in the array for that gate
    string gate, flight, status;
    while (fin >> gate >> flight >> status) {
        auto &lists = airportMap[gate];

        if (status == "arrival")
            lists[0].push_back(flight);
        else if (status == "departure")
            lists[1].push_back(flight);
        else if (status == "delay")
            lists[2].push_back(flight);
    }
    // Close the file
    fin.close();

    // Display the initial state of all gates and flights
    cout << "=== INITIAL AIRPORT STATUS ===" << endl;
    for (auto &gatePair : airportMap) {
        cout << gatePair.first << ": ";
        for (auto &flight : gatePair.second[0])
            cout << flight << " ";
        cout << endl;
    }

    // TEST, SIMULATE 1 TIME PERIOD
    simulate_time_period(airportMap, 1);

    // Begin a time-based simulation for flight changes
        // For 25 time intervals
            // Iterate through each gate in the map
                // For each gate, simulate flight events
                    // Randomly decide which flights move between arrivals, departures, and delays
                        // If a flight departs, remove from arrivals
                        // If a flight is delayed, move from departures to delayed
                        // If a delayed flight departs, remove from delayed and add to departures
                    // Print the changes for this interval

            // Pause briefly to simulate time between intervals
        
    // Display the final state of all gates and flights

    return 0;
}