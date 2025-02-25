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
            for (auto& way : result) {
                way.insert(way.begin(), i);
                ways.push_back(way);
            }
        }
    }

    return ways;
}

int count_digit(int number) {
    int count = 0;
    while(number != 0) {
       number = number / 10;
       count++;
    }
    return count;
 }

void display_ways(const vector< vector<int> > &ways) {
    cout << ways.size() << " way" << (ways.size() <= 1 ? "" : "s")
        << " to climb " << __argv[1] << " stair" << (ways.size() <= 1 ? "." : "s.") << endl;

    for (size_t i = 0; i < ways.size(); i++) {
        cout << right << setw(count_digit(ways.size())) << i + 1 << ". [";

        for (size_t j = 0; j < ways[i].size(); j++) {
            cout << ways[i][j];
            if (j != ways[i].size() - 1) {
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
    if (!(iss >> num_stairs) || num_stairs <= 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    iss.clear();
    
    display_ways(get_ways(num_stairs));
}
