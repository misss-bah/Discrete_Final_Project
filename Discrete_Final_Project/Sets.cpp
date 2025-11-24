#include "Sets.h"
using namespace std;

SetModule::SetModule() {}

void SetModule::addStudent(const string& student) {
    students.add(student);
    cout << "The Student added to set : " << student << endl;
}

void SetModule::addCourse(const string& course) {
    courses.add(course);
    cout << "The Course added to set : " << course << endl;
}

void SetModule::addFaculty(const string& facultyMember) {
    faculty.add(facultyMember);
    cout << "The Faculty added to set : " << facultyMember << endl;
}

void SetModule::addRoom(const string& room) {
    rooms.add(room);
    cout << "The Room added to set : " << room << endl;
}

void SetModule::findStudentsInBothCourses(const string& course1, const string& course2)
{ 

    // Simulated: Create two sets of students enrolled in each course
    Set<string> course1Students;
    Set<string> course2Students;

    // Adding some sample students
    for (int i = 0; i < students.getSize(); i++)
    {
        if (i % 2 == 0)
            course1Students.add(students.getElement(i));
        if (i % 3 == 0)
            course2Students.add(students.getElement(i));
    }

    Set<string> intersection = course1Students.intersectionWith(course2Students);
    cout << endl;
    cout << "=== Students in both " << course1 << " and " << course2 << " ===" << endl;
    cout << "The Course 1 students : ";
    course1Students.display();
    cout << endl;
    cout << "The Course 2 students : ";
    course2Students.display();
    cout << endl;
    cout << "Intersection (both courses) : ";
    intersection.display();
    cout << endl;
}

void SetModule::demonstrateSetOperations() {
    cout << endl;
    cout << "=== SET OPERATIONS DEMONSTRATION ===" << endl;

    Set<string> setA;
    setA.add("SE101");
    setA.add("SE201");
    setA.add("SE301");

    Set<string> setB;
    setB.add("SE201");
    setB.add("SE301");
    setB.add("SE401");

    cout << endl<< "Set A : ";
    setA.display();
    cout << endl<< "Set B : ";
    setB.display();

    Set<string> unionSet = setA.unionWith(setB);
    cout << endl << endl;
    cout << "A ∪ B (Union) : ";
    unionSet.display();

    Set<string> intersectionSet = setA.intersectionWith(setB);
    cout << endl<< "A ∩ B (Intersection) : ";
    intersectionSet.display();

    Set<string> differenceSet = setA.differenceWith(setB);
    cout << endl<<"A - B (Difference) : ";
    differenceSet.display();

    Set<string> symDiffSet = setA.symmetricDifference(setB);
    cout << endl<<"A Δ B (Symmetric Difference) : ";
    symDiffSet.display();

    cout << endl << endl;
    cout << "Set Properties :" << endl;
    cout << "A ⊆ B? " << (setA.isSubsetOf(setB) ? "Yes" : "No") << endl;
    cout << "B ⊆ A? " << (setB.isSubsetOf(setA) ? "Yes" : "No") << endl;
    cout << "A = B? " << (setA.isEqual(setB) ? "Yes" : "No") << endl;
    cout << endl;
}

void SetModule::generatePowerSet(const string& setType) {
    cout << endl<<"=== POWER SET GENERATION ===" << endl;
    cout << "Generating power set for " << setType << endl;

    Set<string> baseSet;
    baseSet.add("A");
    baseSet.add("B");
    baseSet.add("C");

    cout << "Base Set : ";
    baseSet.display();
    cout << endl<<endl<<"Power Set :" << endl;

    int n = baseSet.getSize();
    int powerSetSize = 1 << n; // 2^n

    for (int i = 0; i < powerSetSize; i++) {
        cout << "{ ";
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j)) {
                cout << baseSet.getElement(j) << " ";
            }
        }
        cout << "}" << endl;
    }

    cout << endl<<"Total subsets : " << powerSetSize << endl;
}

void SetModule::displayAllSets() const {
    cout << endl<<"=== ALL SETS ===" << endl;

    cout << endl<<"Students : ";
    students.display();
    cout << " (Size : " << students.getSize() << ")" << endl;

    cout << "Courses : ";
    courses.display();
    cout << " (Size : " << courses.getSize() << ")" << endl;

    cout << "Faculty : ";
    faculty.display();
    cout << " (Size : " << faculty.getSize() << ")" << endl;

    cout << "Rooms : ";
    rooms.display();
    cout << " (Size : " << rooms.getSize() << ")" << endl;
}