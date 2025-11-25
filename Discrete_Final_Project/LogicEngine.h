#ifndef LOGICENGINE_H
#define LOGICENGINE_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_RULES = 100;
const int MAX_VARIABLES = 50;
const int MAX_CLAUSES = 20;

// Proposition structure
struct Proposition {
    string variable;
    bool value;
    bool isNegated;
};

// Logic Rule (If-Then structure)
class LogicRule {
private:
    string antecedent;  // If part
    string consequent;  // Then part
    string ruleDescription;
    bool isActive;

public:
    LogicRule();
    LogicRule(const string& ante, const string& cons, const string& desc);

    bool evaluate(const string facts[], int factCount) const;
    string getAntecedent() const { return antecedent; }
    string getConsequent() const { return consequent; }
    string getDescription() const { return ruleDescription; }
    void display() const;
    void setActive(bool active) { isActive = active; }
    bool getActive() const { return isActive; }
};

// Inference Engine
class InferenceEngine {
private:
    LogicRule rules[MAX_RULES];
    int ruleCount;

    string facts[MAX_VARIABLES];
    int factCount;

    string inferenceLog[MAX_RULES];
    int logCount;

    bool containsFact(const string& fact) const;
    void addInferenceLog(const string& log);
    bool backwardChainingHelper(const string& goal, int depth);

public:
    InferenceEngine();

    void addRule(const string& antecedent, const string& consequent, const string& description);
    void addFact(const string& fact);
    void clearFacts();

    bool forwardChaining();
    bool backwardChaining(const string& goal);
    void modusPonens(const string& p, const string& implication);
    void modusTollens(const string& notQ, const string& implication);

    void displayRules() const;
    void displayFacts() const;
    void displayInferenceLog() const;

    int getRuleCount() const { return ruleCount; }
    int getFactCount() const { return factCount; }
};

// Logic Module for FAST University
class LogicModule {
private:
    InferenceEngine engine;

    // Course-Faculty-Room mappings
    struct Assignment {
        string course;
        string faculty;
        string room;
    };
    Assignment assignments[100];
    int assignmentCount;

public:
    LogicModule();

    void setupUniversityRules();
    void addAssignment(const string& course, const string& faculty, const string& room);

    bool verifyFacultyAssignment(const string& faculty, const string& course, const string& expectedLab);
    bool detectConflicts();
    bool checkRoomAllocation(const string& course);

    void parseCourseRule(const string& rule);
    void enforcePolicy(const string& policy);

    void demonstrateTautology();
    void demonstrateContradiction();
    void demonstrateLogicalEquivalence();

    void displayAllAssignments() const;
    void runLogicDemo();
};

#endif