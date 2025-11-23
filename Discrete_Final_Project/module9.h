#pragma once
#ifndef MODULE9_H
#define MODULE9_H
#include <iostream>
#include <string>
using namespace std;

#define MAX_CONFLICTS 100
#define MAX_ROOMS 50
#define MAX_CREDITS 21
#define MAX_COURSES 50
#define MAX_STUDENTS 200
#define MAX_FACULTY 50
#define MAX_PREREQS_PER_COURSE 10
#define MAX_ENROLLED_PER_STUDENT 10
#define MAX_ASSIGNED_PER_FACULTY 10

struct Course {
	string code;
	string name;
	int credits;
	string prerequisites[MAX_PREREQS_PER_COURSE];
	int prereqCount;
};

struct Student {
	string name;
	string completedCourses[MAX_COURSES];
	int completedCount;
	string enrolledCourses[MAX_ENROLLED_PER_STUDENT];
	int enrolledCount;
};

struct Faculty {
	string name;
	string assignedCourses[MAX_ASSIGNED_PER_FACULTY];
	int assignedCount;
};

struct ConsistencyReport {
	string conflictLog[MAX_CONFLICTS];
	int conflictCount;
};

class ConsistencyChecker {
	private:
		ConsistencyReport report;
public:
	ConsistencyChecker();
		void logConflict(const string& conflict);
		void clearReport();
		bool checkMissingPrereqs(const Course& course, const Student& student);
		bool checkRoomConflict(const string courses[], const string rooms[], int count);
		bool checkFacultyConflict(const string courses[], const string faculty[], int count);
		bool checkOverload(int totalCredits);
		const ConsistencyReport& getReport() const;
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
