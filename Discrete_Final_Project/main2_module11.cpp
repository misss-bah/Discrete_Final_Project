#include <iostream>
#include <string>
#include "Courses.h"
#include "Groups.h"
#include "Induction.h"
#include "LogicEngine.h"
#include "Sets.h"
#include "Relations.h"
#include "Functions.h"
#include "Proofs.h"
#include "Consistency.h"
#include "Benchmark.h"

using namespace std;

void displayMainMenu() {
    cout << "\n";
    cout << "======================================================\n";
    cout << "|        UNIDISC ENGINE - FAST University            |\n";
    cout << "|    Discrete Mathematics Computational Framework    |\n";
    cout << "======================================================\n";

    cout << "\n";
    cout << "1.  Course & Scheduling Module\n";
    cout << "2.  Student Group Combination Module\n";
    cout << "3.  Induction & Strong Induction Module\n";
    cout << "4.  Logic & Inference Engine\n";
    cout << "5.  Set Operations Module\n";
    cout << "6.  Relations Module\n";
    cout << "7.  Functions Module\n";
    cout << "8.  Automated Proof & Verification\n";
    cout << "9.  Consistency Checker\n";
    cout << "10. Algorithmic Efficiency & Benchmarking\n";
    cout << "11. Run All Demos\n";
    cout << "12. Exit\n";
    cout << "\nEnter your choice: ";
}

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
            scheduler.addCourse("CS101", "Introduction to CS", 3);
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

void runInductionModule() {
    InductionModule indModule;
    int choice;

    do {
        cout << "\n=== Induction & Strong Induction Module ===\n";
        cout << "1. Add Course with Prerequisites\n";
        cout << "2. Verify Can Take Course\n";
        cout << "3. Verify Indirect Prerequisites\n";
        cout << "4. Demonstrate Base Case\n";
        cout << "5. Demonstrate Inductive Step\n";
        cout << "6. Run Complete Induction Example\n";
        cout << "7. Display Course Prerequisites\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string course;
            int prereqCount;
            cout << "Enter course name: ";
            getline(cin, course);
            cout << "Enter number of prerequisites: ";
            cin >> prereqCount;
            cin.ignore();

            string* prereqs = new string[prereqCount];
            for (int i = 0; i < prereqCount; i++) {
                cout << "Enter prerequisite " << (i + 1) << ": ";
                getline(cin, prereqs[i]);
            }

            indModule.addCourseWithPrereqs(course, prereqs, prereqCount);
            delete[] prereqs;
            cout << "Course added with prerequisites!\n";
        }
        else if (choice == 4) {
            indModule.demonstrateBaseCase();
        }
        else if (choice == 5) {
            indModule.demonstrateInductiveStep();
        }
        else if (choice == 6) {
            indModule.runInductionExample();
        }
        else if (choice == 7) {
            indModule.displayCoursePrerequisites();
        }

    } while (choice != 0);
}

void runAllDemos() {
    cout << "\n====================================================\n";
    cout << "|         RUNNING ALL MODULE DEMONSTRATIONS        |\n";
    cout << "====================================================\n";

    // Course Demo
    cout << "\n\n>>> DEMO 1: COURSE & SCHEDULING <<<\n";
    CourseScheduler scheduler;
    scheduler.addCourse("CS101", "Intro to CS", 3);
    scheduler.addCourse("CS201", "Data Structures", 3);
    scheduler.addCourse("CS301", "Algorithms", 3);
    scheduler.addPrerequisite("CS201", "CS101");
    scheduler.addPrerequisite("CS301", "CS201");
    scheduler.validatePrerequisites();
    scheduler.displayTopologicalOrder();

    // Groups Demo
    cout << "\n\n>>> DEMO 2: STUDENT GROUPS <<<\n";
    GroupManager gManager;
    gManager.addStudent("21K-0001", "Ali", 3);
    gManager.addStudent("21K-0002", "Sara", 3);
    gManager.addStudent("21K-0003", "Hassan", 3);
    gManager.addStudent("21K-0004", "Fatima", 3);
    gManager.createProjectGroups(2);
    gManager.displayAllGroups();

    // Induction Demo
    cout << "\n\n>>> DEMO 3: INDUCTION <<<\n";
    InductionModule indMod;
    indMod.runInductionExample();

    cout << "\n\n>>> ALL DEMOS COMPLETED <<<\n";
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}
// Replace your runBenchmarkModule() function with this:

