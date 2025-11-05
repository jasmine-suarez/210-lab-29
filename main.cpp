// COMSC-210 | Lab 29 | Jasmine Suarez
// IDE used: VS Code

#include <iostream>
// #include <fstream>
#include <map>
#include <array>
#include <list>
// #include <cstdlib>
// #include <ctime>
using namespace std;

// Define a function to simulate one time period (hour) of changes
    // Parameters: map of gates, number of intervals

int main() {
    // Initialize a map to store gate info, each associated with an array of lists
    // for arrivals, departures, and delays
    map<string, array<list<string>, 3>> airportMap;

    // TEST, DUMMY GATE AND FLIGHT
    airportMap["Gate A1"][0].push_back("AA123"); // [0] = arrivals list

    // Open an external file to read initial flight data and populate the map
        // If file doesn't open, print error and exit

    // Read data from file and populate map
        // For each line, extract gate, flight number, and status
        // Insert flight into list in the array for that gate

    // Close the file

    // Display the initial state of all gates and flights
    cout << "=== INITIAL AIRPORT STATUS ===" << endl;
    for (auto gatePair : airportMap) {
        cout << gatePair.first << ": ";
        for (auto flight : gatePair.second[0])
            cout << flight << " ";
        cout << endl;
    }

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