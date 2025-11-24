#include "Groups.h"
using namespace std;

// Student implementation
Student::Student() : semester(0) {}

Student::Student(const string& id, const string& n, int sem)
    : studentID(id), name(n), semester(sem) {
}

string Student::getID() const {
    return studentID;
}

string Student::getName() const {
    return name;
}

int Student::getSemester() const {
    return semester;
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

StudentGroup::StudentGroup(const string& name, const string& type)
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

int StudentGroup::getMemberCount() const {
    return memberCount;
}

string StudentGroup::getGroupName() const {
    return groupName;
}

// GroupManager implementation
GroupManager::GroupManager() : studentCount(0), groupCount(0) {}

void GroupManager::addStudent(const string& id, const string& name, int semester) {
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

void GroupManager::generateCombinationsUtil(int start, int n, int r, int index,
    int data[], Student* allStudents[],
    StudentGroup& group) {
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

void GroupManager::assignToElectives(const string& elective, int maxStudents) {
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

int GroupManager::getStudentCount() const {
    return studentCount;
}

int GroupManager::getGroupCount() const {
    return groupCount;
}

void generateAllCombinations() {
    // Total number of subsets = 2^size
    int total = 1;
    for (int i = 0; i < size; i++) {
        total *= 2;
    }

    cout << "All possible combinations:\n";

    // Loop through each possible subset number
    for (int mask = 0; mask < total; mask++) {
        cout << "{ ";

        // Check each bit to decide whether to include arr[i]
        for (int i = 0; i < size; i++) {
            if ((mask >> i) & 1) {
                cout << arr[i] << " ";
            }
        }

        cout << "}\n";
    }
}
