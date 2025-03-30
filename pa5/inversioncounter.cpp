/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Ryan Hajtovik
 * Version     : 1.0
 * Date        : March 30, 2035
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for (int i = 0; i < length -1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] > array[j]) {
                ++count;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int[length];
    long count = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {

    if (low >= high) return 0;

    int mid = low + (high - low) / 2;
    long count = 0;
    count += mergesort(array, scratch, low, mid);
    count += mergesort(array, scratch, mid + 1, high);

    int left = low, right = mid + 1, index = low;

    while (left <= mid && right <= high) {
        if (array[left] <= array[right]) {
            scratch[index++] = array[left++];
        }
        else {
            scratch[index++] = array[right++];
            count += (mid - left + 1); // Every element remaining in left[] is an inversion.
        }
    }

    for (int i = left; i <= mid; i++) {
        scratch[index++] = array[left++];
    }
    
    for (int i = right; i <= high; i++) {
        scratch[index++] = array[right++];
    }

    for (int i = low; i <= high; i++) {
        array[i] = scratch[i];
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        cerr << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }

    bool use_slow = false;
    if (argc == 2) {
        string arg = argv[1];
        if (arg == "slow") {
            use_slow = true;
        }
        else {
            cerr << "Error: Unrecognized option \'" << arg << "\'." << endl;
            return 1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    if (values.size() == 0) {
        cerr << "Error: Sequence of integers not received.";
        return 1;
    }

    long inversions;
    if (use_slow) {
        inversions = count_inversions_slow(&values[0], values.size());
        cout << "Number of inversions (slow): " << inversions << endl;
    }
    else {
        inversions = count_inversions_fast(&values[0], values.size());
        cout << "Number of inversions (fast): " << inversions << endl;
    }

    return 0;
}
