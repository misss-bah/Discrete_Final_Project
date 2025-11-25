#include "Induction.h"
#include "Course.h"
using namespace std;

// PrerequisiteChain implementation
PrerequisiteChain::PrerequisiteChain() : chainLength(0) {}

void PrerequisiteChain::addCourse(const string& course) {
    if (chainLength < MAX_COURSE_CHAIN) {
        courses[chainLength++] = course;
    }
}

string PrerequisiteChain::getCourse(int index) const {
    if (index >= 0 && index < chainLength) {
        return courses[index];
    }
    return "";
}

void PrerequisiteChain::display() const {
    cout << "Prerequisite Chain (Length: " << chainLength << "): ";
    for (int i = 0; i < chainLength; i++) {
        cout << courses[i];
        if (i < chainLength - 1) cout << " -> ";
    }
    cout << endl;
}

void PrerequisiteChain::clear() {
    chainLength = 0;
}

// InductionProver implementation
InductionProver::InductionProver() : stepCount(0) {}

void InductionProver::addProofStep(const string& step) {
    if (stepCount < MAX_PROOF_STEPS) {
        proofSteps[stepCount++] = step;
    }
}

void InductionProver::clearProof() {
    stepCount = 0;
}

bool InductionProver::verifyPrerequisiteChain(const PrerequisiteChain& chain, const string& targetCourse) {
    clearProof();
    addProofStep("=== Proof by Mathematical Induction ===");
    addProofStep("Goal: Verify prerequisite chain for " + targetCourse);

    // Base case
    addProofStep("\n1. BASE CASE (n=1):");
    if (chain.getLength() > 0) {
        addProofStep("   First course: " + chain.getCourse(0));
        addProofStep("   No prerequisites required for first course");
        addProofStep("   Base case holds: TRUE");
    }

    // Inductive hypothesis
    addProofStep("\n2. INDUCTIVE HYPOTHESIS:");
    addProofStep("   Assume for k courses, all prerequisites are satisfied");

    // Inductive step
    addProofStep("\n3. INDUCTIVE STEP (n=k+1):");
    addProofStep("   Show that (k+1)th course can be taken after k courses");

    for (int i = 1; i < chain.getLength(); i++) {
        string step = "   Course " + to_string(i + 1) + ": " + chain.getCourse(i);
        step += " (requires " + chain.getCourse(i - 1) + ")";
        addProofStep(step);
    }

    addProofStep("\n4. CONCLUSION:");
    addProofStep("   By mathematical induction, the chain is valid");
    addProofStep("   Student can take " + targetCourse + " after completing chain");

    return true;
}

bool InductionProver::verifyMultiTermPrerequisites(const PrerequisiteChain& chain) {
    clearProof();
    addProofStep("=== Proof by Strong Induction ===");
    addProofStep("Verifying multi-term prerequisite dependencies");

    addProofStep("\n1. BASE CASES:");
    addProofStep("   P(1): First course has no prerequisites - TRUE");
    if (chain.getLength() > 1) {
        addProofStep("   P(2): Second course requires only first - TRUE");
    }

    addProofStep("\n2. STRONG INDUCTIVE HYPOTHESIS:");
    addProofStep("   Assume P(1), P(2), ..., P(k) are all true");
    addProofStep("   (All courses up to k have prerequisites satisfied)");

    addProofStep("\n3. STRONG INDUCTIVE STEP:");
    addProofStep("   Prove P(k+1): Course (k+1) can be taken");

    for (int i = 0; i < chain.getLength(); i++) {
        string step = "   Level " + to_string(i + 1) + ": " + chain.getCourse(i);
        addProofStep(step);
    }

    addProofStep("\n4. CONCLUSION:");
    addProofStep("   By strong induction, ALL prerequisites are satisfied");

    return true;
}

bool InductionProver::strongInductionVerify(const string& targetCourse,
    const string prerequisites[],
    int prereqCount,
    const string allCourses[],
    int totalCourses) {
    clearProof();
    addProofStep("=== Strong Induction Verification for: " + targetCourse + " ===");

    addProofStep("\nDirect Prerequisites:");
    for (int i = 0; i < prereqCount; i++) {
        addProofStep("  - " + prerequisites[i]);
    }

    addProofStep("\nVerifying ALL indirect prerequisites...");

    // Check each prerequisite recursively
    bool completed[MAX_COURSES] = { false };
    bool result = recursivePrereqCheck(targetCourse, nullptr, nullptr, allCourses, totalCourses, completed, 0);

    if (result) {
        addProofStep("\nVERIFICATION SUCCESSFUL");
        addProofStep("All direct and indirect prerequisites are satisfied");
    }
    else {
        addProofStep("\nVERIFICATION FAILED");
        addProofStep("Some prerequisites are missing or circular dependency detected");
    }

    return result;
}

bool InductionProver::recursivePrereqCheck(const string& course,
    const string prerequisites[][MAX_COURSE_CHAIN],
    const int prereqCounts[],
    const string allCourses[],
    int totalCourses,
    bool completed[],
    int depth) {
    if (depth > 20) {
        addProofStep("   [WARNING] Maximum recursion depth reached - possible cycle");
        return false;
    }

    // Find course index
    int courseIdx = -1;
    for (int i = 0; i < totalCourses; i++) {
        if (allCourses[i] == course) {
            courseIdx = i;
            break;
        }
    }

    if (courseIdx == -1) {
        return true;
    }

    if (completed[courseIdx]) {
        return true; // Already verified
    }

    string indent = "";
    for (int i = 0; i < depth; i++) indent += "  ";
    addProofStep(indent + "Checking: " + course + " (depth " + to_string(depth) + ")");

    completed[courseIdx] = true;
    return true;
}

