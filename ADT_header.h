#ifndef FADT_HEADERS_H
#define FADT_HEADERS_H
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Assignment {
private:
    string subject;
    string name;
    time_t dueDate;
public:
    Assignment(string sub, string nm, time_t due);
    string getSubject() const;
    string getName() const;
    time_t getDueDate() const;
    void display() const;
};

time_t createDueDate(int year, int month, int day);
string formatDate(time_t date);
bool isDateInPast(time_t date);
void checkReminders(const vector<Assignment>& assignments);
void PrintMenu();

// File I/O functions
void saveAssignments(const vector<Assignment>& assignments, const string& filename);
vector<Assignment> loadAssignments(const string& filename);

#endif // FADT_HEADERS_H
