#ifndef INDUCTION_H
#define INDUCTION_H
#include"Course.h"
#include <iostream>
#include <string>
using namespace std;

const int MAX_COURSE_CHAIN = 50;
const int MAX_PROOF_STEPS = 100;

class PrerequisiteChain {
private:
    string courses[MAX_COURSE_CHAIN];
    int chainLength;

public:
    PrerequisiteChain();

    void addCourse(const string& course);
    int getLength() const { return chainLength; }
    string getCourse(int index) const;
    void display() const;
    void clear();
};

class InductionProver {
private:
    string proofSteps[MAX_PROOF_STEPS];
    int stepCount;

    void addProofStep(const string& step);
    void clearProof();

public:
    InductionProver();

    // Mathematical Induction
    bool verifyPrerequisiteChain(const PrerequisiteChain& chain, const string& targetCourse);
    void proveByInduction(int n, const string& formula);

    // Strong Induction
    bool verifyMultiTermPrerequisites(const PrerequisiteChain& chain);
    bool strongInductionVerify(const string& targetCourse,
        const string prerequisites[],
        int prereqCount,
        const string allCourses[],
        int totalCourses);

    // Recursive verification
    bool recursivePrereqCheck(const string& course,
        const string prerequisites[][MAX_COURSE_CHAIN],
        const int prereqCounts[],
        const string allCourses[],
        int totalCourses,
        bool completed[],
        int depth);

    void displayProof() const;
    int getStepCount() const { return stepCount; }
};

class InductionModule {
private:
    InductionProver prover;
    PrerequisiteChain chains[MAX_COURSE_CHAIN];
    int chainCount;

    // Course prerequisite storage
    string courseList[MAX_COURSES];
    string prerequisites[MAX_COURSES][MAX_COURSE_CHAIN];
    int prereqCounts[MAX_COURSES];
    int courseCount;

    int findCourseIndex(const string& course) const;

public:
    InductionModule();

    void addCourseWithPrereqs(const string& course, const string prereqs[], int prereqCount);
    void createPrerequisiteChain(const string& startCourse, const string& endCourse);
    bool verifyCanTakeCourse(const string& targetCourse, const string completedCourses[], int completedCount);
    bool verifyIndirectPrerequisites(const string& course);

    void demonstrateBaseCase();
    void demonstrateInductiveStep();
    void runInductionExample();

    void displayAllChains() const;
    void displayCoursePrerequisites() const;
};

#endif