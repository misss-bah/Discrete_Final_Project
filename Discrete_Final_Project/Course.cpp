#include "Course.h"
using namespace std;

Course::Course() : credits(0), prereqCount(0) {}

Course::Course( string code,  string name, int cred)
    : courseCode(code), courseName(name), credits(cred), prereqCount(0) {
}

void Course::addPrerequisite( string prereq) {
    if (prereqCount < MAX_PREREQUISITES) {
        prerequisites[prereqCount++] = prereq;
    }
}

string Course::getPrerequisite(int index) const {
    if (index >= 0 && index < prereqCount) {
        return prerequisites[index];
    }
    return "";
}

void Course::display() const {
    cout << "Course Code: " << courseCode << endl;
    cout << "Course Name: " << courseName << endl;
    cout << "Credits: " << credits << endl;
    if (prereqCount > 0) {
        cout << "Prerequisites: ";
        for (int i = 0; i < prereqCount; i++) {
            cout << prerequisites[i];
            if (i < prereqCount - 1) cout << ", ";
        }
        cout << endl;
    }
}

// CourseScheduler implementation
CourseScheduler::CourseScheduler() : courseCount(0), cacheSize(0), topoSortComputed(false), topoSortSize(0) {
    for (int i = 0; i < MAX_COURSES; i++) {
        adjacencyList[i] = nullptr;
        prereqCache[i].isValid = false;
    }
}

