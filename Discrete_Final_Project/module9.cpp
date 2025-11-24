//#include"module9.h"
//
//ConsistencyModule::ConsistencyModule() {}
//void ConsistencyModule::runRoomCheckDemo() {
//	string courses[] = { "CS101", "MATH201", "ENG301", "HIST101" };
//	string rooms[] = { "RoomA", "RoomB", "RoomA", "RoomC" };
//	int count = 4;
//	checker.clearReport();
//	checker.checkRoomConflict(courses, rooms, count);
//	const ConsistencyReport& report = checker.getReport();
//	cout << "Room Conflict Check Report:\n";
//	for (int i = 0; i < report.conflictCount; i++) {
//		cout << report.conflictLog[i] << endl;
//	}
//}
//void ConsistencyModule::runFacultyCheckDemo() {
//	string courses[] = { "CS101", "MATH201", "ENG301", "HIST101" };
//	string faculty[] = { "Dr. Smith", "Dr. Jones", "Dr. Smith", "Dr. Brown" };
//	int count = 4;
//	checker.clearReport();
//	checker.checkFacultyConflict(courses, faculty, count);
//	const ConsistencyReport& report = checker.getReport();
//	cout << "Faculty Conflict Check Report:\n";
//	for (int i = 0; i < report.conflictCount; i++) {
//		cout << report.conflictLog[i] << endl;
//	}
//}
//void ConsistencyModule::runPrereqCheckDemo() {
//	Course course;
//	course.code = "CS201";
//	course.prereqCount = 2;
//	course.prerequisites[0] = "CS101";
//	course.prerequisites[1] = "MATH101";
//	Student student;
//	student.name = "Alice";
//	student.completedCount = 1;
//	student.completedCourses[0] = "CS101";
//	checker.clearReport();
//	checker.checkMissingPrereqs(course, student);
//	const ConsistencyReport& report = checker.getReport();
//	cout << "Prerequisite Check Report:\n";
//	for (int i = 0; i < report.conflictCount; i++) {
//		cout << report.conflictLog[i] << endl;
//	}
//}
//void ConsistencyModule::runOverloadCheckDemo() {
//	int totalCredits = 24;
//	checker.clearReport();
//	checker.checkOverload(totalCredits);
//	const ConsistencyReport& report = checker.getReport();
//	cout << "Overload Check Report:\n";
//	for (int i = 0; i < report.conflictCount; i++) {
//		cout << report.conflictLog[i] << endl;
//	}
//}
//ConsistencyChecker::ConsistencyChecker() {
//	report.conflictCount = 0;
//}
//void ConsistencyChecker::logConflict(const string& conflict) {
//	if (report.conflictCount < MAX_CONFLICTS) {
//		report.conflictLog[report.conflictCount++] = conflict;
//	}
//}
//void ConsistencyChecker::clearReport() {
//	report.conflictCount = 0;
//}
//bool ConsistencyChecker::checkMissingPrereqs(const Course& course, const Student& student) {
//	for (int i = 0; i < course.prereqCount; i++) {
//		bool found = false;
//		for (int j = 0; j < student.completedCount; j++) {
//			if (course.prerequisites[i] == student.completedCourses[j]) {
//				found = true;
//				break;
//			}
//		}
//		if (!found) {
//			logConflict("Missing prerequisite for " + course.code + ": " + course.prerequisites[i]);
//		}
//	}
//	return report.conflictCount == 0;
//}
//bool ConsistencyChecker::checkRoomConflict(const string courses[], const string rooms[], int count) {
//	for (int i = 0; i < count; i++) {
//		for (int j = i + 1; j < count; j++) {
//			if (rooms[i] == rooms[j]) {
//				logConflict("Room conflict: " + courses[i] + " and " + courses[j] +
//					" both assigned to room " + rooms[i]);
//			}
//		}
//	}
//	return report.conflictCount == 0;
//}
//bool ConsistencyChecker::checkFacultyConflict(const string courses[], const string faculty[], int count) {
//	for (int i = 0; i < count; i++) {
//		for (int j = i + 1; j < count; j++) {
//			if (faculty[i] == faculty[j]) {
//				logConflict("Faculty conflict: " + faculty[i] +
//					" assigned to both " + courses[i] + " and " + courses[j]);
//			}
//		}
//	}
//	return report.conflictCount == 0;
//}
//bool ConsistencyChecker::checkOverload(int totalCredits) {
//	if (totalCredits > 21) {
//		logConflict("Student overload: " + to_string(totalCredits) + " credits exceeds limit.");
//		return false;
//	}
//	return true;
//}
//const ConsistencyReport& ConsistencyChecker::getReport() const {
//	return report;
//}
//
//
//
