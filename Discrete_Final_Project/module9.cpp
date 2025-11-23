#include"module9.h"
#include<string>

ConsistencyChecker::ConsistencyChecker() : conflictCount(0) {}
void ConsistencyChecker::logConflict(const string& conflict) {
	if (conflictCount < MAX_CONFLICTS) {
		conflictLog[conflictCount++] = conflict;
	}
}

void ConsistencyChecker::clear() {
	conflictCount = 0;
}

bool ConsistencyChecker::checkMissingPrereqs(const Course& course, const Student& student) {
	for (int i = 0; i < course.prereqCount; i++) {
		bool found = false;
		for (int j = 0; j < student.enrolledCount; j++) {
			if (course.prereqs[i] == student.enrolledCourses[j]) {
				found = true;
				break;
			}
		}
		if (!found) {
			logConflict("Missing prerequisite: " + course.prereqs[i] + " for course " + course.courseID + " for student " + student.studentID);
		}
	}
	return conflictCount == 0;
}

bool ConsistencyChecker::checkRoomConflict(const Course courses[], int courseCount) {
	for (int i = 0; i < courseCount; i++) {
		for (int j = i + 1; j < courseCount; j++) {
			if (courses[i].room == courses[j].room) {
				logConflict("Room conflict: " + courses[i].courseID + " and " + courses[j].courseID +
					" both assigned to room " + courses[i].room);
			}
		}
	}
	return conflictCount == 0;
}

bool ConsistencyChecker::checkFacultyConflict(const Course courses[], int courseCount) {
	for (int i = 0; i < courseCount; i++) {
		for (int j = i + 1; j < courseCount; j++) {
			if (courses[i].faculty == courses[j].faculty) {
				logConflict("Faculty conflict: " + courses[i].faculty +
					" assigned to both " + courses[i].courseID + " and " + courses[j].courseID);
			}
		}
	}
	return conflictCount == 0;
}

bool ConsistencyChecker::checkOverload(const Student& student) {
	if (student.totalCredits > MAX_CREDITS) {
		logConflict("Student overload: " + student.studentID + " has " + to_string(student.totalCredits) + " credits, exceeds limit of " + to_string(MAX_CREDITS) + ".");
	}
	return conflictCount == 0;
}

void ConsistencyChecker::displayConflicts() const {
	for (int i = 0; i < conflictCount; i++) {
		cout << conflictLog[i] << endl;
	}
}

ConsistencyModule::ConsistencyModule() {}
void ConsistencyModule::runRoomCheckDemo() {
	Course courses[3] = {
		{"CS101", "RoomA", "ProfA", {}, 0, 3},
		{"CS102", "RoomB", "ProfB", {}, 0, 3},
		{"CS103", "RoomA", "ProfC", {}, 0, 3}
	};
	checker.clear();
	checker.checkRoomConflict(courses, 3);
	checker.displayConflicts();
}

void ConsistencyModule::runFacultyCheckDemo() {
	Course courses[3] = {
		{"CS201", "RoomC", "ProfX", {}, 0, 3},
		{"CS202", "RoomD", "ProfY", {}, 0, 3},
		{"CS203", "RoomE", "ProfX", {}, 0, 3}
	};
	checker.clear();
	checker.checkFacultyConflict(courses, 3);
	checker.displayConflicts();
}

void ConsistencyModule::runPrereqCheckDemo() {
	Course course = { "CS301", "RoomF", "ProfZ", {"CS101", "CS102"}, 2, 3 };
	Student student = { "S123", {"CS101"}, 1, 3 };
	checker.clear();
	checker.checkMissingPrereqs(course, student);
	checker.displayConflicts();
}

void ConsistencyModule::runOverloadCheckDemo() {
	Student student = { "S456", {"CS401", "CS402", "CS403", "CS404", "CS405", "CS406", "CS407"}, 7, 24 };
	checker.clear();
	checker.checkOverload(student);
	checker.displayConflicts();
}
