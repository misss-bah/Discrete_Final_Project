
#ifndef COURSES_H
#define COURSES_H

#include <iostream>
#include <string>


using namespace std;

const int MAX_COURSES = 100;
const int MAX_PREREQUISITES = 10;
const int MAX_SEQUENCES = 1000;

template<typename T>
class DynamicArray {
private:
    T* arr;
    int capacity;
    int size;

    void grow() {
        int newCap = (capacity > 0) ? capacity * 2 : 1;
        T* newArr = new T[newCap];
        for (int i = 0; i < size; ++i) newArr[i] = arr[i];
        delete[] arr;
        arr = newArr;
        capacity = newCap;
    }

public:
    DynamicArray() : arr(new T[10]), capacity(10), size(0) {}
    explicit DynamicArray(int initCap) : arr(new T[(initCap > 0 ? initCap : 1)]), capacity((initCap > 0 ? initCap : 1)), size(0) {}

    // Deep copy constructor
    DynamicArray(const DynamicArray& other)
        : arr(new T[other.capacity]), capacity(other.capacity), size(other.size)
    {
        for (int i = 0; i < size; ++i) arr[i] = other.arr[i];
    }

    // Copy assignment (deep copy)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        T* newArr = new T[other.capacity];
        for (int i = 0; i < other.size; ++i) newArr[i] = other.arr[i];
        delete[] arr;
        arr = newArr;
        capacity = other.capacity;
        size = other.size;
        return *this;
    }

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : arr(other.arr), capacity(other.capacity), size(other.size)
    {
        other.arr = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    // Move assignment
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] arr;
            arr = other.arr;
            capacity = other.capacity;
            size = other.size;
            other.arr = nullptr;
            other.capacity = 0;
            other.size = 0;
        }
        return *this;
    }

    ~DynamicArray() { delete[] arr; }

    void push(const T& value) {
        if (size >= capacity) grow();
        arr[size++] = value;
    }
    void push(T&& value) {
        if (size >= capacity) grow();
        arr[size++] = static_cast<T&&>(value);
    }
    void pop() { if (size > 0) --size; }

    T& operator[](int index) { return arr[index]; }
    const T& operator[](int index) const { return arr[index]; }

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
    Course(string code, string name, int cred);
    void addPrerequisite(string prereq);
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

    // Adjacency list representation
    struct AdjNode {
        int courseIndex;
        AdjNode* next;
    };
    AdjNode* adjacencyList[MAX_COURSES];

    // Prerequisite cache
    struct PrereqCache {
        string courseCode;
        bool canTake;
        bool isValid;
    };
    PrereqCache prereqCache[MAX_COURSES];
    int cacheSize;

    // Topological sort cache
    bool topoSortComputed;
    int topoSortResult[MAX_COURSES];
    int topoSortSize;

    // Helper functions
    int findCourseIndex(string code) const;
    bool hasCycleUtil(int courseIdx, bool visited[], bool recStack[]);
    bool hasCycle();
    void topologicalSortUtil(int courseIdx, bool visited[], int stack[], int& stackIndex);
    void generateSequencesRecursive(
        bool completed[],
        int completedCount,
        DynamicArray<DynamicArray<string>>& allSequences,
        DynamicArray<string>& currentSeq,
        int maxDepth,
        int maxSequences
    );
    bool canTakeCourse(int courseIdx, bool completed[]) const;

    // Cache helpers
    bool checkPrereqCache(string courseCode, bool& result) const;
    void addToPrereqCache(string courseCode, bool canTake);
    void invalidateCache();

public:
    CourseScheduler();
    ~CourseScheduler();
    void addCourse(string code, string name, int credits);
    void addPrerequisite(string courseCode, string prereqCode);
    bool validatePrerequisites();
    void generateAllValidSequences(int maxCourses);
    void displayTopologicalOrder();
    void displayAllCourses() const;
    int getCourseCount() const { return courseCount; }

    // Optimized functions
    bool canTakeCourseMemoized(string courseCode, bool completed[]);
    void getTopologicalOrderOptimized(int result[], int& resultSize);
};

#endif 