/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Ryan Hajtovik
 * Version     : 1.0
 * Date        : February 5, 2025
 * Description : Finds prime numbers using the Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
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
    const int max_prime_width = digit_tally(topmost_prime_), primes_per_row = 80 / (max_prime_width + 1);

    cout << endl;
    cout << "Number of primes found: " << quantity_of_primes_ << endl;
    cout << "Primes up to " << upper_bound_ << ":";

    // Multiple line print
    if(quantity_of_primes_ > primes_per_row) {
        int count = primes_per_row; // Keep track of position. Start at max to print new line.

        for(int i = 2; i <= upper_bound_; i++) {
            if(candidate_numbers_[i]) {
                // If position at max length start new line with no space, reset counter
                if(count == primes_per_row) { 
                    cout << endl << right << setw(max_prime_width) << i;
                    count = 1;
                }
                // Print a space then the next number, increase position counter
                else {
                    cout << " " << right << setw(max_prime_width) << i;
                    count++;
                }
            }
        }
    }
    // Single line print
    else {
        cout << endl << "2"; // Start new line print 2 without space
        for(int i = 3; i <= upper_bound_; i++) {
            if(candidate_numbers_[i]) {
                cout << " " << i; // Prints rest with space before
            }
        }
    }
}

void PrimesSieve::filter() {
    // Initalize all candidate_numbers_ to be true
    for(int i = 2; i <= upper_bound_; i++) {
        candidate_numbers_[i] = true;
    }

    // Set non-prime numbers to false
    for(int i = 2; i <= sqrt(upper_bound_); i++) {
        if(candidate_numbers_[i]) {
            for(int j = i*i; j <= upper_bound_; j += i) {
                candidate_numbers_[j] = false;
            }
        }
    }

    //Count the number of primes and set the topmost_prime_ to the last counted prime
    quantity_of_primes_ = 0;
    for(int i = 2; i <= upper_bound_; i++) {
        if(candidate_numbers_[i]) {
            quantity_of_primes_++;
            topmost_prime_ = i;
        }
    }
}

int PrimesSieve::digit_tally(int num) {
    //Set tally to one because 2-9 can't be divided by ten
    int tally = 1;

    //Divide by 10 until you can't and increase tally each time
    while(num >= 10) {
        num /= 10;
        tally++;
    }
    return tally;
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

    // Create instance of PrimeSieve called seive and pass upper_bound as the argument
    PrimesSieve seive(upper_bound);

    // Call the print function on the instance
    seive.print_my_primes();
    return 0;
}
