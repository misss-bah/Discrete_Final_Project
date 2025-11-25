#include "LogicEngine.h"

// ------------------- LogicRule -------------------

LogicRule::LogicRule() {
    antecedent = "";
    consequent = "";
    ruleDescription = "";
    isActive = true;
}

LogicRule::LogicRule(const string& ante, const string& cons, const string& desc) {
    antecedent = ante;
    consequent = cons;
    ruleDescription = desc;
    isActive = true;
}

bool LogicRule::evaluate(const string facts[], int factCount) const {
    for (int i = 0; i < factCount; i++) {
        if (facts[i] == antecedent) return true;
    }
    return false;
}

void LogicRule::display() const {
    cout << "IF " << antecedent << " THEN " << consequent;
    if (ruleDescription != "") cout << " [" << ruleDescription << "]";
    cout << " Status: " << (isActive ? "Active" : "Inactive") << endl;
}

// ------------------- InferenceEngine -------------------

InferenceEngine::InferenceEngine() {
    ruleCount = 0;
    factCount = 0;
    logCount = 0;
}

bool InferenceEngine::containsFact(const string& fact) const {
    for (int i = 0; i < factCount; i++) {
        if (facts[i] == fact) return true;
    }
    return false;
}

void InferenceEngine::addInferenceLog(const string& log) {
    if (logCount < MAX_RULES) {
        inferenceLog[logCount] = log;
        logCount++;
    }
}

void InferenceEngine::addRule(const string& antecedent, const string& consequent, const string& description) {
    if (ruleCount < MAX_RULES) {
        rules[ruleCount] = LogicRule(antecedent, consequent, description);
        ruleCount++;
    }
}

void InferenceEngine::addFact(const string& fact) {
    if (!containsFact(fact) && factCount < MAX_VARIABLES) {
        facts[factCount] = fact;
        factCount++;
    }
}

void InferenceEngine::clearFacts() {
    factCount = 0;
}

bool InferenceEngine::forwardChaining() {
    bool newFactAdded = false;
    for (int i = 0; i < ruleCount; i++) {
        if (rules[i].getActive() && rules[i].evaluate(facts, factCount)) {
            if (!containsFact(rules[i].getConsequent())) {
                addFact(rules[i].getConsequent());
                addInferenceLog("Forward: " + rules[i].getAntecedent() + " -> " + rules[i].getConsequent());
                newFactAdded = true;
            }
        }
    }
    return newFactAdded;
}

bool InferenceEngine::backwardChaining(const string& goal) {
    if (containsFact(goal)) return true;

    for (int i = 0; i < ruleCount; i++) {
        if (rules[i].getConsequent() == goal) {
            if (backwardChaining(rules[i].getAntecedent())) {
                addFact(goal);
                addInferenceLog("Backward: " + rules[i].getAntecedent() + " -> " + goal);
                return true;
            }
        }
    }
    return false;
}

void InferenceEngine::modusPonens(const string& p, const string& implication) {
    string q = implication;
    if (containsFact(p) && !containsFact(q)) {
        addFact(q);
        addInferenceLog("Modus Ponens: " + p + " -> " + q);
    }
}

void InferenceEngine::modusTollens(const string& notQ, const string& implication) {
    string p = implication;
    if (containsFact(notQ) && !containsFact(p)) {
        addFact(p);
        addInferenceLog("Modus Tollens: " + notQ + " -> " + p);
    }
}

void InferenceEngine::displayRules() const {
    cout << "Rules:" << endl;
    for (int i = 0; i < ruleCount; i++) rules[i].display();
}

void InferenceEngine::displayFacts() const {
    cout << "Facts: ";
    for (int i = 0; i < factCount; i++) cout << facts[i] << " ";
    cout << endl;
}

void InferenceEngine::displayInferenceLog() const {
    cout << "Inference Log:" << endl;
    for (int i = 0; i < logCount; i++) cout << inferenceLog[i] << endl;
}

// ------------------- LogicModule -------------------

LogicModule::LogicModule() {
    assignmentCount = 0;
}

