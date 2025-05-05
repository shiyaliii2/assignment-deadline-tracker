#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "header/FADT_headers.h"
using namespace std;

// Define a constant for the filename
const string ASSIGNMENTS_FILE = "assignments.txt";

int main() {
    // Load existing assignments from file
    vector<Assignment> assignments = loadAssignments(ASSIGNMENTS_FILE);
    string choice;
    do {

        PrintMenu();
        getline(cin,choice);

        if(choice == "1"){
             string sub, name, dateInput;
                int year, month, day;
                system("cls");
                cout << "Enter subject: ";
                getline(cin, sub);
                cout << "Enter assignment name: ";
                getline(cin, name);

                // Accept date in YYYY-MM-DD format
                cout << "Enter due date (YYYY-MM-DD): ";
                getline(cin, dateInput);
                cout<<endl;
                // Parse the date string
                if (sscanf(dateInput.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
                    system("cls");
                    cout << "Invalid date format. Please use YYYY-MM-DD format.\n";
                    continue;
                }

                time_t due = createDueDate(year, month, day);
                time_t now = time(0);

                tm* now_tm = localtime(&now);
                now_tm->tm_hour = 0;
                now_tm->tm_min = 0;
                now_tm->tm_sec = 0;
                time_t today_start = mktime(now_tm);

                if (due < today_start) {
                    system("cls");
                    cout << "Error: Due date cannot be in the past. Please enter a present or future date.\n";
                    continue;
                }

                assignments.push_back(Assignment(sub, name, due));
                cout << "Assignment added!\n"<<endl;
                cout << "Due date set to: " << formatDate(due) << endl;

                // Save assignments every time a new one is added
                saveAssignments(assignments, ASSIGNMENTS_FILE);


        }else if(choice == "2"){
                cout << "\n======= ALL ASSIGNMENTS =========\n";
                if(assignments.empty()) {
                    cout << "\n  No assignments found.\n"<<endl;
                } else {
                    for (const auto& a : assignments) {
                        a.display();
                    }
                }
                cout << "==================================\n";

        } else if(choice == "3"){

            checkReminders(assignments);

        } else if(choice == "4"){
                saveAssignments(assignments, ASSIGNMENTS_FILE);
                cout << "Assignments saved. Goodbye!\n";
                break;
        }


        else{
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != "4");





    return 0;
}
