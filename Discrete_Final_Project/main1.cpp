#include <iostream>
#include <string>
#include "Course.h"
#include "Groups.h"

using namespace std;

void runCourseModule() {
    CourseScheduler scheduler;
    int choice;

    do {
        cout << "\n=== Course & Scheduling Module ===\n";
        cout << "1. Add Course\n";
        cout << "2. Add Prerequisite\n";
        cout << "3. Validate Prerequisites\n";
        cout << "4. Display Topological Order\n";
        cout << "5. Generate Valid Sequences\n";
        cout << "6. Display All Courses\n";
        cout << "7. Load Sample Data\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string code, name;
            int credits;
            cout << "Enter course code: ";
            getline(cin, code);
            cout << "Enter course name: ";
            getline(cin, name);
            cout << "Enter credits: ";
            cin >> credits;
            cin.ignore();
            scheduler.addCourse(code, name, credits);
            cout << "Course added successfully!\n";
        }
        else if (choice == 2) {
            string course, prereq;
            cout << "Enter course code: ";
            getline(cin, course);
            cout << "Enter prerequisite code: ";
            getline(cin, prereq);
            scheduler.addPrerequisite(course, prereq);
            cout << "Prerequisite added!\n";
        }
        else if (choice == 3) {
            scheduler.validatePrerequisites();
        }
        else if (choice == 4) {
            scheduler.displayTopologicalOrder();
        }
        else if (choice == 5) {
            int maxCourses;
            cout << "Enter maximum courses in sequence: ";
            cin >> maxCourses;
            scheduler.generateAllValidSequences(maxCourses);
        }
        else if (choice == 6) {
            scheduler.displayAllCourses();
        }
        else if (choice == 7) {
            // Load sample data
            scheduler.addCourse("CS101", "Intro to CS", 3);
            scheduler.addCourse("CS102", "Programming Fundamentals", 3);
            scheduler.addCourse("CS201", "Data Structures", 3);
            scheduler.addCourse("CS202", "OOP", 3);
            scheduler.addCourse("CS301", "Algorithms", 3);

            scheduler.addPrerequisite("CS102", "CS101");
            scheduler.addPrerequisite("CS201", "CS102");
            scheduler.addPrerequisite("CS202", "CS102");
            scheduler.addPrerequisite("CS301", "CS201");

            cout << "Sample data loaded!\n";
        }

    } while (choice != 0);
}

void runGroupModule() {
    GroupManager manager;
    int choice;

    do {
        cout << "\n=== Student Group Combination Module ===\n";
        cout << "1. Add Student\n";
        cout << "2. Create Project Groups\n";
        cout << "3. Create Lab Sessions\n";
        cout << "4. Assign to Electives\n";
        cout << "5. Display All Students\n";
        cout << "6. Display All Groups\n";
        cout << "7. Calculate Combinations\n";
        cout << "8. Load Sample Students\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string id, name;
            int semester;
            cout << "Enter student ID: ";
            getline(cin, id);
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter semester: ";
            cin >> semester;
            cin.ignore();
            manager.addStudent(id, name, semester);
            cout << "Student added!\n";
        }
        else if (choice == 2) {
            int groupSize;
            cout << "Enter group size: ";
            cin >> groupSize;
            manager.createProjectGroups(groupSize);
        }
        else if (choice == 3) {
            int labSize;
            cout << "Enter students per lab: ";
            cin >> labSize;
            manager.createLabSessions(labSize);
        }
        else if (choice == 4) {
            string elective;
            int maxStudents;
            cin.ignore();
            cout << "Enter elective name: ";
            getline(cin, elective);
            cout << "Enter max students: ";
            cin >> maxStudents;
            manager.assignToElectives(elective, maxStudents);
        }
        else if (choice == 5) {
            manager.displayAllStudents();
        }
        else if (choice == 6) {
            manager.displayAllGroups();
        }
        else if (choice == 7) {
            int total, groupSize;
            cout << "Enter total students: ";
            cin >> total;
            cout << "Enter group size: ";
            cin >> groupSize;
            cout << "Possible combinations: "
                << manager.calculatePossibleCombinations(total, groupSize) << endl;
        }
        else if (choice == 8) {
            // Sample students
            manager.addStudent("24F-3001", "Ali Ahmed", 3);
            manager.addStudent("24F-3002", "Sara Khan", 3);
            manager.addStudent("24F-3003", "Hassan Ali", 3);
            manager.addStudent("24F-3004", "Fatima Noor", 3);
            manager.addStudent("24F-3005", "Omar Siddiqui", 3);
            manager.addStudent("24F-3006", "Ayesha Malik", 3);
            manager.addStudent("24F-3007", "Bilal Tariq", 3);
            manager.addStudent("24F-3008", "Zainab Riaz", 3);

            cout << "Sample students loaded!\n";
        }

    } while (choice != 0);
}

int main() {
    int choice;

    do {
        cout << "\n=== UNIDISC ENGINE - COURSE & GROUP MODULES ===\n";
        cout << "1. Course & Scheduling Module\n";
        cout << "2. Student Group Combination Module\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            runCourseModule();
            break;
        case 2:
            runGroupModule();
            break;
        case 0:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
