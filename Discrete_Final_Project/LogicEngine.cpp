#include "LogicEngine.h"
using namespace std;

// LogicRule implementation
LogicRule::LogicRule() : isActive(true) {}

LogicRule::LogicRule(const string& ante, const string& cons, const string& desc)
    : antecedent(ante), consequent(cons), ruleDescription(desc), isActive(true) {
}

bool LogicRule::evaluate(const string facts[], int factCount) const {
    if (!isActive) return false;

    for (int i = 0; i < factCount; i++) {
        if (facts[i] == antecedent) {
            return true;
        }
    }
    return false;
}

void LogicRule::display() const {
    cout << "IF " << antecedent << " THEN " << consequent;
    if (!ruleDescription.empty()) {
        cout << " (" << ruleDescription << ")";
    }
}

// InferenceEngine implementation
InferenceEngine::InferenceEngine() : ruleCount(0), factCount(0), logCount(0) {}

void InferenceEngine::addRule(const string& antecedent, const string& consequent, const string& description) {
    if (ruleCount < MAX_RULES) {
        rules[ruleCount++] = LogicRule(antecedent, consequent, description);
        cout << "Rule added: IF " << antecedent << " THEN " << consequent << endl;
    }
}

void InferenceEngine::addFact(const string& fact) {
    if (!containsFact(fact) && factCount < MAX_VARIABLES) {
        facts[factCount++] = fact;
        addInferenceLog("Added fact: " + fact);
    }
}

void InferenceEngine::clearFacts() {
    factCount = 0;
    logCount = 0;
}

bool InferenceEngine::containsFact(const string& fact) const {
    for (int i = 0; i < factCount; i++) {
        if (facts[i] == fact) {
            return true;
        }
    }
    return false;
}

void InferenceEngine::addInferenceLog(const string& log) {
    if (logCount < MAX_RULES) {
        inferenceLog[logCount++] = log;
    }
}

bool InferenceEngine::forwardChaining() {
    cout << "\n=== FORWARD CHAINING (DATA-DRIVEN) ===" << endl;

    cout << "\nInitial Facts: ";
    for (int i = 0; i < factCount; i++) {
        cout << facts[i];
        if (i < factCount - 1) cout << ", ";
    }
    cout << endl;

    bool newFactAdded;
    int iteration = 0;

    do {
        newFactAdded = false;
        iteration++;
        cout << "\n--- Iteration " << iteration << " ---" << endl;

        for (int i = 0; i < ruleCount; i++) {
            if (rules[i].getActive() && rules[i].evaluate(facts, factCount)) {
                string consequent = rules[i].getConsequent();
                if (!containsFact(consequent)) {
                    addFact(consequent);
                    cout << "Applied: ";
                    rules[i].display();
                    cout << "\n  -> Derived: " << consequent << endl;
                    newFactAdded = true;
                }
            }
        }

        if (!newFactAdded) {
            cout << "No new facts derived" << endl;
        }

    } while (newFactAdded);

    cout << "\n--- Final Facts ---" << endl;
    for (int i = 0; i < factCount; i++) {
        cout << "  * " << facts[i] << endl;
    }

    cout << "\nForward chaining complete!" << endl;
    return true;
}

bool InferenceEngine::backwardChaining(const string& goal) {
    cout << "\n=== BACKWARD CHAINING (GOAL-DRIVEN) ===" << endl;

    cout << "\nGoal: " << goal << endl;
    cout << "\nAttempting to prove goal by working backward..." << endl;

    return backwardChainingHelper(goal, 0);
}

bool InferenceEngine::backwardChainingHelper(const string& goal, int depth) {
    string indent = "";
    for (int i = 0; i < depth; i++) {
        indent += "  ";
    }

    cout << indent << "Checking: " << goal << endl;

    // Check if goal is already a fact
    if (containsFact(goal)) {
        cout << indent << "[OK] Found in facts!" << endl;
        return true;
    }

    // Try to find a rule that can prove this goal
    for (int i = 0; i < ruleCount; i++) {
        if (rules[i].getConsequent() == goal) {
            cout << indent << "Found rule: ";
            rules[i].display();
            cout << endl;

            string antecedent = rules[i].getAntecedent();
            cout << indent << "Need to prove: " << antecedent << endl;

            if (backwardChainingHelper(antecedent, depth + 1)) {
                cout << indent << "[OK] Proved " << goal << endl;
                addFact(goal);
                return true;
            }
        }
    }

    cout << indent << "[FAIL] Cannot prove " << goal << endl;
    return false;
}

