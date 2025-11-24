#ifndef COURSE_H
#define	COURSE_H

#include<iostream>
#include<string>
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
	DynamicArray() : capacity(10), size(0) { arr = new T[capacity]; }
	~DynamicArray() { delete[] arr; }
	void push(const T& element) {
		if (size >= capacity) resize();
		arr[size++] = element;
	}
	T& operator[](int index) {
		return arr[index]; 
	}
	 T& operator[](int index) const {
		return arr[index]; 
	}

	int getSize() const {
		return size; }
	void clear() { size = 0; 
	}
	bool isEmpty() const {
		return size == 0;
	}

};
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

	void addPrerequisite( string prereq);
	string getCode() const;
	string getName() const;
	int getCredits() const;
	int getPrereqCount() const;
	string getPrerequisite(int index) const;

	void display() const;
 };
struct AdjNode {
	int courseIndex;
	AdjNode* next;
};
struct PrereqCache {
	string courseCode;
	bool canTake;
	bool isValid;
};
class CourseScheduler {
private:
	Course courses[MAX_COURSES];
	int courseCount;
	AdjNode* adjacencyList[MAX_COURSES];
	PrereqCache prereqCache[MAX_COURSES];
	int cacheSize;

	// ===== MODULE 10: DYNAMIC PROGRAMMING (without mutable) =====
	bool topoSortComputed;
	int topoSortResult[MAX_COURSES];
	int topoSortSize;

	int findCourseIndex(string code) const;
	bool hasCycleUtil(int courseIdx, bool visited[], bool recStack[]);
	bool hasCycle();
	void topologicalSortUtil(int courseIdx, bool visited[], int stack[], int& stackIndex);
	void generateSequencesRecursive(bool completed[], int completedCount,DynamicArray<DynamicArray<string>>& allSequences,DynamicArray<string>& currentSeq,int maxDepth);
	bool canTakeCourse(int courseIdx, bool completed[]) const;
	// ===== MODULE 10: CACHE HELPERS =====
	bool checkPrereqCache(const string& courseCode, bool& result) const;
	void addToPrereqCache(const string& courseCode, bool canTake);
	void invalidateCache();

public:
	CourseScheduler();
	~CourseScheduler();

	int getCourseCount() const;
	void addCourse( string code,  string name, int credits);
	void addPrerequisite( string courseCode,  string prereqCode);
	bool validatePrerequisites();
	void generateAllValidSequences(int maxCourses);
	void displayTopologicalOrder();
	void displayAllCourses() const;
	// ===== MODULE 10: OPTIMIZED FUNCTIONS =====
	bool canTakeCourseMemoized(const string& courseCode, bool completed[]);
	void getTopologicalOrderOptimized(int result[], int& resultSize); // Not const anymore
};

#endif 
