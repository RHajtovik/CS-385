#include <vector>
#include <iostream>
using namespace std;

int hoare_partition(int array[], int left, int right) {
    int p = array[left];
    int i = left - 1;
    int j = right + 1;

    while (true) {
        i++;
        while (array[i] < p){
            i++;
        }
            
        j--;
        while (array[j] > p) {
            j--;
        }

        if (i >= j) {
            return j;
        }
        swap(array[i], array[j]);
        // Just print the array after each swap
        for (int k = 0; k <= right; k++) {
            cout << array[k] << " ";
        }
        cout << endl;
    }

    
}


int main() {
    int array[] = {6,2,9,4,8,0,1,3};
    int size = sizeof(array) / sizeof(array[0]);
    hoare_partition(array, 0, size - 1);

    return 0;
}