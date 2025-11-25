#include "Functions.h"
#include <iostream>
using namespace std;

FunctionModule::FunctionModule() {
}

void FunctionModule::assignStudentToCourse(const string& student, const string& course)
{
    studentToCourse.addMapping(student, course);
}

void FunctionModule::assignCourseToFaculty(const string& course, const string& faculty)
{
    courseToFaculty.addMapping(course, faculty);
}

void FunctionModule::assignFacultyToRoom(const string& faculty, const string& room)
{
    facultyToRoom.addMapping(faculty, room);
}

void FunctionModule::verifyInjectivity(const string& functionName)
{
    if (functionName == "StudentToCourse")
    {
        cout << (studentToCourse.isInjective() ? "Injective\n" : "Not Injective\n");
    }
    else if (functionName == "CourseToFaculty")
    {
        cout << (courseToFaculty.isInjective() ? "Injective\n" : "Not Injective\n");
    }
    else if (functionName == "FacultyToRoom")
    {
        cout << (facultyToRoom.isInjective() ? "Injective\n" : "Not Injective\n");
    }
}

void FunctionModule::verifySurjectivity(const string& functionName) {
    // Example codomain for demo 
    string codomain[] = { "A", "B", "C" };
    int size = 3;

    if (functionName == "StudentToCourse")
    {
        cout << (studentToCourse.isSurjective(codomain, size) ? "Surjective\n" : "Not Surjective\n");
    }
    else if (functionName == "CourseToFaculty")
    {
        cout << (courseToFaculty.isSurjective(codomain, size) ? "Surjective\n" : "Not Surjective\n");
    }
    else if (functionName == "FacultyToRoom")
    {
        cout << (facultyToRoom.isSurjective(codomain, size) ? "Surjective\n" : "Not Surjective\n");
    }
}

void FunctionModule::testFunctionComposition() {
    cout << "Function composition test demo" << endl;
}

void FunctionModule::testInverseFunction() {
    cout << "Function inverse test demo" << endl;
}

void FunctionModule::displayAllFunctions() const {
    cout << endl << "Student -> Course : ";
    studentToCourse.display();
    cout << endl;
    cout << "Course -> Faculty : ";
    courseToFaculty.display();
    cout << endl;
    cout << "Faculty -> Room : ";
    facultyToRoom.display();
    cout << endl;
}
