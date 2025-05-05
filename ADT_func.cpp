#include "header/FADT_headers.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

// Function to save assignments to a file
void saveAssignments(const vector<Assignment>& assignments, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to open file for writing: " << filename << endl;
        return;
    }
    for (const auto& assignment : assignments) {
        // Store the date in ISO format YYYY-MM-DD instead of raw time_t
        outFile << assignment.getSubject() << "|"
                << assignment.getName() << "|"
                << formatDate(assignment.getDueDate()) << endl;
    }
    outFile.close();
}

// Function to load assignments from a file
vector<Assignment> loadAssignments(const string& filename) {
    vector<Assignment> assignments;
    ifstream inFile(filename);
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string subject, name, dueDateStr;
        getline(ss, subject, '|');
        getline(ss, name, '|');
        getline(ss, dueDateStr);

        // Parse the date from YYYY-MM-DD format
        int year, month, day;
        sscanf(dueDateStr.c_str(), "%d-%d-%d", &year, &month, &day);
        time_t dueDate = createDueDate(year, month, day);

        assignments.push_back(Assignment(subject, name, dueDate));
    }
    inFile.close();

    return assignments;
}

Assignment::Assignment(string sub, string nm, time_t due)
    : subject(sub), name(nm), dueDate(due) {}

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

time_t createDueDate(int year, int month, int day) {
    tm tmStruct = {0};
    tmStruct.tm_year = year - 1900;
    tmStruct.tm_mon = month - 1;
    tmStruct.tm_mday = day;
    tmStruct.tm_hour = 12; // Set to noon to avoid timezone issues
    return mktime(&tmStruct);
}

// Function to check if a date is in the past
bool isDateInPast(time_t date) {
    time_t now = time(nullptr);
    // Convert to local time structures to compare just dates
    tm* date_tm = localtime(&date);
    tm* now_tm = localtime(&now);

    // Reset hours, minutes, seconds to compare dates only
    date_tm->tm_hour = 0;
    date_tm->tm_min = 0;
    date_tm->tm_sec = 0;
    now_tm->tm_hour = 0;
    now_tm->tm_min = 0;
    now_tm->tm_sec = 0;

    // Convert back to time_t for comparison
    time_t date_day = mktime(date_tm);
    time_t now_day = mktime(now_tm);

    return date_day < now_day;
}

string formatDate(time_t date) {
    char buffer[80];
    tm* timeinfo = localtime(&date);
    strftime(buffer, 80, "%Y-%m-%d", timeinfo);
    return string(buffer);
}

void checkReminders(const vector<Assignment>& assignments) {
    time_t now = time(nullptr);
    time_t tomorrow = now + 24 * 60 * 60;
    cout << "\n====== REMINDERS =======\n";
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
    cout << "========================\n";
}

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
