#include <iostream>
#include "Functions.h"
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
    cout << "\n=== Function Composition Test ===" << endl;
    cout << "Composing: f(x) = courseToFaculty, g(x) = facultyToRoom" << endl;
    cout << "Result: (g ∘ f)(course) = room assignment" << endl;

    Function<string, string> composed = courseToFaculty.compose(facultyToRoom);
    cout << "Composed function: ";
    composed.display();
    cout << endl;
}

void FunctionModule::testInverseFunction() {
    cout << "\n=== Function Inverse Test ===" << endl;

    if (courseToFaculty.isInjective()) {
        cout << "courseToFaculty is injective - inverse exists" << endl;
        Function<string, string> inverse = courseToFaculty.inverse();
        cout << "Inverse function (faculty → course): ";
        inverse.display();
        cout << endl;
    }
    else {
        cout << "courseToFaculty is NOT injective - inverse does not exist" << endl;
    }

    cout << "\nBijection Test: ";
    string codomain[] = { "Dr.A", "Dr.B", "Dr.C" };
    if (courseToFaculty.isBijective(codomain, 3)) {
        cout << "Function is bijective (1-1 and onto)" << endl;
    }
    else {
        cout << "Function is NOT bijective" << endl;
    }
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
