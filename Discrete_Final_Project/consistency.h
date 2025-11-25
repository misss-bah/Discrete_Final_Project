#ifndef CONSISTENCY_H
#define CONSISTENCY_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_CONFLICTS = 200;

class ConsistencyChecker {
private:
    string conflictLog[MAX_CONFLICTS];
    int conflictCount;

public:
    ConsistencyChecker();

    void logConflict(const string& conflict);
    void clear();

    bool checkMissingPrereqs(const string course, const string prereqs[], int prereqCount,
        const string completed[], int completedCount);

    bool checkRoomConflict(const string courses[], const string rooms[], int count);
    bool checkFacultyConflict(const string courses[], const string faculty[], int count);

    bool checkOverload(int totalCredits);

    void displayConflicts() const;
    bool isConsistent() const { return conflictCount == 0; }
};

class ConsistencyModule {
private:
    ConsistencyChecker checker;

public:
    ConsistencyModule();

    void runRoomCheckDemo();
    void runFacultyCheckDemo();
    void runPrereqCheckDemo();
    void runOverloadCheckDemo();
};

#endif
