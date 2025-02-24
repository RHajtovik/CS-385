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
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    
}

void display_ways(const vector< vector<int> > &ways) {
    for (size_t i = 1; i < ways.size(); i++) {
        cout << i << ". [";

        for (size_t j = 0; i < ways[i].size()-1; j++) {
            cout << ways[i][j];
            if(j < ways[i].size()-1) {
                cout << ", ";
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
        cerr << "Usage ./stairclimber <number of stairs>" << endl;
        return 1;
    }

    // Check that argument is valid
    iss.str(argv[1]);
    if (!(iss >> num_stairs) || num_stairs > 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    iss.clear();
    
    get_ways(num_stairs);
}
