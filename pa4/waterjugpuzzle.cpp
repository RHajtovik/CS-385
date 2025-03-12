/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Ryan Hajtovik
 * Date        : March 12, 2025
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

bool validateInputs(char * const argv[], int &capA, int &capB, int &capC, int &goalA, int &goalB, int &goalC) {
    istringstream iss;
    int* capactities[] = {&capA, &capB, &capC};
    int* goals[] = {&goalA, &goalB, &goalC};

    // Validate and set capacities
    for(int i = 0; i < 3; i++) {
        iss.str(argv[i+1]);
        if(!(iss >> *capactities[i]) || *capactities[i] < 0) {
            cerr << "Error: Invalid capacity " << argv[i+1] << " for jug " << char('A' + i) << "." << endl;
            return false;
        }
        iss.clear();
    }

    iss.str(argv[1]);
    if (!(iss >> capA || capA < 0)){
        cerr << "Error: Invalid capacity " << argv[1] << " for jug A." << endl;
        return false;
    }
    iss.clear();

    return true;
}

int main(int argc, char * const argv[]) {
    int capA, capB, capC, goalA, goalB, goalC;

    if(argc != 7) {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    if (!validateInputs(argv, capA, capB, capC, goalA, goalB, goalC)) {
        return 1;
    }
}