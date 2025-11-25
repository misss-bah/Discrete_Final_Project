#include "Consistency.h"

ConsistencyChecker::ConsistencyChecker() : conflictCount(0) {}

void ConsistencyChecker::logConflict(const string& conflict) {
    if (conflictCount < MAX_CONFLICTS) {
        conflictLog[conflictCount++] = conflict;
    }
}

void ConsistencyChecker::clear() {
    conflictCount = 0;
}

bool ConsistencyChecker::checkMissingPrereqs(const string course, const string prereqs[],
    int prereqCount, const string completed[],
    int completedCount)
{
    for (int i = 0; i < prereqCount; i++) {
        bool found = false;
        for (int j = 0; j < completedCount; j++) {
            if (prereqs[i] == completed[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            logConflict("Missing prerequisite: " + prereqs[i] + " for course " + course);
        }
    }
    return conflictCount == 0;
}

bool ConsistencyChecker::checkRoomConflict(const string courses[], const string rooms[], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (rooms[i] == rooms[j]) {
                logConflict("Room conflict: " + courses[i] + " and " + courses[j] +
                    " both assigned to room " + rooms[i]);
            }
        }
    }
    return conflictCount == 0;
}

bool ConsistencyChecker::checkFacultyConflict(const string courses[], const string faculty[], int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (faculty[i] == faculty[j]) {
                logConflict("Faculty conflict: " + faculty[i] +
                    " assigned to both " + courses[i] + " and " + courses[j]);
            }
        }
    }
    return conflictCount == 0;
}

bool ConsistencyChecker::checkOverload(int totalCredits) {
    if (totalCredits > 21) {
        logConflict("Student overload: " + to_string(totalCredits) + " credits exceeds limit.");
        return false;
    }
    return true;
}

void ConsistencyChecker::displayConflicts() const {
    if (conflictCount == 0) {
        cout << "No conflicts found. System is consistent.\n";
        return;
    }
    cout << "\n=== CONSISTENCY CONFLICTS ===\n";
    for (int i = 0; i < conflictCount; i++) {
        cout << conflictLog[i] << endl;
    }
    cout << "==============================\n";
}

ConsistencyModule::ConsistencyModule() {}

void ConsistencyModule::runRoomCheckDemo() {
    string courses[3] = { "CS101", "CS201", "CS301" };
    string rooms[3] = { "R1", "R1", "R3" };
    checker.checkRoomConflict(courses, rooms, 3);
    checker.displayConflicts();
}

void ConsistencyModule::runFacultyCheckDemo() {
    string courses[3] = { "CS101", "CS201", "CS202" };
    string faculty[3] = { "Dr.Ali", "Dr.Ali", "Dr.Sara" };
    checker.checkFacultyConflict(courses, faculty, 3);
    checker.displayConflicts();
}

void ConsistencyModule::runPrereqCheckDemo() {
    string prereqs[2] = { "CS101", "CS102" };
    string completed[1] = { "CS101" };
    checker.checkMissingPrereqs("CS201", prereqs, 2, completed, 1);
    checker.displayConflicts();
}

void ConsistencyModule::runOverloadCheckDemo() {
    checker.checkOverload(24);
    checker.displayConflicts();
}
