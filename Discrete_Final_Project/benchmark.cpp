#include "Benchmark.h"
#include "Sets.h"
#include "Courses.h"
#include "Relations.h"
#include "Induction.h"
#include "LogicEngine.h"
#include "Functions.h"
#include "Consistency.h"

Benchmark::Benchmark() {}

double Benchmark::measure(void (*func)()) {
    clock_t start = clock();
    func();
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC * 1000.0; // Returns milliseconds
}

// ========================================
// MODULE 12: PERFORMANCE BENCHMARKING
// ========================================

void Benchmark::benchmarkSets() {
    cout << "\n=== Benchmark: Set Operations ===\n";
    double t = measure([]() {
        Set<string> A;
        for (int i = 0; i < 50; i++) A.add("Item" + to_string(i));
        Set<string> B;
        for (int i = 25; i < 75; i++) B.add("Item" + to_string(i));
        A.unionWith(B);
        A.intersectionWith(B);
        A.differenceWith(B);
        });
    cout << "Time: " << t << " ms\n";
}

void Benchmark::benchmarkScheduling() {
    cout << "\n=== Benchmark: Course Scheduling ===\n";
    double t = measure([]() {
        CourseScheduler s;
        s.addCourse("CS101", "Intro", 3);
        s.addCourse("CS102", "Programming", 3);
        s.addCourse("CS201", "DS", 3);
        s.addCourse("CS202", "OOP", 3);
        s.addCourse("CS301", "Algorithms", 3);
        s.addPrerequisite("CS102", "CS101");
        s.addPrerequisite("CS201", "CS102");
        s.addPrerequisite("CS202", "CS102");
        s.addPrerequisite("CS301", "CS201");
        s.validatePrerequisites();
        s.displayTopologicalOrder();
        });
    cout << "Time: " << t << " ms\n";
}

void Benchmark::benchmarkRelations() {
    cout << "\n=== Benchmark: Relations ===\n";
    double t = measure([]() {
        Relation<string, string> rel;
        for (int i = 0; i < 20; i++) {
            rel.addPair("S" + to_string(i), "C" + to_string(i % 5));
        }
        string domain[5] = { "S0", "S1", "S2", "S3", "S4" };
        rel.isReflexive(domain, 5);
        rel.isSymmetric();
        rel.isTransitive();
        });
    cout << "Time: " << t << " ms\n";
}

void Benchmark::benchmarkLogic() {
    cout << "\n=== Benchmark: Logic Engine ===\n";
    double t = measure([]() {
        InferenceEngine eng;
        eng.addRule("A", "B", "Rule1");
        eng.addRule("B", "C", "Rule2");
        eng.addRule("C", "D", "Rule3");
        eng.addFact("A");
        for (int i = 0; i < 3; i++) {
            eng.forwardChaining();
        }
        });
    cout << "Time: " << t << " ms\n";
}

void Benchmark::benchmarkInduction() {
    cout << "\n=== Benchmark: Induction Module ===\n";
    double t = measure([]() {
        InductionProver p;
        PrerequisiteChain c;
        c.addCourse("CS101");
        c.addCourse("CS201");
        c.addCourse("CS301");
        c.addCourse("CS401");
        p.verifyPrerequisiteChain(c, "CS401");
        p.verifyMultiTermPrerequisites(c);
        });
    cout << "Time: " << t << " ms\n";
}

void Benchmark::benchmarkFunctions() {
    cout << "\n=== Benchmark: Functions Module ===\n";
    double t = measure([]() {
        Function<string, string> f;
        for (int i = 0; i < 30; i++) {
            f.addMapping("S" + to_string(i), "C" + to_string(i % 10));
        }
        f.isInjective();
        string codomain[10];
        for (int i = 0; i < 10; i++) {
            codomain[i] = "C" + to_string(i);
        }
        f.isSurjective(codomain, 10);
        });
    cout << "Time: " << t << " ms\n";
}

