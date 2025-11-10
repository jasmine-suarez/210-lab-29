// COMSC-210 | Lab 29 | Jasmine Suarez
// IDE used: VS Code

#include <iostream>
#include <fstream>
#include <map>
#include <array>
#include <list>
#include <cstdlib>
#include <ctime>
using namespace std;

// Define a function to simulate one time period (hour) of changes
    // Parameters: map of gates, number of intervals
void simulate_time_period(map<string, array<list<string>, 3>> &airportMap, int hour);

int main() {
    srand(time(0));
    // Initialize a map to store gate info, each associated with an array of lists
    // for arrivals, departures, and delays
    map<string, array<list<string>, 3>> airportMap;

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
        cout << gatePair.first << ": \n";

        cout << "    Arrivals: ";
        for (auto &flight : gatePair.second[0])
            cout << flight << " ";

        cout << "\n    Departures: ";
        for (auto &flight : gatePair.second[1])
            cout << flight << " ";

        cout << "\n    Delayed: ";
        for (auto &flight : gatePair.second[2])
            cout << flight << " ";
        cout << endl;
    }

    // Begin a time-based simulation for flight changes
        // For 25 time intervals
    for (int hour = 1; hour <= 25; hour++)
        simulate_time_period(airportMap, hour);
        
    // Display the final state of all gates and flights
    cout << "\n=== FINAL AIRPORT STATUS ===" << endl;
    for (auto &gatePair : airportMap) {
        cout << gatePair.first << ": \n";

        cout << "    Arrivals: ";
        for (auto &flight : gatePair.second[0])
            cout << flight << " ";

        cout << "\n    Departures: ";
        for (auto &flight : gatePair.second[1])
            cout << flight << " ";

        cout << "\n    Delayed: ";
        for (auto &flight : gatePair.second[2])
            cout << flight << " ";
        cout << endl;
    }

    return 0;
}

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

        // 50% CHANCE THAT A DELAYED FLIGHT WILL BE CLEARED FOR DEPARTURE
        if (!flightLists[2].empty()) {
            int random = rand() % 100;
            if (random < 50) { // 50% chance
                string flight = flightLists[2].front();
                flightLists[2].pop_front();
                flightLists[1].push_back(flight);
                cout << "Flight " << flight << " is cleared for departure at " << gateName << endl;
            }
        }

        // 25% CHANCE THAT A DEPARTURE WILL BE DELAYED
        if (!flightLists[1].empty()) {
            int random = rand() % 100;
            if (random < 25) { // 25% chance
                string flight = flightLists[1].front();
                flightLists[1].pop_front();
                flightLists[2].push_back(flight);
                cout << "Flight " << flight << " delayed at " << gateName << endl;
            }
        }

        // 25% CHANCE THAT A DEPARTING FLIGHT LEAVES
        if (!flightLists[1].empty()) {
            int random = rand() % 100;
            if (random < 25) {
                string flight = flightLists[1].front();
                flightLists[1].pop_front();
                cout << "Flight " << flight << " is now departing from " << gateName << endl;
            }
        }
    }
}