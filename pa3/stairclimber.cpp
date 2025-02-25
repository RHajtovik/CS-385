/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Ryan Hajtovik
 * Date        : February 24, 2025
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    if (num_stairs == 0) {
        return {{}};
    }
    
    vector< vector<int> > ways;

    for (int i = 1; i <=3; i++) {
        if (num_stairs >= i) {
            auto result = get_ways(num_stairs - i);
            for (auto& way : result) {                  // for each vector(way) in vector of vectors(result)
                way.insert(way.begin(), i);             // insert i to the beginining of the way vector
                ways.push_back(way);                    // add entire way vector to the end of the ways vector
            }
        }
    }

    return ways;
}

// Count the digits for setw
int count_digit(int number) {
    int count = 0;
    while(number != 0) {
       number = number / 10;
       count++;
    }
    return count;
 }

void display_ways(const vector< vector<int> > &ways) {

    // Print out y way(s) to climb x stair(s)
    cout << ways.size() << " way" << (ways.size() == 1 ? "" : "s")
        << " to climb " << ways[0].size() << " stair" << (ways.size() == 1 ? "." : "s.") << endl;

    for (size_t i = 0; i < ways.size(); i++) {                                  // Loop through each outer vector in ways
        cout << right << setw(count_digit(ways.size())) << i + 1 << ". [";      // Print and align number

        for (size_t j = 0; j < ways[i].size(); j++) {                           // Loop through each element the inner vector
            cout << ways[i][j];                                                 // print that element
            if (j != ways[i].size() - 1) {                                      // check j is not second to last element
                cout << ", ";                                                   // print ", " if multiple more elements remain
            }
        }

        cout << "]" << endl;                                                    
    }
}

int main(int argc, char * const argv[]) {
    int num_stairs;
    istringstream iss;

    // Check for correct arguments
    if (argc != 2) {
        cerr << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    // Check that argument is valid
    iss.str(argv[1]);
    if (!(iss >> num_stairs) || num_stairs <= 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    iss.clear();
    
    display_ways(get_ways(num_stairs));
}
