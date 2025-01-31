/*******************************************************************************
 * Filename: student.cpp
 * Author  : 
 * Version : 1.0
 * Date    : January 1, 2025
 * Description: Computes the GCD of two command-line arguments.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Student {
public:
    Student(string first_name, string last_name, int id, float gpa) : first_{first_name}, last_{last_name}, id_{id}, gpa_{gpa} {}

    void print_info() const {
        cout << first_ << ' ' << last_ << ', ' << fixed << setprecision(2) << gpa_ 
            << ', ' << id_ << endl;
    }

    float get_gpa() const {
        return gpa_;
    }

private:
    string first_, last_;
    float gpa_;
    int id_;

};

/* 
* For-each loop that uses reference so student isn't a copy of students
* Checks each student in students
* Appends every student with a gpa less than 1.0 to failing_students vector
*/
vector<Student> find_failing_students(const vector<Student> &students) {
    vector<Student> failing_students;
    for (const auto &student : students) {
        if (student.get_gpa() < 1.0) {
            failing_students.push_back(student);
        }
    }

    return failing_students;
}

/*
Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students) {
    for(auto it = students.cbegin(); it != students.cend(); it++){
        it -> print_info();
    }
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen. */
int main() {
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;

    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while (gpa < 0 || gpa > 4) {
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y' || repeat == 'y');
        cout << endl << "All students:" << endl;
        print_students(students);
        cout << endl << "Failing students:";
        auto failing_students = find_failing_students(students);
        if(failing_students.empty()) { // Checks if find_failing_students returns an empty vector, If empty returns true
            cout << " None" << endl; // Prints a space and the word 'None' on the same line if no students are failing.
        } else {
            cout << endl;
            print_students(failing_students); // Prints each failing student on a separate line.
        }
    return 0;
}