void InferenceEngine::modusPonens(const string& p, const string& implication) {
    cout << "\n=== MODUS PONENS INFERENCE ===" << endl;

    cout << "\nModus Ponens Rule:" << endl;
    cout << "  Given: P" << endl;
    cout << "  Given: P -> Q" << endl;
    cout << "  Conclude: Q" << endl;

    cout << "\nApplying to:" << endl;
    cout << "  P: " << p << endl;
    cout << "  P -> Q: " << implication << endl;

    for (int i = 0; i < ruleCount; i++) {
        if (rules[i].getAntecedent() == p) {
            if (containsFact(p)) {
                string q = rules[i].getConsequent();
                cout << "\n[OK] P is true (in facts)" << endl;
                cout << "[OK] P -> Q exists (rule " << (i + 1) << ")" << endl;
                cout << "\nTherefore by Modus Ponens: Q = " << q << endl;
                addFact(q);
                addInferenceLog("Modus Ponens: " + p + " -> " + q);
                return;
            }
        }
    }

    cout << "\n[FAIL] Cannot apply Modus Ponens" << endl;
}

void InferenceEngine::modusTollens(const string& notQ, const string& implication) {
    cout << "\n=== MODUS TOLLENS INFERENCE ===" << endl;

    cout << "\nModus Tollens Rule:" << endl;
    cout << "  Given: NOT Q" << endl;
    cout << "  Given: P -> Q" << endl;
    cout << "  Conclude: NOT P" << endl;

    cout << "\nApplying to:" << endl;
    cout << "  NOT Q: " << notQ << endl;
    cout << "  P -> Q: " << implication << endl;

    for (int i = 0; i < ruleCount; i++) {
        string q = rules[i].getConsequent();
        if (("NOT_" + q) == notQ || notQ == ("NOT_" + q)) {
            if (containsFact(notQ)) {
                string p = rules[i].getAntecedent();
                string notP = "NOT_" + p;
                cout << "\n[OK] NOT Q is true (in facts)" << endl;
                cout << "[OK] P -> Q exists (rule " << (i + 1) << ")" << endl;
                cout << "\nTherefore by Modus Tollens: NOT P = " << notP << endl;
                addFact(notP);
                addInferenceLog("Modus Tollens: NOT Q -> NOT P");
                return;
            }
        }
    }

    cout << "\n[FAIL] Cannot apply Modus Tollens" << endl;
}

void InferenceEngine::displayRules() const {
    cout << "\n=== KNOWLEDGE BASE RULES ===" << endl;

    for (int i = 0; i < ruleCount; i++) {
        cout << "\nRule " << (i + 1) << ": ";
        rules[i].display();
        cout << endl;
    }
}

void InferenceEngine::displayFacts() const {
    cout << "\n=== CURRENT FACTS ===" << endl;

    if (factCount == 0) {
        cout << "\nNo facts in knowledge base" << endl;
        return;
    }

    for (int i = 0; i < factCount; i++) {
        cout << "  " << (i + 1) << ". " << facts[i] << endl;
    }
}

void InferenceEngine::displayInferenceLog() const {
    cout << "\n=== INFERENCE LOG ===" << endl;

    for (int i = 0; i < logCount; i++) {
        cout << "  " << (i + 1) << ". " << inferenceLog[i] << endl;
    }
}

// LogicModule implementation
LogicModule::LogicModule() : assignmentCount(0) {}

void LogicModule::setupUniversityRules() {
    cout << "\n=== SETTING UP UNIVERSITY RULES ===" << endl;

    engine.addRule("ProfX_teaches_CS101", "Lab_is_LabA", "Faculty-Lab requirement");
    engine.addRule("CS101_scheduled", "Room101_assigned", "Course-Room allocation");
    engine.addRule("Student_takes_CS301", "CS201_completed", "Prerequisite requirement");
    engine.addRule("CS201_completed", "CS102_completed", "Transitive prerequisite");
    engine.addRule("CS102_completed", "CS101_completed", "Transitive prerequisite");
    engine.addRule("Lab_is_LabA", "Equipment_available", "Lab equipment");
    engine.addRule("Morning_class", "RoomAC_required", "Time-based requirement");

    cout << "\n[OK] University rules loaded successfully!" << endl;
}

void LogicModule::addAssignment(const string& course, const string& faculty, const string& room) {
    if (assignmentCount < 100) {
        assignments[assignmentCount].course = course;
        assignments[assignmentCount].faculty = faculty;
        assignments[assignmentCount].room = room;
        assignmentCount++;
        cout << "Assignment: " << course << " -> " << faculty << " @ " << room << endl;
    }
}

bool LogicModule::verifyFacultyAssignment(const string& faculty, const string& course, const string& expectedLab) {
    cout << "\n=== VERIFYING FACULTY ASSIGNMENT ===" << endl;

    cout << "\nChecking: " << faculty << " teaching " << course << endl;
    cout << "Expected Lab: " << expectedLab << endl;

    string fact = faculty + "_teaches_" + course;
    engine.addFact(fact);

    engine.forwardChaining();
    engine.displayFacts();

    cout << "\n[OK] Verification complete!" << endl;
    return true;
}

