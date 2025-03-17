/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Ryan Hajtovik
 * Date        : March 12, 2025
 * Description : Solve the Water Jug Problem using BFS
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>

using namespace std;

// Represent a state or snapshot while the algorithm is solving
struct State {
    int a, b, c;
    string path;    // store path as a sting for faster printing

    State(int a, int b, int c, string path): a(a), b(b), c(c), path(path) {} // Constructor to initialize the state with given water levels and path history
};

// Comparison struct to allow sorting and uniqueness in set<State, Compare>
struct Compare {
    bool operator()(const State &s1, const State &s2) const {   // Overload the operator() to define the sorting order for set<State, Compare>
        return tie(s1.a, s1.b, s1.c) < tie(s2.a, s2.b, s2.c);   // Compare states lexicographically: first by 'a', then 'b', then 'c'
    }
};

void solveWaterJugProblem(const int &capA, const int &capB, const int &capC, const int &goalA, const int &goalB, const int &goalC) {
    queue<State> q;
    set<State, Compare> visited;

    // Initial state: (0, 0, capC) because jug C starts full
    State initial(0, 0, capC, "Initial state. (0, 0, " + to_string(capC) + ")\n");
    q.push(initial);
    visited.insert(initial);

    // Defines the pouring actions: (from, to)
    vector<pair<int, int>> actions = {
        {2, 0}, {1, 0}, {2, 1}, {0, 1}, {1, 2}, {0, 2}
    };

    // BFS loop
    while (!q.empty()) {
        State current = q.front();
        q.pop();

        // Base Case: If the goal state is reached, print the path and exit
        if (current.a == goalA && current.b == goalB && current.c == goalC) {
            cout << current.path;
            return;
        }

        // Try all possible pouring actions
        for (auto action : actions) {
            int from = action.first, to = action.second;
            int jug[3] = {current.a, current.b, current.c}; 
            int capacities[3] = {capA, capB, capC};

            // Calculate the maximum pourable amount
            int pourAmount = min(jug[from], capacities[to] - jug[to]);

            // Check if pour is possible
            if (pourAmount > 0) {
                jug[from] -= pourAmount;
                jug[to] += pourAmount;

                // Create the next state after pour
                State nextState(jug[0], jug[1], jug[2], current.path);
                nextState.path += "Pour " + to_string(pourAmount) + (pourAmount == 1 ? " gallon" : " gallons") + " from "
                                + char('A' + from) + " to " + char('A' + to) + ". ("
                                + to_string(nextState.a) + ", " + to_string(nextState.b) + ", " + to_string(nextState.c) + ")\n";

                // If the new state hasn't been visited, enqueue it
                if (visited.find(nextState) == visited.end()) {
                    visited.insert(nextState);
                    q.push(nextState);
                }
            }
        }
    }

    cout << "No solution.\n";
}

bool validateInputs(char * const argv[], int &capA, int &capB, int &capC, int &goalA, int &goalB, int &goalC) {
    int* capactities[] = {&capA, &capB, &capC};
    int* goals[] = {&goalA, &goalB, &goalC};

    // Validate and set capacities
    for(int i = 0; i < 3; i++) {
        istringstream iss(argv[i+1]);
        if(!(iss >> *capactities[i]) || *capactities[i] <= 0) {
            cerr << "Error: Invalid capacity \'" << argv[i+1] << "\' for jug " << char('A' + i) << "." << endl;
            return false;
        }
    }

    // Validate and set goals
    for(int i = 0; i < 3; i++) {
        istringstream iss(argv[i+4]);
        if(!(iss >> *goals[i]) || *goals[i] < 0) {
            cerr << "Error: Invalid goal \'" << argv[i+4] << "\' for jug " << char('A' + i) << "." << endl;
            return false;
        }
    }

    // Validate that capacities are greater than goals
    for(int i = 0; i < 3; i++) {
        if(*goals[i] > *capactities[i]) {
            cerr << "Error: Goal cannot exceed capacity of jug " << char('A' + i) << "." << endl;
            return false;
        }
    }

    // Validate that total gallons in goal state are equal to cap c
    if(goalA + goalB + goalC != capC) {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return false;
    }

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
    
    solveWaterJugProblem(capA, capB, capC, goalA, goalB, goalC);
    return 0;
}