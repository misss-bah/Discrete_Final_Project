#ifndef GROUPS_H
#define GROUPS_H
#include "Course.h"
#include <iostream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 200;
const int MAX_GROUPS = 100;
const int MAX_GROUP_SIZE = 20;

class Student {
private:
    string studentID;
    string name;
    int semester;

public:
    Student();
    Student(const string& id, const string& n, int sem);

    string getID() const;
    string getName() const;
    int getSemester() const;
    void display() const;
};

class StudentGroup {
private:
    Student* members[MAX_GROUP_SIZE];
    int memberCount;
    string groupName;
    string groupType;

public:
    StudentGroup();
    StudentGroup(const string& name, const string& type);

    bool addMember(Student* student);
    void displayGroup() const;
    int getMemberCount() const;
    string getGroupName() const;
};

class GroupManager {
private:
    Student students[MAX_STUDENTS];
    int studentCount;
    StudentGroup groups[MAX_GROUPS];
    int groupCount;

    // Helper functions
    long long factorial(int n);
    long long nCr(int n, int r);
    void generateCombinationsUtil(int start, int n, int r, int index,
        int data[], Student* allStudents[],
        StudentGroup& group);

public:
    GroupManager();

    void addStudent(const string& id, const string& name, int semester);
    void createProjectGroups(int groupSize);
    void createLabSessions(int studentsPerLab);
    void assignToElectives(const string& elective, int maxStudents);
    void displayAllStudents() const;
    void displayAllGroups() const;
    int getStudentCount() const;
    int getGroupCount() const;

    // Combination calculations
    long long calculatePossibleCombinations(int totalStudents, int groupSize);
    void generateAllCombinations(int groupSize, int maxGroups);
};

#endif