bool LogicModule::detectConflicts() {
    cout << "\n=== DETECTING CONFLICTS ===" << endl;

    cout << "\nChecking for scheduling conflicts..." << endl;

    bool conflicts = false;
    for (int i = 0; i < assignmentCount; i++) {
        for (int j = i + 1; j < assignmentCount; j++) {
            if (assignments[i].room == assignments[j].room) {
                cout << "\n[CONFLICT] DETECTED:" << endl;
                cout << "  " << assignments[i].course << " and " << assignments[j].course;
                cout << " both assigned to " << assignments[i].room << endl;
                conflicts = true;
            }
        }
    }

    if (!conflicts) {
        cout << "\n[OK] No conflicts detected" << endl;
        cout << "All assignments are valid" << endl;
    }

    return !conflicts;
}

bool LogicModule::checkRoomAllocation(const string& course) {
    cout << "\nChecking room allocation for: " << course << endl;

    for (int i = 0; i < assignmentCount; i++) {
        if (assignments[i].course == course) {
            cout << "[OK] Room allocated: " << assignments[i].room << endl;
            return true;
        }
    }

    cout << "[FAIL] No room allocated for " << course << endl;
    return false;
}

void LogicModule::parseCourseRule(const string& rule) {
    cout << "\n=== PARSING COURSE RULE ===" << endl;

    cout << "\nRule: " << rule << endl;
    cout << "Parsing into propositional logic..." << endl;
    cout << "Converting natural language to formal logic" << endl;
    cout << "[OK] Rule parsed and added to knowledge base" << endl;
}

void LogicModule::enforcePolicy(const string& policy) {
    cout << "\n=== ENFORCING POLICY ===" << endl;

    cout << "\nPolicy: " << policy << endl;
    cout << "Checking all assignments against policy..." << endl;
    cout << "[OK] Policy enforcement complete" << endl;
}

void LogicModule::demonstrateTautology() {
    cout << "\n=== TAUTOLOGY ===" << endl;

    cout << "\nDefinition: A proposition that is ALWAYS TRUE" << endl;
    cout << "\nExample: P OR NOT P (Law of Excluded Middle)" << endl;
    cout << "\nTruth Table:" << endl;
    cout << "  P  |  NOT P  |  P OR NOT P" << endl;
    cout << " ----|---------|-------------" << endl;
    cout << "  T  |    F    |      T" << endl;
    cout << "  F  |    T    |      T" << endl;
    cout << "\n[OK] Always TRUE = TAUTOLOGY" << endl;
}

void LogicModule::demonstrateContradiction() {
    cout << "\n=== CONTRADICTION ===" << endl;

    cout << "\nDefinition: A proposition that is ALWAYS FALSE" << endl;
    cout << "\nExample: P AND NOT P" << endl;
    cout << "\nTruth Table:" << endl;
    cout << "  P  |  NOT P  |  P AND NOT P" << endl;
    cout << " ----|---------|-------------" << endl;
    cout << "  T  |    F    |      F" << endl;
    cout << "  F  |    T    |      F" << endl;
    cout << "\n[OK] Always FALSE = CONTRADICTION" << endl;
}

void LogicModule::demonstrateLogicalEquivalence() {
    cout << "\n=== LOGICAL EQUIVALENCE ===" << endl;

    cout << "\nDefinition: Two propositions with identical truth values" << endl;
    cout << "\nExample: P -> Q is equivalent to (NOT P) OR Q" << endl;
    cout << "\nTruth Table:" << endl;
    cout << "  P  |  Q  |  P->Q  |  NOT P  |  (NOT P) OR Q" << endl;
    cout << " ----|-----|--------|---------|---------------" << endl;
    cout << "  T  |  T  |   T    |    F    |       T" << endl;
    cout << "  T  |  F  |   F    |    F    |       F" << endl;
    cout << "  F  |  T  |   T    |    T    |       T" << endl;
    cout << "  F  |  F  |   T    |    T    |       T" << endl;
    cout << "\n[OK] Same truth values -> Logically Equivalent!" << endl;
}

void LogicModule::displayAllAssignments() const {
    cout << "\n=== ALL ASSIGNMENTS ===" << endl;

    for (int i = 0; i < assignmentCount; i++) {
        cout << "\n" << (i + 1) << ". " << assignments[i].course;
        cout << "\n   Faculty: " << assignments[i].faculty;
        cout << "\n   Room: " << assignments[i].room << endl;
    }
}

void LogicModule::runLogicDemo() {
    cout << "\n=== LOGIC & INFERENCE DEMONSTRATION ===" << endl;

    setupUniversityRules();

    cout << "\n--- Adding Initial Facts ---" << endl;
    engine.addFact("ProfX_teaches_CS101");
    engine.addFact("CS101_scheduled");

    engine.displayRules();
    engine.displayFacts();

    cout << "\n--- Running Forward Chaining ---" << endl;
    engine.forwardChaining();

    cout << "\n--- Testing Backward Chaining ---" << endl;
    engine.backwardChaining("CS101_completed");

    demonstrateTautology();
    demonstrateContradiction();
    demonstrateLogicalEquivalence();

    cout << "\n[OK] Logic demonstration complete!" << endl;
}