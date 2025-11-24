#include "Groups.h"
using namespace std;

// Student implementation
Student::Student() : semester(0) {}

Student::Student( string id,  string n, int sem)
    : studentID(id), name(n), semester(sem) {
}

void Student::display() const {
    cout << "ID: " << studentID << ", Name: " << name << ", Semester: " << semester;
}

// StudentGroup implementation
StudentGroup::StudentGroup() : memberCount(0), groupName(""), groupType("") {
    for (int i = 0; i < MAX_GROUP_SIZE; i++) {
        members[i] = nullptr;
    }
}

StudentGroup::StudentGroup( string name,  string type)
    : memberCount(0), groupName(name), groupType(type) {
    for (int i = 0; i < MAX_GROUP_SIZE; i++) {
        members[i] = nullptr;
    }
}

bool StudentGroup::addMember(Student* student) {
    if (memberCount < MAX_GROUP_SIZE) {
        members[memberCount++] = student;
        return true;
    }
    return false;
}

void StudentGroup::displayGroup() const {
    cout << "\n--- " << groupName << " (" << groupType << ") ---" << endl;
    cout << "Members (" << memberCount << "):" << endl;
    for (int i = 0; i < memberCount; i++) {
        cout << "  " << (i + 1) << ". ";
        members[i]->display();
        cout << endl;
    }
}

// GroupManager implementation
GroupManager::GroupManager() : studentCount(0), groupCount(0) {}

void GroupManager::addStudent( string id,  string name, int semester) {
    if (studentCount < MAX_STUDENTS) {
        students[studentCount++] = Student(id, name, semester);
    }
}

long long GroupManager::factorial(int n) {
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

long long GroupManager::nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    return factorial(n) / (factorial(r) * factorial(n - r));
}

long long GroupManager::calculatePossibleCombinations(int totalStudents, int groupSize) {
    return nCr(totalStudents, groupSize);
}

void GroupManager::generateCombinationsUtil(int start, int n, int r, int index,  int data[], Student* allStudents[], StudentGroup& group) {
    if (index == r) {
        for (int i = 0; i < r; i++) {
            group.addMember(allStudents[data[i]]);
        }
        return;
    }

    for (int i = start; i <= n - r + index; i++) {
        data[index] = i;
        generateCombinationsUtil(i + 1, n, r, index + 1, data, allStudents, group);
    }
}

void GroupManager::createProjectGroups(int groupSize) {
    if (studentCount < groupSize) {
        cout << "Not enough students for group size " << groupSize << endl;
        return;
    }

    int numGroups = studentCount / groupSize;
    cout << "\n=== Creating Project Groups (Size: " << groupSize << ") ===" << endl;
    cout << "Possible combinations: " << calculatePossibleCombinations(studentCount, groupSize) << endl;

    int studentIndex = 0;
    for (int g = 0; g < numGroups && groupCount < MAX_GROUPS; g++) {
        string groupName = "Project Group " + to_string(g + 1);
        groups[groupCount] = StudentGroup(groupName, "Project");

        for (int i = 0; i < groupSize && studentIndex < studentCount; i++) {
            groups[groupCount].addMember(&students[studentIndex++]);
        }
        groupCount++;
    }

    cout << "Created " << numGroups << " project groups" << endl;
}

void GroupManager::createLabSessions(int studentsPerLab) {
    if (studentCount < studentsPerLab) {
        cout << "Not enough students for lab sessions" << endl;
        return;
    }

    int numLabs = (studentCount + studentsPerLab - 1) / studentsPerLab;
    cout << "\n=== Creating Lab Sessions (Size: " << studentsPerLab << ") ===" << endl;

    int studentIndex = 0;
    for (int l = 0; l < numLabs && groupCount < MAX_GROUPS; l++) {
        string labName = "Lab Session " + to_string(l + 1);
        groups[groupCount] = StudentGroup(labName, "Lab");

        for (int i = 0; i < studentsPerLab && studentIndex < studentCount; i++) {
            groups[groupCount].addMember(&students[studentIndex++]);
        }
        groupCount++;
    }

    cout << "Created " << numLabs << " lab sessions" << endl;
}

void GroupManager::assignToElectives( string elective, int maxStudents) {
    cout << "\n=== Assigning to Elective: " << elective << " ===" << endl;

    if (groupCount >= MAX_GROUPS) {
        cout << "Maximum groups reached" << endl;
        return;
    }

    groups[groupCount] = StudentGroup(elective, "Elective");

    int assigned = 0;
    for (int i = 0; i < studentCount && assigned < maxStudents; i++) {
        groups[groupCount].addMember(&students[i]);
        assigned++;
    }

    cout << "Assigned " << assigned << " students to " << elective << endl;
    groupCount++;
}

void GroupManager::displayAllStudents() const {
    cout << "\n=== All Students (" << studentCount << ") ===" << endl;
    for (int i = 0; i < studentCount; i++) {
        cout << (i + 1) << ". ";
        students[i].display();
        cout << endl;
    }
}

void GroupManager::displayAllGroups() const {
    cout << "\n=== All Groups (" << groupCount << ") ===" << endl;
    for (int i = 0; i < groupCount; i++) {
        groups[i].displayGroup();
    }
}
// Helper recursive function (private to GroupManager)
void GroupManager::generateCombinationsUtil(int start, int r, int index,
    int data[], StudentGroup& group) {
    if (index == r) {
        // Add the selected students to the group
        for (int i = 0; i < r; i++) {
            group.addMember(&students[data[i]]);
        }
        return;
    }

    for (int i = start; i <= studentCount - r + index; i++) {
        data[index] = i;
        generateCombinationsUtil(i + 1, r, index + 1, data, group);
    }
}

void GroupManager::generateAllCombinations(int groupSize, int maxDisplay) {
    cout << "\n=== Generating All Possible Combinations ===" << endl;
    cout << "Group Size: " << groupSize << endl;

    if (studentCount < groupSize) {
        cout << "Not enough students to form a group of this size." << endl;
        return;
    }

    long long totalComb = calculatePossibleCombinations(studentCount, groupSize);
    cout << "Total Possible Combinations: " << totalComb << endl;

    if (maxDisplay > 10) {
        cout << "(Showing first 10 combinations only for display)" << endl;
        maxDisplay = 10;
    }

    int data[MAX_GROUP_SIZE];  // indices of selected students
    int displayed = 0;

    // Generate each combination sequentially
    for (int start = 0; start <= studentCount - groupSize && displayed < maxDisplay; start++) {
        StudentGroup newGroup("Project Group " + to_string(groupCount + 1), "Project");
        generateCombinationsUtil(start, groupSize, 0, data, newGroup);
        groups[groupCount++] = newGroup;
        displayed++;
    }

    cout << "Created " << displayed << " groups (up to display limit)" << endl;
}
