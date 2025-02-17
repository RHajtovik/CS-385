/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Ryan Hajtovik
 * Date        : February 17, 2025
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(char c : s) {           // Loop through each character in the string
        if (!islower(c)){       // Check if character is lower case
            return false;       // If not lower case return false
        }
    }
    return true;                // Return true after every character has been checked
}

bool all_unique_letters(const string &s) {
    unsigned int bit_vector = 0;                        // initialize bit vector

    for(char c : s) {                                   // Loop through every character in sting
        int bit_position = c - 'a';                     // Determine the bit position (0 for 'a', 1 for 'b', ..., 25 for 'z')
        
        if((bit_vector & (1 << bit_position)) != 0) {   // left shift 1 to the bit_position, check that the new bit is not set in the bit vector
            return false;                               // If bit is already set, character is a duplicate, return false
        }
        
        bit_vector |= (1 << bit_position);              // Set the bit at the bit_position in the bit_vector to mark the character as seen
    }

    return true;                                        // Return true after every character is checked, and no duplicates found
}

int main(int argc, char * const argv[]) {
    // Check for valid arguments
    if (argc != 2) {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    string s = argv[1];

    if (!is_all_lowercase(s)) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (all_unique_letters(s)) {
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }

    return 0;
}
