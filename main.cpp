#include <iostream>
#include <vector>
#include <fstream>
#include "header/FADT_headers.h"
using namespace std;

// Define a constant for the filename
const string ASSIGNMENTS_FILE = "assignments.dat";

int main() {
    // Load existing assignments from file
    vector<Assignment> assignments = loadAssignments(ASSIGNMENTS_FILE);

    int choice;
    do {
        PrintMenu();
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1: {
                string sub, name;
                int year, month, day;
                cout << "Enter subject: ";
                getline(cin, sub);
                cout << "Enter assignment name: ";
                getline(cin, name);
                cout << "Enter due date (YYYY MM DD): ";
                cin >> year >> month >> day;
                time_t due = createDueDate(year, month, day);
                assignments.push_back(Assignment(sub, name, due));
                cout << "Assignment added!\n";

                // Save assignments every time a new one is added
                saveAssignments(assignments, ASSIGNMENTS_FILE);
                break;
            }
            case 2: {
                cout << "\n--- ALL ASSIGNMENTS ---\n";
                if(assignments.empty()) {
                    cout << "No assignments found.\n";
                } else {
                    for (const auto& a : assignments) {
                        a.display();
                    }
                }
                cout << "----------------------\n";
                break;
            }
            case 3: {
                checkReminders(assignments);
                break;
            }
            case 4: {
                // Save before exiting
                saveAssignments(assignments, ASSIGNMENTS_FILE);
                cout << "Assignments saved. Goodbye!\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 4);
    return 0;
}

