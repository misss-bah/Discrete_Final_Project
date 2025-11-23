#pragma once
#ifndef MODULE9_H
#define MODULE9_H
#include <iostream>
#include <string>

using namespace std;
#define MAX_COURSES 50
#define MAX_PREREQS 10	
#define MAX_STUDENTS 100	
#define MAX_ENROLLED_PER_STUDENT 10
#define MAX_CREDITS 21
#define MAX_FACULTY 50
#define MAX_ASSIGNED_PER_FACULTY 10
#define MAX_CONFLICTS 200

struct Course {
	string courseID;
	string room;
	string faculty;
	string prereqs[MAX_PREREQS];
	int prereqCount;
	int credits;
};

struct Student {
	string studentID;
	string enrolledCourses[MAX_ENROLLED_PER_STUDENT];
	int enrolledCount;
	int totalCredits;
};

struct Faculty {
	string facultyID;
	string assignedCourses[MAX_ASSIGNED_PER_FACULTY];
	int assignedCount;
};

class ConsistencyChecker {
	private:
	string conflictLog[MAX_CONFLICTS];
	int conflictCount;
public:
	ConsistencyChecker();
	void logConflict(const string& conflict);
	void clear();
	bool checkMissingPrereqs(const Course& course, const Student& student);
	bool checkRoomConflict(const Course courses[], int courseCount);
	bool checkFacultyConflict(const Course courses[], int courseCount);
	bool checkOverload(const Student& student);
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





#endif // !MODULE9_H