void runBenchmarkModule() {
    Benchmark bench;
    int choice;
    do {
        cout << "\n--- PERFORMANCE BENCHMARKING ---\n";
        cout << "1. Benchmark Sets\n";
        cout << "2. Benchmark Scheduling\n";
        cout << "3. Benchmark Relations\n";
        cout << "4. Benchmark Induction\n";
        cout << "5. Benchmark Logic\n";
        cout << "6. Benchmark Functions\n";
        cout << "7. Run All Benchmarks\n";

        cout << "\n--- UNIT TESTING (Correctness) ---\n";
        cout << "8. Test Sets Correctness\n";
        cout << "9. Test Scheduling Correctness\n";
        cout << "10. Test Relations Correctness\n";
        cout << "11. Test Induction Correctness\n";
        cout << "12. Test Logic Correctness\n";
        cout << "13. Test Functions Correctness\n";
        cout << "14. Test Consistency Correctness\n";
        cout << "15. Run All Unit Tests\n";

        cout << "\n--- COMPREHENSIVE TESTING ---\n";
        cout << "16. Generate Full Test Report\n";
        cout << "17. Stress Test Large Datasets\n";

        cout << "\n0. Back to Main Menu\n";
        cout << "\nChoice: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
            // Benchmarks
        case 1: bench.benchmarkSets(); break;
        case 2: bench.benchmarkScheduling(); break;
        case 3: bench.benchmarkRelations(); break;
        case 4: bench.benchmarkInduction(); break;
        case 5: bench.benchmarkLogic(); break;
        case 6: bench.benchmarkFunctions(); break;
        case 7: bench.benchmarkAll(); break;

            // Unit Tests
        case 8:
            if (bench.testSetsCorrectness())
                cout << "\n✓ Sets module PASSED all tests\n";
            else
                cout << "\n✗ Sets module FAILED some tests\n";
            break;
        case 9:
            if (bench.testSchedulingCorrectness())
                cout << "\n✓ Scheduling module PASSED all tests\n";
            else
                cout << "\n✗ Scheduling module FAILED some tests\n";
            break;
        case 10:
            if (bench.testRelationsCorrectness())
                cout << "\n✓ Relations module PASSED all tests\n";
            else
                cout << "\n✗ Relations module FAILED some tests\n";
            break;
        case 11:
            if (bench.testInductionCorrectness())
                cout << "\n✓ Induction module PASSED all tests\n";
            else
                cout << "\n✗ Induction module FAILED some tests\n";
            break;
        case 12:
            if (bench.testLogicCorrectness())
                cout << "\n✓ Logic module PASSED all tests\n";
            else
                cout << "\n✗ Logic module FAILED some tests\n";
            break;
        case 13:
            if (bench.testFunctionsCorrectness())
                cout << "\n✓ Functions module PASSED all tests\n";
            else
                cout << "\n✗ Functions module FAILED some tests\n";
            break;
        case 14:
            if (bench.testConsistencyCorrectness())
                cout << "\n✓ Consistency module PASSED all tests\n";
            else
                cout << "\n✗ Consistency module FAILED some tests\n";
            break;
        case 15:
            bench.runAllTests();
            break;

            // Comprehensive
        case 16:
            bench.generateTestReport();
            break;
        case 17:
            bench.stressTestLargeDataset();
            break;

        case 0:
            cout << "\nReturning to main menu...\n";
            break;

        default:
            cout << "\nInvalid choice! Try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }

    } while (choice != 0);
}
void runConsistencyModule() {
    ConsistencyModule cmod;
    int choice;
    do {
        cout << "\n=== Consistency Checker ===\n";
        cout << "1. Room Conflict Demo\n2. Faculty Conflict Demo\n3. Prerequisite Check Demo\n4. Overload Check Demo\n0. Back\nChoice: ";
        cin >> choice; cin.ignore();

        if (choice == 1) cmod.runRoomCheckDemo();
        else if (choice == 2) cmod.runFacultyCheckDemo();
        else if (choice == 3) cmod.runPrereqCheckDemo();
        else if (choice == 4) cmod.runOverloadCheckDemo();
    } while (choice != 0);
}
void runProofModule() {
    ProofModule pmod;
    int choice;
    do {
        cout << "\n=== Automated Proof Module ===\n";
        cout << "1. Run Induction Demo\n2. Run Logic Proof Demo\n3. Run Prerequisite Proof Demo\n";
        cout << "0. Back\nChoice: "; cin >> choice; cin.ignore();

        if (choice == 1) pmod.runInductionDemo();
        else if (choice == 2) pmod.runLogicDemo();
        else if (choice == 3) pmod.runPrerequisiteDemo();
    } while (choice != 0);
}
void runFunctionsModule() {
    FunctionModule fmod;
    int choice;
    do {
        cout << "\n=== Functions Module ===\n";
        cout << "1. Assign Student to Course\n2. Assign Course to Faculty\n3. Assign Faculty to Room\n";
        cout << "4. Verify Injectivity\n5. Verify Surjectivity\n6. Test Composition\n7. Test Inverse\n8. Display All Functions\n0. Back\n";
        cout << "Choice: "; cin >> choice; cin.ignore();

        if (choice == 1) { string s, c; cout << "Student: "; getline(cin, s); cout << "Course: "; getline(cin, c); fmod.assignStudentToCourse(s, c); }
        else if (choice == 2) { string c, f; cout << "Course: "; getline(cin, c); cout << "Faculty: "; getline(cin, f); fmod.assignCourseToFaculty(c, f); }
        else if (choice == 3) { string f, r; cout << "Faculty: "; getline(cin, f); cout << "Room: "; getline(cin, r); fmod.assignFacultyToRoom(f, r); }
        else if (choice == 4) { string name; cout << "Function name: "; getline(cin, name); fmod.verifyInjectivity(name); }
        else if (choice == 5) { string name; cout << "Function name: "; getline(cin, name); fmod.verifySurjectivity(name); }
        else if (choice == 6) fmod.testFunctionComposition();
        else if (choice == 7) fmod.testInverseFunction();
        else if (choice == 8) fmod.displayAllFunctions();
    } while (choice != 0);
}
void runRelationsModule() {
    RelationModule rel;
    int choice;
    do {
        cout << "\n=== Relations Module ===\n";
        cout << "1. Add Student-Course\n2. Add Faculty-Course\n3. Add Course-Room\n";
        cout << "4. Check Relation Properties\n5. Find Indirect Enrollments\n";
        cout << "6. Compose Relations\n7. Display All Relations\n0. Back to Main Menu\n";
        cout << "Choice: "; cin >> choice; cin.ignore();

        if (choice == 1) { string s, c; cout << "Student: "; getline(cin, s); cout << "Course: "; getline(cin, c); rel.addStudentCourse(s, c); }
        else if (choice == 2) { string f, c; cout << "Faculty: "; getline(cin, f); cout << "Course: "; getline(cin, c); rel.addFacultyCourse(f, c); }
        else if (choice == 3) { string c, r; cout << "Course: "; getline(cin, c); cout << "Room: "; getline(cin, r); rel.addCourseRoom(c, r); }
        else if (choice == 4) rel.checkRelationProperties();
        else if (choice == 5) rel.findIndirectEnrollments();
        else if (choice == 6) rel.composeRelations();
        else if (choice == 7) rel.displayAllRelations();
    } while (choice != 0);
}
void runSetModule() {
    SetModule sets;
    int choice;
    do {
        cout << "\n=== Set Operations Module ===\n";
        cout << "1. Add Student\n2. Add Course\n3. Add Faculty\n4. Add Room\n";
        cout << "5. Demonstrate Set Operations\n6. Generate Power Set\n";
        cout << "7. Display All Sets\n0. Back to Main Menu\n";
        cout << "Choice: "; cin >> choice; cin.ignore();

        if (choice == 1) { string s; cout << "Student name: "; getline(cin, s); sets.addStudent(s); }
        else if (choice == 2) { string s; cout << "Course name: "; getline(cin, s); sets.addCourse(s); }
        else if (choice == 3) { string s; cout << "Faculty name: "; getline(cin, s); sets.addFaculty(s); }
        else if (choice == 4) { string s; cout << "Room name: "; getline(cin, s); sets.addRoom(s); }
        else if (choice == 5) sets.demonstrateSetOperations();
        else if (choice == 6) { string type; cout << "Set type (student/course/faculty/room): "; getline(cin, type); sets.generatePowerSet(type); }
        else if (choice == 7) sets.displayAllSets();
    } while (choice != 0);
}
void runLogicModule() {
    LogicModule logic;
    int choice;
    do {
        cout << "\n=== Logic & Inference Engine ===\n";
        cout << "1. Add Assignment (Course, Faculty, Room)\n";
        cout << "2. Verify Faculty Assignment\n";
        cout << "3. Detect Conflicts\n";
        cout << "4. Check Room Allocation\n";
        cout << "5. Demonstrate Tautology\n";
        cout << "6. Demonstrate Contradiction\n";
        cout << "7. Demonstrate Logical Equivalence\n";
        cout << "8. Display All Assignments\n";
        cout << "0. Back to Main Menu\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string course, faculty, room;
            cout << "Enter course: "; getline(cin, course);
            cout << "Enter faculty: "; getline(cin, faculty);
            cout << "Enter room: "; getline(cin, room);
            logic.addAssignment(course, faculty, room);
        }
        else if (choice == 2) {
            string faculty, course, expectedLab;
            cout << "Enter faculty: "; getline(cin, faculty);
            cout << "Enter course: "; getline(cin, course);
            cout << "Enter expected lab/room: "; getline(cin, expectedLab);
            bool valid = logic.verifyFacultyAssignment(faculty, course, expectedLab);
            cout << (valid ? "Assignment OK\n" : "Assignment Conflict Detected!\n");
        }
        else if (choice == 3) {
            bool conflicts = logic.detectConflicts();
            cout << (conflicts ? "Conflicts detected!\n" : "No conflicts.\n");
        }
        else if (choice == 4) {
            string course;
            cout << "Enter course: "; getline(cin, course);
            bool ok = logic.checkRoomAllocation(course);
            cout << (ok ? "Room allocation OK\n" : "Room conflict detected!\n");
        }
        else if (choice == 5) logic.demonstrateTautology();
        else if (choice == 6) logic.demonstrateContradiction();
        else if (choice == 7) logic.demonstrateLogicalEquivalence();
        else if (choice == 8) logic.displayAllAssignments();

    } while (choice != 0);
}


int main() {
    int choice;

    cout << "======================================================\n";
    cout << "=                  UNIDISC ENGINE                    =\n";
    cout << "=           FAST University Academic System          =\n";
    cout << "=   Discrete Mathematics Computational Framework     =\n";
    cout << "======================================================\n";
    cout << "\nInitializing system...\n";
    cout << "System ready!\n";

    do {
        displayMainMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            runCourseModule();
            break;
        case 2:
            runGroupModule();
            break;
        case 3:
            runInductionModule();
            break;
        case 4: runLogicModule(); break;
        case 5: runSetModule(); break;
        case 6: runRelationsModule(); break;
        case 7: runFunctionsModule(); break;
        case 8: runProofModule(); break;
        case 9: runConsistencyModule(); break;
        case 10: runBenchmarkModule(); break;

        case 11:
            runAllDemos();
            break;
        case 12:
            cout << "\nThank you for using UNIDISC ENGINE!\n";
            cout << "Developed for FAST University Discrete Mathematics Project\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 12);

    return 0;
}