void Benchmark::benchmarkAll() {
    cout << "\n" << string(50, '=') << "\n";
    cout << "    RUNNING ALL PERFORMANCE BENCHMARKS\n";
    cout << string(50, '=') << "\n";

    benchmarkSets();
    benchmarkScheduling();
    benchmarkRelations();
    benchmarkInduction();
    benchmarkLogic();
    benchmarkFunctions();

    cout << "\n" << string(50, '=') << "\n";
    cout << "    BENCHMARKING COMPLETE\n";
    cout << string(50, '=') << "\n";
}

// ========================================
// MODULE 12: UNIT TESTING (CORRECTNESS)
// ========================================

bool Benchmark::testSetsCorrectness() {
    cout << "\n=== Testing Sets Correctness ===\n";
    bool allPassed = true;

    // Test 1: Union
    Set<string> A, B;
    A.add("CS101");
    A.add("CS201");
    B.add("CS201");
    B.add("CS301");
    Set<string> unionSet = A.unionWith(B);
    bool test1 = (unionSet.getSize() == 3);
    cout << "Test 1 (Union size = 3): " << (test1 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test1;

    // Test 2: Intersection
    Set<string> intersect = A.intersectionWith(B);
    bool test2 = (intersect.getSize() == 1);
    cout << "Test 2 (Intersection size = 1): " << (test2 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test2;

    // Test 3: Subset
    bool test3 = A.isSubsetOf(unionSet);
    cout << "Test 3 (A subset of Union): " << (test3 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test3;

    // Test 4: Difference
    Set<string> diff = A.differenceWith(B);
    bool test4 = (diff.getSize() == 1);
    cout << "Test 4 (Difference size = 1): " << (test4 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test4;

    // Test 5: Symmetric Difference
    Set<string> symDiff = A.symmetricDifference(B);
    bool test5 = (symDiff.getSize() == 2);
    cout << "Test 5 (Symmetric Diff size = 2): " << (test5 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test5;

    return allPassed;
}

bool Benchmark::testSchedulingCorrectness() {
    cout << "\n=== Testing Course Scheduling Correctness ===\n";
    bool allPassed = true;

    // Test 1: Valid prerequisite chain
    CourseScheduler s;
    s.addCourse("CS101", "Intro", 3);
    s.addCourse("CS201", "DS", 3);
    s.addPrerequisite("CS201", "CS101");
    bool test1 = s.validatePrerequisites();
    cout << "Test 1 (Valid prerequisites): " << (test1 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test1;

    // Test 2: Course count
    bool test2 = (s.getCourseCount() == 2);
    cout << "Test 2 (Course count = 2): " << (test2 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test2;

    // Test 3: Circular dependency detection
    CourseScheduler s2;
    s2.addCourse("A", "A", 3);
    s2.addCourse("B", "B", 3);
    s2.addCourse("C", "C", 3);
    s2.addPrerequisite("A", "B");
    s2.addPrerequisite("B", "C");
    s2.addPrerequisite("C", "A"); // Circular!
    bool test3 = !s2.validatePrerequisites(); // Should return false
    cout << "Test 3 (Circular detection): " << (test3 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test3;

    return allPassed;
}

bool Benchmark::testRelationsCorrectness() {
    cout << "\n=== Testing Relations Correctness ===\n";
    bool allPassed = true;

    // Test 1: Reflexive relation
    Relation<string, string> rel;
    rel.addPair("A", "A");
    rel.addPair("B", "B");
    string domain[] = { "A", "B" };
    bool test1 = rel.isReflexive(domain, 2);
    cout << "Test 1 (Reflexive): " << (test1 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test1;

    // Test 2: Symmetric relation
    Relation<string, string> rel2;
    rel2.addPair("A", "B");
    rel2.addPair("B", "A");
    bool test2 = rel2.isSymmetric();
    cout << "Test 2 (Symmetric): " << (test2 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test2;

    // Test 3: Transitive relation
    Relation<string, string> rel3;
    rel3.addPair("A", "B");
    rel3.addPair("B", "C");
    rel3.addPair("A", "C");
    bool test3 = rel3.isTransitive();
    cout << "Test 3 (Transitive): " << (test3 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test3;

    // Test 4: Non-transitive relation
    Relation<string, string> rel4;
    rel4.addPair("A", "B");
    rel4.addPair("B", "C");
    // Missing (A,C) - should be non-transitive
    bool test4 = !rel4.isTransitive();
    cout << "Test 4 (Non-transitive detection): " << (test4 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test4;

    return allPassed;
}

bool Benchmark::testInductionCorrectness() {
    cout << "\n=== Testing Induction Correctness ===\n";
    bool allPassed = true;

    // Test 1: Simple prerequisite verification
    InductionModule im;
    string prereqs1[] = { "CS101" };
    im.addCourseWithPrereqs("CS201", prereqs1, 1);
    string completed1[] = { "CS101" };
    bool test1 = im.verifyCanTakeCourse("CS201", completed1, 1);
    cout << "Test 1 (Prerequisites satisfied): " << (test1 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test1;

    // Test 2: Missing prerequisite
    string completed2[] = { "CS102" };
    bool test2 = !im.verifyCanTakeCourse("CS201", completed2, 1);
    cout << "Test 2 (Missing prerequisite detection): " << (test2 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test2;

    // Test 3: Chain verification
    InductionProver p;
    PrerequisiteChain c;
    c.addCourse("CS101");
    c.addCourse("CS201");
    c.addCourse("CS301");
    bool test3 = p.verifyPrerequisiteChain(c, "CS301");
    cout << "Test 3 (Chain verification): " << (test3 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test3;

    return allPassed;
}

bool Benchmark::testLogicCorrectness() {
    cout << "\n=== Testing Logic Engine Correctness ===\n";
    bool allPassed = true;

    // Test 1: Forward chaining
    InferenceEngine eng;
    eng.addRule("P", "Q", "Test Rule");
    eng.addFact("P");
    bool test1 = eng.forwardChaining();
    cout << "Test 1 (Forward chaining): " << (test1 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test1;

    // Test 2: Rule application
    InferenceEngine eng2;
    eng2.addRule("A", "B", "Rule1");
    eng2.addRule("B", "C", "Rule2");
    eng2.addFact("A");
    eng2.forwardChaining(); // A -> B
    bool test2 = eng2.forwardChaining(); // B -> C
    cout << "Test 2 (Multiple inferences): " << (test2 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test2;

    return allPassed;
}

bool Benchmark::testFunctionsCorrectness() {
    cout << "\n=== Testing Functions Correctness ===\n";
    bool allPassed = true;

    // Test 1: Injective function
    Function<string, string> f1;
    f1.addMapping("S1", "C1");
    f1.addMapping("S2", "C2");
    f1.addMapping("S3", "C3");
    bool test1 = f1.isInjective();
    cout << "Test 1 (Injective function): " << (test1 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test1;

    // Test 2: Non-injective function
    Function<string, string> f2;
    f2.addMapping("S1", "C1");
    f2.addMapping("S2", "C1"); // Same output
    bool test2 = !f2.isInjective();
    cout << "Test 2 (Non-injective detection): " << (test2 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test2;

    // Test 3: Correct mapping
    bool test3 = (f1.apply("S1") == "C1");
    cout << "Test 3 (Correct mapping): " << (test3 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test3;

    // Test 4: Surjective function
    Function<string, string> f3;
    f3.addMapping("S1", "C1");
    f3.addMapping("S2", "C2");
    string codomain[] = { "C1", "C2" };
    bool test4 = f3.isSurjective(codomain, 2);
    cout << "Test 4 (Surjective function): " << (test4 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test4;

    return allPassed;
}

bool Benchmark::testConsistencyCorrectness() {
    cout << "\n=== Testing Consistency Checker Correctness ===\n";
    bool allPassed = true;

    // Test 1: Room conflict detection
    ConsistencyChecker cc1;
    string courses1[] = { "CS101", "CS201" };
    string rooms1[] = { "R1", "R1" };
    bool test1 = !cc1.checkRoomConflict(courses1, rooms1, 2);
    cout << "Test 1 (Room conflict detection): " << (test1 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test1;

    // Test 2: No conflict
    ConsistencyChecker cc2;
    string courses2[] = { "CS101", "CS201" };
    string rooms2[] = { "R1", "R2" };
    bool test2 = cc2.checkRoomConflict(courses2, rooms2, 2);
    cout << "Test 2 (No room conflict): " << (test2 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test2;

    // Test 3: Overload detection
    ConsistencyChecker cc3;
    bool test3 = !cc3.checkOverload(24); // Over 21 credits
    cout << "Test 3 (Overload detection): " << (test3 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test3;

    // Test 4: No overload
    ConsistencyChecker cc4;
    bool test4 = cc4.checkOverload(18); // Under 21 credits
    cout << "Test 4 (No overload): " << (test4 ? "PASS" : "FAIL") << "\n";
    allPassed = allPassed && test4;

    return allPassed;
}

void Benchmark::runAllTests() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "       RUNNING COMPREHENSIVE UNIT TESTS\n";
    cout << string(60, '=') << "\n";

    int passed = 0, total = 7;

    if (testSetsCorrectness()) passed++;
    if (testSchedulingCorrectness()) passed++;
    if (testRelationsCorrectness()) passed++;
    if (testInductionCorrectness()) passed++;
    if (testLogicCorrectness()) passed++;
    if (testFunctionsCorrectness()) passed++;
    if (testConsistencyCorrectness()) passed++;

    cout << "\n" << string(60, '=') << "\n";
    cout << "UNIT TEST RESULTS: " << passed << "/" << total << " modules passed\n";
    if (passed == total) {
        cout << "? ALL TESTS PASSED - System is working correctly!\n";
    }
    else {
        cout << "? SOME TESTS FAILED - Review failed modules\n";
    }
    cout << string(60, '=') << "\n";
}

void Benchmark::generateTestReport() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "       COMPREHENSIVE TEST & BENCHMARK REPORT\n";
    cout << string(60, '=') << "\n";

    cout << "\n--- PHASE 1: UNIT TESTING (Correctness Validation) ---\n";
    runAllTests();

    cout << "\n--- PHASE 2: PERFORMANCE BENCHMARKING ---\n";
    benchmarkAll();

    cout << "\n" << string(60, '=') << "\n";
    cout << "       REPORT GENERATION COMPLETE\n";
    cout << string(60, '=') << "\n";
}

void Benchmark::stressTestLargeDataset() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "       STRESS TESTING WITH LARGE DATASETS\n";
    cout << string(60, '=') << "\n";

    // Test 1: Large Set Operations
    cout << "\nTest 1: Large Set Operations (1000 elements)\n";
    double t1 = measure([]() {
        Set<string> A;
        for (int i = 0; i < 1000; i++) {
            A.add("Student" + to_string(i));
        }
        Set<string> B;
        for (int i = 500; i < 1500; i++) {
            B.add("Student" + to_string(i));
        }
        A.unionWith(B);
        A.intersectionWith(B);
        });
    cout << "Time: " << t1 << " ms\n";

    // Test 2: Large Relation Operations
    cout << "\nTest 2: Large Relations (500 pairs)\n";
    double t2 = measure([]() {
        Relation<string, string> rel;
        for (int i = 0; i < 500; i++) {
            rel.addPair("S" + to_string(i), "C" + to_string(i % 50));
        }
        rel.isSymmetric();
        rel.isTransitive();
        });
    cout << "Time: " << t2 << " ms\n";

    // Test 3: Large Function Mappings
    cout << "\nTest 3: Large Function Mappings (200 mappings)\n";
    double t3 = measure([]() {
        Function<string, string> f;
        for (int i = 0; i < 200; i++) {
            f.addMapping("S" + to_string(i), "C" + to_string(i % 20));
        }
        f.isInjective();
        });
    cout << "Time: " << t3 << " ms\n";

    cout << "\n" << string(60, '=') << "\n";
    cout << "       STRESS TESTING COMPLETE\n";
    cout << string(60, '=') << "\n";
}