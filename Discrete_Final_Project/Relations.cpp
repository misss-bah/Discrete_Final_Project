#include "Relations.h"

RelationModule::RelationModule() {}

void RelationModule::addStudentCourse(const string& student, const string& course) {
    studentCourse.addPair(student, course);
}

void RelationModule::addFacultyCourse(const string& faculty, const string& course) {
    facultyCourse.addPair(faculty, course);
}

void RelationModule::addCourseRoom(const string& course, const string& room) {
    courseRoom.addPair(course, room);
}

void RelationModule::checkRelationProperties() {
    string domain[3] = { "A", "B", "C" };
    int size = 3;

    cout << endl;
    cout << "Checking Relation Properties for Student -> Course :" << endl;
    cout << "Reflexive : " << (studentCourse.isReflexive(domain, size) ? "Yes" : "No") << endl;
    cout << "Symmetric : " << (studentCourse.isSymmetric() ? "Yes" : "No") << endl;
    cout << "Transitive : " << (studentCourse.isTransitive() ? "Yes" : "No") << endl;
    cout << "Antisymmetric : " << (studentCourse.isAntisymmetric() ? "Yes" : "No") << endl;
}

void RelationModule::findIndirectEnrollments() {
    cout << endl;
    cout << "Indirect Enrollment Detection (Student . CourseRoom) :" << endl;

    Relation<string, string> composed = studentCourse.compose(courseRoom);
    composed.display();
    cout << endl;
}

void RelationModule::composeRelations() {
    cout << endl;
    cout << "Composition: (StudentCourse . FacultyCourse) :" << endl;

    Relation<string, string> R = studentCourse.compose(facultyCourse);
    R.display();
    cout << endl;
}

void RelationModule::displayAllRelations() const {
    cout << endl;
    cout << "Student -> Course : ";
    studentCourse.display();
    cout << endl;
    cout << "Faculty -> Course : ";
    facultyCourse.display();
    cout << endl;
    cout << "Course -> Room : ";
    courseRoom.display();

    cout << endl;
}