void LogicModule::addAssignment(const string& course, const string& faculty, const string& room) {
    if (assignmentCount < MAX_COURSES) {
        assignments[assignmentCount].course = course;
        assignments[assignmentCount].faculty = faculty;
        assignments[assignmentCount].room = room;
        assignmentCount++;
    }
}

void LogicModule::setupUniversityRules() {
    engine.addRule("LabAvailable", "AssignFaculty", "If lab is available, assign faculty");
    engine.addRule("FacultyFree", "AllocateRoom", "If faculty is free, allocate room");
}

bool LogicModule::verifyFacultyAssignment(const string& faculty, const string& course, const string& expectedLab) {
    for (int i = 0; i < assignmentCount; i++) {
        if (assignments[i].faculty == faculty && assignments[i].course == course)
            return assignments[i].room == expectedLab;
    }
    return false;
}

bool LogicModule::detectConflicts() {
    for (int i = 0; i < assignmentCount; i++) {
        for (int j = i + 1; j < assignmentCount; j++) {
            if (assignments[i].room == assignments[j].room) return true;
        }
    }
    return false;
}

bool LogicModule::checkRoomAllocation(const string& course) {
    for (int i = 0; i < assignmentCount; i++) {
        if (assignments[i].course == course) return true;
    }
    return false;
}

void LogicModule::parseCourseRule(const string& rule) {
    cout << "Parsing course rule: " << rule << endl;
}

void LogicModule::enforcePolicy(const string& policy) {
    cout << "Enforcing policy: " << policy << endl;
}

void LogicModule::demonstrateTautology() {
    cout << "\n=== Tautology Demonstration ===" << endl;
    cout << "Statement: A OR (NOT A)" << endl;
    cout << "Truth Table:" << endl;
    cout << "A | NOT A | A OR (NOT A)" << endl;
    cout << "---------" << endl;
    cout << "T |  F   |     T      (when A is true, A OR NOT A = true)" << endl;
    cout << "F |  T   |     T      (when A is false, NOT A is true, so A OR NOT A = true)" << endl;
    cout << "Result: TAUTOLOGY (always true regardless of A's value)" << endl;
}

void LogicModule::demonstrateContradiction() {
    cout << "\n=== Contradiction Demonstration ===" << endl;
    cout << "Statement: A AND (NOT A)" << endl;
    cout << "Truth Table:" << endl;
    cout << "A | NOT A | A AND (NOT A)" << endl;
    cout << "-----------" << endl;
    cout << "T |  F   |      F      (when A is true, NOT A is false, so A AND NOT A = false)" << endl;
    cout << "F |  T   |      F      (when A is false, A is false, so A AND NOT A = false)" << endl;
    cout << "Result: CONTRADICTION (always false regardless of A's value)" << endl;
}

void LogicModule::demonstrateLogicalEquivalence() {
    cout << "\n=== Logical Equivalence Demonstration (DeMorgan's Law) ===" << endl;
    cout << "Statement 1: NOT (A AND B)" << endl;
    cout << "Statement 2: (NOT A) OR (NOT B)" << endl;
    cout << "\nTruth Table:" << endl;
    cout << "A | B | A AND B | NOT(A AND B) | NOT A | NOT B | (NOT A) OR (NOT B)" << endl;
    cout << "---" << endl;
    cout << "T | T |    T    |      F       |  F   |  F   |         F" << endl;
    cout << "T | F |    F    |      T       |  F   |  T   |         T" << endl;
    cout << "F | T |    F    |      T       |  T   |  F   |         T" << endl;
    cout << "F | F |    F    |      T       |  T   |  T   |         T" << endl;
    cout << "\nConclusion: NOT(A AND B) ? (NOT A) OR (NOT B) [DeMorgan's Law]" << endl;
}

void LogicModule::displayAllAssignments() const {
    cout << "Assignments:" << endl;
    for (int i = 0; i < assignmentCount; i++) {
        cout << "Course: " << assignments[i].course
            << ", Faculty: " << assignments[i].faculty            << ", Room: " << assignments[i].room << endl;
    }
}

void LogicModule::runLogicDemo() {
    cout << "Running Logic Demo..." << endl;
    setupUniversityRules();
    engine.forwardChaining();
    engine.backwardChaining("AssignFaculty");
    engine.displayFacts();
    engine.displayInferenceLog();
}
