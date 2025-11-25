//#include <iostream>
//#include <string>
//#include "WindowsColors.h"
//#include "Courses.h"
//#include "Groups.h"
//#include "Induction.h"
//#include "LogicEngine.h"
//#include "Sets.h"
//#include "Relations.h"
//#include "Functions.h"
//#include "Proofs.h"
//#include "Consistency.h"
//#include "Benchmark.h"
//
//using namespace std;
//
//void displayMainMenu() {
//    WindowsColors::clearScreen();
//    WindowsColors::printHeader("UNIDISC ENGINE - FAST University");
//    WindowsColors::printInfo("Discrete Mathematics Computational Framework");
//
//    cout << "\n";
//    WindowsColors::printMenuOption(1, "Course & Scheduling Module");
//    WindowsColors::printMenuOption(2, "Student Group Combination Module");
//    WindowsColors::printMenuOption(3, "Induction & Strong Induction Module");
//    WindowsColors::printMenuOption(4, "Logic & Inference Engine");
//    WindowsColors::printMenuOption(5, "Set Operations Module");
//    WindowsColors::printMenuOption(6, "Relations Module");
//    WindowsColors::printMenuOption(7, "Functions Module");
//    WindowsColors::printMenuOption(8, "Automated Proof & Verification");
//    WindowsColors::printMenuOption(9, "Consistency Checker");
//    WindowsColors::printMenuOption(10, "Algorithmic Efficiency & Benchmarking");
//    WindowsColors::printMenuOption(11, "Run All Demos");
//    WindowsColors::printMenuOption(12, "Exit");
//
//    WindowsColors::printMenuSeparator();
//    WindowsColors::printChoicePrompt();
//}
//
//void runCourseModule() {
//    CourseScheduler scheduler;
//    int choice;
//
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Course & Scheduling Module");
//
//        WindowsColors::printMenuOption(1, "Add Course");
//        WindowsColors::printMenuOption(2, "Add Prerequisite");
//        WindowsColors::printMenuOption(3, "Validate Prerequisites");
//        WindowsColors::printMenuOption(4, "Display Topological Order");
//        WindowsColors::printMenuOption(5, "Generate Valid Sequences");
//        WindowsColors::printMenuOption(6, "Display All Courses");
//        WindowsColors::printMenuOption(7, "Load Sample Data");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            string code, name;
//            int credits;
//            WindowsColors::printInfo("Enter course code: ");
//            getline(cin, code);
//            WindowsColors::printInfo("Enter course name: ");
//            getline(cin, name);
//            WindowsColors::printInfo("Enter credits: ");
//            cin >> credits;
//            cin.ignore();
//            scheduler.addCourse(code, name, credits);
//            WindowsColors::printSuccess("Course added successfully!");
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            string course, prereq;
//            WindowsColors::printInfo("Enter course code: ");
//            getline(cin, course);
//            WindowsColors::printInfo("Enter prerequisite code: ");
//            getline(cin, prereq);
//            scheduler.addPrerequisite(course, prereq);
//            WindowsColors::printSuccess("Prerequisite added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            scheduler.validatePrerequisites();
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            scheduler.displayTopologicalOrder();
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            int maxCourses;
//            WindowsColors::printInfo("Enter maximum courses in sequence: ");
//            cin >> maxCourses;
//            scheduler.generateAllValidSequences(maxCourses);
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            scheduler.displayAllCourses();
//            WindowsColors::pause();
//        }
//        else if (choice == 7) {
//            scheduler.addCourse("CS101", "Introduction to CS", 3);
//            scheduler.addCourse("CS102", "Programming Fundamentals", 3);
//            scheduler.addCourse("CS201", "Data Structures", 3);
//            scheduler.addCourse("CS202", "OOP", 3);
//            scheduler.addCourse("CS301", "Algorithms", 3);
//
//            scheduler.addPrerequisite("CS102", "CS101");
//            scheduler.addPrerequisite("CS201", "CS102");
//            scheduler.addPrerequisite("CS202", "CS102");
//            scheduler.addPrerequisite("CS301", "CS201");
//
//            WindowsColors::printSuccess("Sample data loaded!");
//            WindowsColors::pause();
//        }
//
//    } while (choice != 0);
//}
//
//void runGroupModule() {
//    GroupManager manager;
//    int choice;
//
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Student Group Combination Module");
//
//        WindowsColors::printMenuOption(1, "Add Student");
//        WindowsColors::printMenuOption(2, "Create Project Groups");
//        WindowsColors::printMenuOption(3, "Create Lab Sessions");
//        WindowsColors::printMenuOption(4, "Assign to Electives");
//        WindowsColors::printMenuOption(5, "Display All Students");
//        WindowsColors::printMenuOption(6, "Display All Groups");
//        WindowsColors::printMenuOption(7, "Calculate Combinations");
//        WindowsColors::printMenuOption(8, "Load Sample Students");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            string id, name;
//            int semester;
//            WindowsColors::printInfo("Enter student ID: ");
//            getline(cin, id);
//            WindowsColors::printInfo("Enter name: ");
//            getline(cin, name);
//            WindowsColors::printInfo("Enter semester: ");
//            cin >> semester;
//            manager.addStudent(id, name, semester);
//            WindowsColors::printSuccess("Student added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            int groupSize;
//            WindowsColors::printInfo("Enter group size: ");
//            cin >> groupSize;
//            manager.createProjectGroups(groupSize);
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            int labSize;
//            WindowsColors::printInfo("Enter students per lab: ");
//            cin >> labSize;
//            manager.createLabSessions(labSize);
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            string elective;
//            int maxStudents;
//            cin.ignore();
//            WindowsColors::printInfo("Enter elective name: ");
//            getline(cin, elective);
//            WindowsColors::printInfo("Enter max students: ");
//            cin >> maxStudents;
//            manager.assignToElectives(elective, maxStudents);
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            manager.displayAllStudents();
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            manager.displayAllGroups();
//            WindowsColors::pause();
//        }
//        else if (choice == 7) {
//            int total, groupSize;
//            WindowsColors::printInfo("Enter total students: ");
//            cin >> total;
//            WindowsColors::printInfo("Enter group size: ");
//            cin >> groupSize;
//            long long combs = manager.calculatePossibleCombinations(total, groupSize);
//            WindowsColors::printStatsBox("Possible Combinations (nCr)", to_string(combs));
//            WindowsColors::pause();
//        }
//        else if (choice == 8) {
//            manager.addStudent("24F-3001", "Ali Ahmed", 3);
//            manager.addStudent("24F-3002", "Sara Khan", 3);
//            manager.addStudent("24F-3003", "Hassan Ali", 3);
//            manager.addStudent("24F-3004", "Fatima Noor", 3);
//            manager.addStudent("24F-3005", "Omar Siddiqui", 3);
//            manager.addStudent("24F-3006", "Ayesha Malik", 3);
//            manager.addStudent("24F-3007", "Bilal Tariq", 3);
//            manager.addStudent("24F-3008", "Zainab Riaz", 3);
//
//            WindowsColors::printSuccess("Sample students loaded!");
//            WindowsColors::pause();
//        }
//
//    } while (choice != 0);
//}
//
//void runInductionModule() {
//    InductionModule indModule;
//    int choice;
//
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Induction & Strong Induction Module");
//
//        WindowsColors::printMenuOption(1, "Add Course with Prerequisites");
//        WindowsColors::printMenuOption(2, "Verify Can Take Course");
//        WindowsColors::printMenuOption(3, "Verify Indirect Prerequisites");
//        WindowsColors::printMenuOption(4, "Demonstrate Base Case");
//        WindowsColors::printMenuOption(5, "Demonstrate Inductive Step");
//        WindowsColors::printMenuOption(6, "Run Complete Induction Example");
//        WindowsColors::printMenuOption(7, "Display Course Prerequisites");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            string course;
//            int prereqCount;
//            WindowsColors::printInfo("Enter course name: ");
//            getline(cin, course);
//            WindowsColors::printInfo("Enter number of prerequisites: ");
//            cin >> prereqCount;
//            cin.ignore();
//
//            string* prereqs = new string[prereqCount];
//            for (int i = 0; i < prereqCount; i++) {
//                WindowsColors::printInfo("Enter prerequisite " + to_string(i + 1) + ": ");
//                getline(cin, prereqs[i]);
//            }
//
//            indModule.addCourseWithPrereqs(course, prereqs, prereqCount);
//            delete[] prereqs;
//            WindowsColors::printSuccess("Course added with prerequisites!");
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            indModule.demonstrateBaseCase();
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            indModule.demonstrateInductiveStep();
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            indModule.runInductionExample();
//            WindowsColors::pause();
//        }
//        else if (choice == 7) {
//            indModule.displayCoursePrerequisites();
//            WindowsColors::pause();
//        }
//
//    } while (choice != 0);
//}
//
//void runAllDemos() {
//    WindowsColors::clearScreen();
//    WindowsColors::printHeader("RUNNING ALL MODULE DEMONSTRATIONS");
//
//    WindowsColors::printSubHeader("Demo 1: Course & Scheduling");
//    CourseScheduler scheduler;
//    scheduler.addCourse("CS101", "Intro to CS", 3);
//    scheduler.addCourse("CS201", "Data Structures", 3);
//    scheduler.addCourse("CS301", "Algorithms", 3);
//    scheduler.addPrerequisite("CS201", "CS101");
//    scheduler.addPrerequisite("CS301", "CS201");
//    scheduler.validatePrerequisites();
//    scheduler.displayTopologicalOrder();
//
//    WindowsColors::printSubHeader("Demo 2: Student Groups");
//    GroupManager gManager;
//    gManager.addStudent("21K-0001", "Ali", 3);
//    gManager.addStudent("21K-0002", "Sara", 3);
//    gManager.addStudent("21K-0003", "Hassan", 3);
//    gManager.addStudent("21K-0004", "Fatima", 3);
//    gManager.createProjectGroups(2);
//    gManager.displayAllGroups();
//
//    WindowsColors::printSubHeader("Demo 3: Induction");
//    InductionModule indMod;
//    indMod.runInductionExample();
//
//    WindowsColors::printSuccess("All demos completed successfully!");
//    WindowsColors::pause();
//}
//
//void runBenchmarkModule() {
//    Benchmark bench;
//    int choice;
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Algorithmic Efficiency & Benchmarking");
//
//        WindowsColors::printMenuOption(1, "Benchmark Sets");
//        WindowsColors::printMenuOption(2, "Benchmark Scheduling");
//        WindowsColors::printMenuOption(3, "Benchmark Relations");
//        WindowsColors::printMenuOption(4, "Benchmark Induction");
//        WindowsColors::printMenuOption(5, "Benchmark Logic");
//        WindowsColors::printMenuOption(6, "Run All Benchmarks");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            bench.benchmarkSets();
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            bench.benchmarkScheduling();
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            bench.benchmarkRelations();
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            bench.benchmarkInduction();
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            bench.benchmarkLogic();
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            WindowsColors::printSection("Running All Benchmarks");
//            bench.benchmarkSets();
//            bench.benchmarkScheduling();
//            bench.benchmarkRelations();
//            bench.benchmarkInduction();
//            bench.benchmarkLogic();
//            WindowsColors::printSuccess("All benchmarks completed!");
//            WindowsColors::pause();
//        }
//    } while (choice != 0);
//}
//
//void runConsistencyModule() {
//    ConsistencyModule cmod;
//    int choice;
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Consistency Checker");
//
//        WindowsColors::printMenuOption(1, "Room Conflict Detection");
//        WindowsColors::printMenuOption(2, "Faculty Conflict Detection");
//        WindowsColors::printMenuOption(3, "Prerequisite Check");
//        WindowsColors::printMenuOption(4, "Overload Check");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            cmod.runRoomCheckDemo();
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            cmod.runFacultyCheckDemo();
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            cmod.runPrereqCheckDemo();
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            cmod.runOverloadCheckDemo();
//            WindowsColors::pause();
//        }
//    } while (choice != 0);
//}
//
//void runProofModule() {
//    ProofModule pmod;
//    int choice;
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Automated Proof & Verification");
//
//        WindowsColors::printMenuOption(1, "Induction Proof Demo");
//        WindowsColors::printMenuOption(2, "Logic Proof Demo");
//        WindowsColors::printMenuOption(3, "Prerequisite Proof Demo");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            pmod.runInductionDemo();
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            pmod.runLogicDemo();
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            pmod.runPrerequisiteDemo();
//            WindowsColors::pause();
//        }
//    } while (choice != 0);
//}
//
//void runFunctionsModule() {
//    FunctionModule fmod;
//    int choice;
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Functions Module");
//
//        WindowsColors::printMenuOption(1, "Assign Student to Course");
//        WindowsColors::printMenuOption(2, "Assign Course to Faculty");
//        WindowsColors::printMenuOption(3, "Assign Faculty to Room");
//        WindowsColors::printMenuOption(4, "Verify Injectivity");
//        WindowsColors::printMenuOption(5, "Verify Surjectivity");
//        WindowsColors::printMenuOption(6, "Test Function Composition");
//        WindowsColors::printMenuOption(7, "Test Function Inverse");
//        WindowsColors::printMenuOption(8, "Display All Functions");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            string s, c;
//            WindowsColors::printInfo("Enter student: ");
//            getline(cin, s);
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, c);
//            fmod.assignStudentToCourse(s, c);
//            WindowsColors::printSuccess("Mapping added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            string c, f;
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, c);
//            WindowsColors::printInfo("Enter faculty: ");
//            getline(cin, f);
//            fmod.assignCourseToFaculty(c, f);
//            WindowsColors::printSuccess("Mapping added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            string f, r;
//            WindowsColors::printInfo("Enter faculty: ");
//            getline(cin, f);
//            WindowsColors::printInfo("Enter room: ");
//            getline(cin, r);
//            fmod.assignFacultyToRoom(f, r);
//            WindowsColors::printSuccess("Mapping added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            string name;
//            WindowsColors::printInfo("Function name: ");
//            getline(cin, name);
//            fmod.verifyInjectivity(name);
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            string name;
//            WindowsColors::printInfo("Function name: ");
//            getline(cin, name);
//            fmod.verifySurjectivity(name);
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            fmod.testFunctionComposition();
//            WindowsColors::pause();
//        }
//        else if (choice == 7) {
//            fmod.testInverseFunction();
//            WindowsColors::pause();
//        }
//        else if (choice == 8) {
//            fmod.displayAllFunctions();
//            WindowsColors::pause();
//        }
//    } while (choice != 0);
//}
//
//void runRelationsModule() {
//    RelationModule rel;
//    int choice;
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Relations Module");
//
//        WindowsColors::printMenuOption(1, "Add Student-Course");
//        WindowsColors::printMenuOption(2, "Add Faculty-Course");
//        WindowsColors::printMenuOption(3, "Add Course-Room");
//        WindowsColors::printMenuOption(4, "Check Relation Properties");
//        WindowsColors::printMenuOption(5, "Find Indirect Enrollments");
//        WindowsColors::printMenuOption(6, "Compose Relations");
//        WindowsColors::printMenuOption(7, "Display All Relations");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            string s, c;
//            WindowsColors::printInfo("Enter student: ");
//            getline(cin, s);
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, c);
//            rel.addStudentCourse(s, c);
//            WindowsColors::printSuccess("Pair added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            string f, c;
//            WindowsColors::printInfo("Enter faculty: ");
//            getline(cin, f);
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, c);
//            rel.addFacultyCourse(f, c);
//            WindowsColors::printSuccess("Pair added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            string c, r;
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, c);
//            WindowsColors::printInfo("Enter room: ");
//            getline(cin, r);
//            rel.addCourseRoom(c, r);
//            WindowsColors::printSuccess("Pair added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            rel.checkRelationProperties();
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            rel.findIndirectEnrollments();
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            rel.composeRelations();
//            WindowsColors::pause();
//        }
//        else if (choice == 7) {
//            rel.displayAllRelations();
//            WindowsColors::pause();
//        }
//    } while (choice != 0);
//}
//
//void runSetModule() {
//    SetModule sets;
//    int choice;
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Set Operations Module");
//
//        WindowsColors::printMenuOption(1, "Add Student");
//        WindowsColors::printMenuOption(2, "Add Course");
//        WindowsColors::printMenuOption(3, "Add Faculty");
//        WindowsColors::printMenuOption(4, "Add Room");
//        WindowsColors::printMenuOption(5, "Demonstrate Set Operations");
//        WindowsColors::printMenuOption(6, "Generate Power Set");
//        WindowsColors::printMenuOption(7, "Display All Sets");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            string s;
//            WindowsColors::printInfo("Enter student name: ");
//            getline(cin, s);
//            sets.addStudent(s);
//            WindowsColors::printSuccess("Student added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            string s;
//            WindowsColors::printInfo("Enter course name: ");
//            getline(cin, s);
//            sets.addCourse(s);
//            WindowsColors::printSuccess("Course added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            string s;
//            WindowsColors::printInfo("Enter faculty name: ");
//            getline(cin, s);
//            sets.addFaculty(s);
//            WindowsColors::printSuccess("Faculty added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            string s;
//            WindowsColors::printInfo("Enter room name: ");
//            getline(cin, s);
//            sets.addRoom(s);
//            WindowsColors::printSuccess("Room added!");
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            sets.demonstrateSetOperations();
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            string type;
//            WindowsColors::printInfo("Enter set type (student/course/faculty/room): ");
//            getline(cin, type);
//            sets.generatePowerSet(type);
//            WindowsColors::pause();
//        }
//        else if (choice == 7) {
//            sets.displayAllSets();
//            WindowsColors::pause();
//        }
//    } while (choice != 0);
//}
//
//void runLogicModule() {
//    LogicModule logic;
//    int choice;
//    do {
//        WindowsColors::clearScreen();
//        WindowsColors::printHeader("Logic & Inference Engine");
//
//        WindowsColors::printMenuOption(1, "Add Assignment (Course, Faculty, Room)");
//        WindowsColors::printMenuOption(2, "Verify Faculty Assignment");
//        WindowsColors::printMenuOption(3, "Detect Conflicts");
//        WindowsColors::printMenuOption(4, "Check Room Allocation");
//        WindowsColors::printMenuOption(5, "Demonstrate Tautology");
//        WindowsColors::printMenuOption(6, "Demonstrate Contradiction");
//        WindowsColors::printMenuOption(7, "Demonstrate Logical Equivalence");
//        WindowsColors::printMenuOption(8, "Display All Assignments");
//        WindowsColors::printMenuOption(0, "Back to Main Menu");
//
//        WindowsColors::printMenuSeparator();
//        WindowsColors::printChoicePrompt();
//        cin >> choice;
//        cin.ignore();
//
//        if (choice == 1) {
//            string course, faculty, room;
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, course);
//            WindowsColors::printInfo("Enter faculty: ");
//            getline(cin, faculty);
//            WindowsColors::printInfo("Enter room: ");
//            getline(cin, room);
//            logic.addAssignment(course, faculty, room);
//            WindowsColors::printSuccess("Assignment added successfully!");
//            WindowsColors::pause();
//        }
//        else if (choice == 2) {
//            string faculty, course, expectedLab;
//            WindowsColors::printInfo("Enter faculty: ");
//            getline(cin, faculty);
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, course);
//            WindowsColors::printInfo("Enter expected lab/room: ");
//            getline(cin, expectedLab);
//            bool valid = logic.verifyFacultyAssignment(faculty, course, expectedLab);
//            if (valid) WindowsColors::printSuccess("Assignment verified!");
//            else WindowsColors::printError("Assignment conflict detected!");
//            WindowsColors::pause();
//        }
//        else if (choice == 3) {
//            bool conflicts = logic.detectConflicts();
//            if (conflicts) WindowsColors::printWarning("Conflicts detected!");
//            else WindowsColors::printSuccess("No conflicts found!");
//            WindowsColors::pause();
//        }
//        else if (choice == 4) {
//            string course;
//            WindowsColors::printInfo("Enter course: ");
//            getline(cin, course);
//            bool ok = logic.checkRoomAllocation(course);
//            if (ok) WindowsColors::printSuccess("Room allocation OK!");
//            else WindowsColors::printError("Room conflict detected!");
//            WindowsColors::pause();
//        }
//        else if (choice == 5) {
//            logic.demonstrateTautology();
//            WindowsColors::pause();
//        }
//        else if (choice == 6) {
//            logic.demonstrateContradiction();
//            WindowsColors::pause();
//        }
//        else if (choice == 7) {
//            logic.demonstrateLogicalEquivalence();
//            WindowsColors::pause();
//        }
//        else if (choice == 8) {
//            logic.displayAllAssignments();
//            WindowsColors::pause();
//        }
//    } while (choice != 0);
//}
//
//int main() {
//    int choice;
//
//    WindowsColors::initConsole();
//    WindowsColors::clearScreen();
//    WindowsColors::printHeader("UNIDISC ENGINE");
//    WindowsColors::printInfo("FAST University Academic System");
//    WindowsColors::printInfo("Discrete Mathematics Computational Framework");
//
//    cout << "\n";
//    WindowsColors::printSuccess("System initialized successfully!");
//    WindowsColors::printInfo("Loading modules...");
//
//
//    WindowsColors::printSuccess("All modules loaded!");
//    WindowsColors::pause();
//
//    do {
//        displayMainMenu();
//        cin >> choice;
//        cin.ignore();
//
//        switch (choice) {
//        case 1:
//            runCourseModule();
//            break;
//        case 2:
//            runGroupModule();
//            break;
//        case 3:
//            runInductionModule();
//            break;
//        case 4:
//            runLogicModule();
//            break;
//        case 5:
//            runSetModule();
//            break;
//        case 6:
//            runRelationsModule();
//            break;
//        case 7:
//            runFunctionsModule();
//            break;
//        case 8:
//            runProofModule();
//            break;
//        case 9:
//            runConsistencyModule();
//            break;
//        case 10:
//            runBenchmarkModule();
//            break;
//        case 11:
//            runAllDemos();
//            break;
//        case 12:
//            WindowsColors::clearScreen();
//            WindowsColors::printHeader("GOODBYE!");
//            WindowsColors::printSuccess("Thank you for using UNIDISC ENGINE!");
//            WindowsColors::printInfo("Developed for FAST University");
//            WindowsColors::printInfo("Discrete Mathematics Project");
//            cout << "\n";
//            break;
//        default:
//            WindowsColors::printError("Invalid choice! Please try again.");
//            WindowsColors::pause();
//        }
//
//    } while (choice != 12);
//
//    return 0;
//}