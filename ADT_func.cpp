#include "header/FADT_headers.h"
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>

// Function to save assignments to a file
void saveAssignments(const vector<Assignment>& assignments, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }

    for (const auto& assignment : assignments) {
        outFile << assignment.getSubject() << "|"
                << assignment.getName() << "|"
                << assignment.getDueDate() << endl;
    }

    outFile.close();
    cout << "Assignments saved to " << filename << endl;
}

// Function to load assignments from a file
vector<Assignment> loadAssignments(const string& filename) {
    vector<Assignment> assignments;
    ifstream inFile(filename);

    if (!inFile) {
        cout << "No existing assignments file found. Starting with empty list." << endl;
        return assignments;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string subject, name, dueDateStr;
        time_t dueDate;

        getline(ss, subject, '|');
        getline(ss, name, '|');
        string timeStr;
        getline(ss, timeStr);

        // Convert string to time_t
        dueDate = stoll(timeStr);

        assignments.push_back(Assignment(subject, name, dueDate));
    }

    inFile.close();
    cout << "Loaded " << assignments.size() << " assignments from " << filename << endl;

    return assignments;
}
//Constructor
Assignment::Assignment(string sub, string nm, time_t due)
    : subject(sub), name(nm), dueDate(due) {}
//Getters
string Assignment::getSubject() const {
    return subject;
}

string Assignment::getName() const {
    return name;
}

time_t Assignment::getDueDate() const {
    return dueDate;
}

void Assignment::display() const {
    cout << subject << " - " << name << " (Due: " << formatDate(dueDate) << ")\n";
}
//Di ko alam to pre basta parang icacalculate o iseset yung date from year 1900 parang ganon perds
time_t createDueDate(int year, int month, int day) {
    tm tmStruct = {0};
    tmStruct.tm_year = year - 1900;
    tmStruct.tm_mon = month - 1;
    tmStruct.tm_mday = day;
    return mktime(&tmStruct);
}

string formatDate(time_t date) {
    char buffer[80];
    tm* timeinfo = localtime(&date);
    strftime(buffer, 80, "%Y-%m-%d", timeinfo);
    return string(buffer);
}


//Check reminders 
void checkReminders(const vector<Assignment>& assignments) {
    time_t now = time(nullptr);
    time_t tomorrow = now + 24 * 60 * 60;

    cout << "\n--- REMINDERS ---\n";
    for (const auto& assignment : assignments) {
        time_t due = assignment.getDueDate();
        if (due < now) {
            cout << "!!! PAST DUE !!! " << assignment.getSubject()
                 << " - " << assignment.getName() << " was due on "
                 << formatDate(due) << endl;
        } else if (due < tomorrow) {
            cout << "!!! DUE TOMORROW !!! " << assignment.getSubject()
                 << " - " << assignment.getName() << endl;
        } else if (due < now + 3 * 24 * 60 * 60) {
            cout << "Due soon (3 days): " << assignment.getSubject()
                 << " - " << assignment.getName() << " (due "
                 << formatDate(due) << ")" << endl;
        }
    }
    cout << "----------------\n";
}
//Print display
void PrintMenu(){

    cout << "\n============================================\n";
    cout << "       ASSIGNMENT DEADLINE TRACKER\n";
    cout << "============================================\n";
    cout << "1. Add new assignment\n";
    cout << "2. View all assignments\n";
    cout << "3. Check reminders\n";
    cout << "4. Save and exit\n";
    cout << "============================================\n"<<endl;
    cout << "Enter your choice: ";

}
