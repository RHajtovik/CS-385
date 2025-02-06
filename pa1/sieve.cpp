/*******************************************************************************
 * Name        : sieve.cpp
 * Author      :
 * Date        :
 * Description : Sieve of Eratosthenes
 * Pledge      :
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int upper_bound);

    ~PrimesSieve() {
        delete [] candidate_numbers_;
    }

    void print_my_primes() const;

private:
    // Instance variables
    bool * const candidate_numbers_;
    const int upper_bound_;
    int quantity_of_primes_, topmost_prime_;

    // Method declarations
    void filter();
    static int digit_tally(int num);
};

PrimesSieve::PrimesSieve(int upper_bound) :
        candidate_numbers_{new bool[upper_bound + 1]}, upper_bound_{upper_bound} {
    filter();
}

void PrimesSieve::print_my_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
}

void PrimesSieve::filter() {
    // TODO: write sieve algorithm
    // All instance variables must be initialized by the end of this method.
}

int PrimesSieve::digit_tally(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    return 0;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string upper_bound_str;
    cin >> upper_bound_str;
    int upper_bound;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(upper_bound_str);

    // Check for error.
    if ( !(iss >> upper_bound) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (upper_bound < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    return 0;
}
