#ifndef PROOFS_H
#define PROOFS_H

#include <iostream>
#include <string>
using namespace std;

const int MAX_PROOF_LINES = 200;

class ProofGenerator {
private:
    string steps[MAX_PROOF_LINES];
    int stepCount;

public:
    ProofGenerator();

    void addStep(const string& step);
    void clear();

    void generateInductionProof(const string& statement, int base, int n);
    void generateLogicProof(const string& rule);
    void generatePrerequisiteProof(const string& course, const string prereqs[], int count);

    void displayProof() const;
    int getStepCount() const { return stepCount; }
};

class ProofModule {
private:
    ProofGenerator generator;

public:
    ProofModule();

    void runInductionDemo();
    void runLogicDemo();
    void runPrerequisiteDemo();

    void display() const;
};

#endif
