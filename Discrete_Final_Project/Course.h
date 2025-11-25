#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_COURSES = 100;
const int MAX_PREREQUISITES = 10;
const int MAX_SEQUENCES = 1000;

// Manual Dynamic Array template
template<typename T>
class DynamicArray {
private:
    T* arr;
    int capacity;
    int size;

    void resize() {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

public:
    DynamicArray() : capacity(10), size(0) {
        arr = new T[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void push(const T& element) {
        if (size >= capacity) {
            resize();
        }
        arr[size++] = element;
    }

    T& operator[](int index) {
        return arr[index];
    }

    const T& operator[](int index) const {
        return arr[index];
    }

    int getSize() const { return size; }
    void clear() { size = 0; }
    bool isEmpty() const { return size == 0; }
};

// Course class
class Course {
private:
    string courseCode;
    string courseName;
    int credits;
    string prerequisites[MAX_PREREQUISITES];
    int prereqCount;

public:
    Course();
    Course(const string& code, const string& name, int cred);

    void addPrerequisite(const string& prereq);
    string getCode() const { return courseCode; }
    string getName() const { return courseName; }
    int getCredits() const { return credits; }
    int getPrereqCount() const { return prereqCount; }
    string getPrerequisite(int index) const;

    void display() const;
};

// Course Scheduler
class CourseScheduler {
private:
    Course courses[MAX_COURSES];
    int courseCount;

    // Adjacency list representation (manual)
    struct AdjNode {
        int courseIndex;
        AdjNode* next;
    };
    AdjNode* adjacencyList[MAX_COURSES];

    // Helper functions
    int findCourseIndex(const string& code) const;
    bool hasCycleUtil(int courseIdx, bool visited[], bool recStack[]);
    bool hasCycle();
    void topologicalSortUtil(int courseIdx, bool visited[], int stack[], int& stackIndex);
    void generateSequencesRecursive(bool completed[], int completedCount,
        DynamicArray<DynamicArray<string>>& allSequences,
        DynamicArray<string>& currentSeq,
        int maxDepth);
    bool canTakeCourse(int courseIdx, bool completed[]) const;

public:
    CourseScheduler();
    ~CourseScheduler();

    void addCourse(const string& code, const string& name, int credits);
    void addPrerequisite(const string& courseCode, const string& prereqCode);
    bool validatePrerequisites();
    void generateAllValidSequences(int maxCourses);
    void displayTopologicalOrder();
    void displayAllCourses() const;
    int getCourseCount() const { return courseCount; }
};

#endif