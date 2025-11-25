#include "Proofs.h"

ProofGenerator::ProofGenerator() : stepCount(0) {}

void ProofGenerator::addStep(const string& step) {
    if (stepCount < MAX_PROOF_LINES) {
        steps[stepCount++] = step;
    }
}

void ProofGenerator::clear() {
    stepCount = 0;
}

void ProofGenerator::generateInductionProof(const string& statement, int base, int n) {
    clear();
    addStep("Proof by Mathematical Induction on: " + statement);

    addStep("Step 1 (Base Case):");
    addStep("Verify statement holds for n = " + to_string(base));

    addStep("Step 2 (Inductive Hypothesis):");
    addStep("Assume statement holds for n = k");

    addStep("Step 3 (Inductive Step):");
    addStep("Show that if it holds for k, then it holds for k+1");

    addStep("Step 4 (Conclusion):");
    addStep("By induction, the statement holds for all n <= " + to_string(n));
}

void ProofGenerator::generateLogicProof(const string& rule) {
    clear();
    addStep("Logical Proof Demonstration");
    addStep("Applying Modus Ponens to: " + rule);
    addStep("If P -> Q and P is true, then Q must be true.");
    addStep("Inference completed.");
}

void ProofGenerator::generatePrerequisiteProof(const string& course, const string prereqs[], int count) {
    clear();
    addStep("Formal Verification of Prerequisites for " + course);
    for (int i = 0; i < count; i++) {
        addStep("Step " + to_string(i + 1) + ": " + prereqs[i] + " must be completed.");
    }
    addStep("Prerequisite verification completed successfully.");
}

void ProofGenerator::displayProof() const {
    cout << "\n=== PROOF STEPS ===\n";
    for (int i = 0; i < stepCount; i++) {
        cout << steps[i] << endl;
    }
    cout << "=====================\n";
}

ProofModule::ProofModule() {}

void ProofModule::runInductionDemo() {
    generator.generateInductionProof("Sum of first n natural numbers = n(n+1)/2", 1, 10);
    generator.displayProof();
}

void ProofModule::runLogicDemo() {
    generator.generateLogicProof("If Student takes CS101, then Lab A is assigned");
    generator.displayProof();
}

void ProofModule::runPrerequisiteDemo() {
    string prereqs[3] = { "CS101", "CS102", "CS201" };
    generator.generatePrerequisiteProof("CS301", prereqs, 3);
    generator.displayProof();
}

void ProofModule::display() const {
}