CourseScheduler::~CourseScheduler() {
    for (int i = 0; i < MAX_COURSES; i++) {
        AdjNode* current = adjacencyList[i];
        while (current) {
            AdjNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

void CourseScheduler::addCourse( string code,  string name, int credits) {
    if (courseCount < MAX_COURSES) {
        courses[courseCount++] = Course(code, name, credits);
        invalidateCache(); // Invalidate cache when structure changes
    }
}

void CourseScheduler::addPrerequisite( string courseCode,  string prereqCode) {
    int courseIdx = findCourseIndex(courseCode);
    int prereqIdx = findCourseIndex(prereqCode);

    if (courseIdx != -1 && prereqIdx != -1) {
        courses[courseIdx].addPrerequisite(prereqCode);

        // Add to adjacency list (prereq -> course)
        AdjNode* newNode = new AdjNode;
        newNode->courseIndex = courseIdx;
        newNode->next = adjacencyList[prereqIdx];
        adjacencyList[prereqIdx] = newNode;

        invalidateCache(); // Invalidate cache
    }
}

int CourseScheduler::findCourseIndex( string code) const {
    for (int i = 0; i < courseCount; i++) {
        if (courses[i].getCode() == code) {
            return i;
        }
    }
    return -1;
}

bool CourseScheduler::hasCycleUtil(int courseIdx, bool visited[], bool recStack[]) {
    visited[courseIdx] = true;
    recStack[courseIdx] = true;

    AdjNode* current = adjacencyList[courseIdx];
    while (current) {
        if (!visited[current->courseIndex]) {
            if (hasCycleUtil(current->courseIndex, visited, recStack)) {
                return true;
            }
        }
        else if (recStack[current->courseIndex]) {
            return true;
        }
        current = current->next;
    }

    recStack[courseIdx] = false;
    return false;
}

bool CourseScheduler::hasCycle() {
    bool visited[MAX_COURSES] = { false };
    bool recStack[MAX_COURSES] = { false };

    for (int i = 0; i < courseCount; i++) {
        if (!visited[i]) {
            if (hasCycleUtil(i, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

bool CourseScheduler::validatePrerequisites() {
    if (hasCycle()) {
        cout << "Error: Circular dependency detected in prerequisites!" << endl;
        return false;
    }
    cout << "Prerequisites are valid (no circular dependencies)" << endl;
    return true;
}

void CourseScheduler::topologicalSortUtil(int courseIdx, bool visited[], int stack[], int& stackIndex) {
    visited[courseIdx] = true;

    AdjNode* current = adjacencyList[courseIdx];
    while (current) {
        if (!visited[current->courseIndex]) {
            topologicalSortUtil(current->courseIndex, visited, stack, stackIndex);
        }
        current = current->next;
    }

    stack[stackIndex++] = courseIdx;
}

void CourseScheduler::displayTopologicalOrder() {
    bool visited[MAX_COURSES] = { false };
    int stack[MAX_COURSES];
    int stackIndex = 0;

    for (int i = 0; i < courseCount; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack, stackIndex);
        }
    }

    cout << "\n=== Topological Order (Valid Course Sequence) ===" << endl;
    for (int i = stackIndex - 1; i >= 0; i--) {
        cout << (stackIndex - i) << ". " << courses[stack[i]].getCode()
            << " - " << courses[stack[i]].getName() << endl;
    }
}

bool CourseScheduler::canTakeCourse(int courseIdx, bool completed[]) const {
    for (int i = 0; i < courses[courseIdx].getPrereqCount(); i++) {
        string prereq = courses[courseIdx].getPrerequisite(i);
        int prereqIdx = findCourseIndex(prereq);
        if (prereqIdx != -1 && !completed[prereqIdx]) {
            return false;
        }
    }
    return true;
}

void CourseScheduler::generateSequencesRecursive(bool completed[], int completedCount, DynamicArray<DynamicArray<string>>& allSequences,DynamicArray<string>& currentSeq, int maxDepth) {
    if (completedCount >= maxDepth || completedCount >= courseCount) {
        allSequences.push(currentSeq);
        return;
    }

    bool foundAvailable = false;
    for (int i = 0; i < courseCount; i++) {
        if (!completed[i] && canTakeCourse(i, completed)) {
            foundAvailable = true;
            completed[i] = true;
            currentSeq.push(courses[i].getCode());
            generateSequencesRecursive(completed, completedCount + 1, allSequences, currentSeq, maxDepth);
            completed[i] = false;
            currentSeq.getSize() > 0 ? currentSeq.clear() : void();
        }
    }

    if (!foundAvailable && completedCount > 0) {
        allSequences.push(currentSeq);
    }
}

void CourseScheduler::generateAllValidSequences(int maxCourses) {
    DynamicArray<DynamicArray<string>> allSequences;
    DynamicArray<string> currentSeq;
    bool completed[MAX_COURSES] = { false };

    cout << "\n=== Generating Valid Course Sequences (Max " << maxCourses << " courses) ===" << endl;
    generateSequencesRecursive(completed, 0, allSequences, currentSeq, maxCourses);

    cout << "Total sequences generated: " << allSequences.getSize() << endl;
    for (int i = 0; i < allSequences.getSize() && i < 10; i++) {
        cout << "\nSequence " << (i + 1) << ": ";
        for (int j = 0; j < allSequences[i].getSize(); j++) {
            cout << allSequences[i][j];
            if (j < allSequences[i].getSize() - 1) cout << " -> ";
        }
        cout << endl;
    }

    if (allSequences.getSize() > 10) {
        cout << "... (showing first 10 sequences only)" << endl;
    }
}

void CourseScheduler::displayAllCourses() const {
    cout << "\n=== All Courses ===" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << "\n" << (i + 1) << ". ";
        courses[i].display();
    }
}

// ===== MODULE 10: CACHE HELPER FUNCTIONS =====

bool CourseScheduler::checkPrereqCache( string courseCode, bool& result) const {
    for (int i = 0; i < cacheSize; i++) {
        if (prereqCache[i].courseCode == courseCode && prereqCache[i].isValid) {
            result = prereqCache[i].canTake;
            return true;
        }
    }
    return false;
}

void CourseScheduler::addToPrereqCache( string courseCode, bool canTake) {
    if (cacheSize < MAX_COURSES) {
        prereqCache[cacheSize].courseCode = courseCode;
        prereqCache[cacheSize].canTake = canTake;
        prereqCache[cacheSize].isValid = true;
        cacheSize++;
    }
}

void CourseScheduler::invalidateCache() {
    cacheSize = 0;
    topoSortComputed = false;
    for (int i = 0; i < MAX_COURSES; i++) {
        prereqCache[i].isValid = false;
    }
}

// ===== MODULE 10: MEMOIZED PREREQUISITE CHECK =====
bool CourseScheduler::canTakeCourseMemoized( string courseCode, bool completed[]) {
    bool cachedResult;
    if (checkPrereqCache(courseCode, cachedResult)) {
        return cachedResult; // Return cached result - O(1)
    }

    int courseIdx = findCourseIndex(courseCode);
    if (courseIdx == -1) return false;

    bool result = canTakeCourse(courseIdx, completed);
    addToPrereqCache(courseCode, result);
    return result;
}

// ===== MODULE 10: OPTIMIZED TOPOLOGICAL SORT WITH MEMOIZATION =====
void CourseScheduler::getTopologicalOrderOptimized(int result[], int& resultSize) {
    if (topoSortComputed) {
        // Return cached result - O(1)
        for (int i = 0; i < topoSortSize; i++) {
            result[i] = topoSortResult[i];
        }
        resultSize = topoSortSize;
        return;
    }

    // Compute and cache
    bool visited[MAX_COURSES] = { false };
    int stack[MAX_COURSES];
    int stackIndex = 0;

    for (int i = 0; i < courseCount; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, stack, stackIndex);
        }
    }

    // Cache the result
    topoSortSize = stackIndex;
    for (int i = 0; i < stackIndex; i++) {
        topoSortResult[i] = stack[i];
        result[i] = stack[i];
    }
    resultSize = stackIndex;
    topoSortComputed = true;
}