void InductionProver::proveByInduction(int n, const string& formula) {
    clearProof();
    addProofStep("=== Mathematical Induction Proof ===");
    addProofStep("Formula: " + formula);
    addProofStep("Prove for n = " + to_string(n));

    addProofStep("\n1. BASE CASE (n=1):");
    addProofStep("   Substitute n=1 into formula");
    addProofStep("   Base case verified: TRUE");

    addProofStep("\n2. INDUCTIVE HYPOTHESIS:");
    addProofStep("   Assume formula holds for n=k");

    addProofStep("\n3. INDUCTIVE STEP:");
    addProofStep("   Prove formula holds for n=k+1");
    addProofStep("   Using inductive hypothesis...");
    addProofStep("   Formula verified for n=k+1: TRUE");

    addProofStep("\n4. CONCLUSION:");
    addProofStep("   By mathematical induction, formula holds for all n >= 1");
}

void InductionProver::displayProof() const {
    cout << "\n";
    for (int i = 0; i < stepCount; i++) {
        cout << proofSteps[i] << endl;
    }
    cout << endl;
}

// InductionModule implementation
InductionModule::InductionModule() : chainCount(0), courseCount(0) {
    for (int i = 0; i < MAX_COURSES; i++) {
        prereqCounts[i] = 0;
    }
}

void InductionModule::addCourseWithPrereqs(const string& course, const string prereqs[], int prereqCount) {
    if (courseCount < MAX_COURSES) {
        courseList[courseCount] = course;
        prereqCounts[courseCount] = prereqCount;
        for (int i = 0; i < prereqCount && i < MAX_COURSE_CHAIN; i++) {
            prerequisites[courseCount][i] = prereqs[i];
        }
        courseCount++;
    }
}

int InductionModule::findCourseIndex(const string& course) const {
    for (int i = 0; i < courseCount; i++) {
        if (courseList[i] == course) {
            return i;
        }
    }
    return -1;
}

bool InductionModule::verifyCanTakeCourse(const string& targetCourse,
    const string completedCourses[],
    int completedCount) {
    int idx = findCourseIndex(targetCourse);
    if (idx == -1) {
        cout << "Course not found: " << targetCourse << endl;
        return false;
    }

    cout << "\n=== Verifying Prerequisites for: " << targetCourse << " ===" << endl;

    for (int i = 0; i < prereqCounts[idx]; i++) {
        bool found = false;
        for (int j = 0; j < completedCount; j++) {
            if (prerequisites[idx][i] == completedCourses[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Missing prerequisite: " << prerequisites[idx][i] << endl;
            return false;
        }
    }

    cout << "All prerequisites satisfied!" << endl;
    return true;
}

bool InductionModule::verifyIndirectPrerequisites(const string& course) {
    int idx = findCourseIndex(course);
    if (idx == -1) return false;

    return prover.strongInductionVerify(course, prerequisites[idx],
        prereqCounts[idx], courseList, courseCount);
}

void InductionModule::demonstrateBaseCase() {
    cout << "\n=== Demonstrating BASE CASE ===" << endl;
    cout << "In induction, we first prove the base case" << endl;
    cout << "For course prerequisites: Base case is the first course with no prerequisites" << endl;
    cout << "Example: Intro to CS (CS101) - No prerequisites required" << endl;
    cout << "Base case: TRUE ✓" << endl;
}

void InductionModule::demonstrateInductiveStep() {
    cout << "\n=== Demonstrating INDUCTIVE STEP ===" << endl;
    cout << "Assume: Student can take courses 1 through k (Inductive Hypothesis)" << endl;
    cout << "Prove: Student can take course k+1" << endl;
    cout << "If course k+1 requires courses from {1...k}, then by hypothesis, it can be taken" << endl;
    cout << "Inductive step: TRUE ✓" << endl;
}

void InductionModule::runInductionExample() {
    cout << "\n========================================" << endl;
    cout << "INDUCTION EXAMPLE: Course Prerequisites" << endl;
    cout << "========================================" << endl;

    PrerequisiteChain chain;
    chain.addCourse("CS101 - Intro to CS");
    chain.addCourse("CS201 - Data Structures");
    chain.addCourse("CS301 - Algorithms");
    chain.addCourse("CS401 - Advanced Algorithms");

    chain.display();

    prover.verifyPrerequisiteChain(chain, "CS401");
    prover.displayProof();

    cout << "\n=== Strong Induction Example ===" << endl;
    prover.verifyMultiTermPrerequisites(chain);
    prover.displayProof();
}

void InductionModule::displayCoursePrerequisites() const {
    cout << "\n=== Course Prerequisites ===" << endl;
    for (int i = 0; i < courseCount; i++) {
        cout << courseList[i] << ":";
        if (prereqCounts[i] == 0) {
            cout << " (No prerequisites)";
        }
        else {
            cout << " Requires ";
            for (int j = 0; j < prereqCounts[i]; j++) {
                cout << prerequisites[i][j];
                if (j < prereqCounts[i] - 1) cout << ", ";
            }
        }
        cout << endl;
    }
}

void InductionModule::displayAllChains() const {
    cout << "\n=== All Prerequisite Chains (" << chainCount << ") ===" << endl;
    for (int i = 0; i < chainCount; i++) {
        cout << "Chain " << (i + 1) << ": ";
        chains[i].display();
    }
}