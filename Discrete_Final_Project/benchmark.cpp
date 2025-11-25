#include "Benchmark.h"
#include "Sets.h"
#include "Course.h"
#include "Relations.h"
#include "Induction.h"
#include "LogicEngine.h"
#include <ctime>

Benchmark::Benchmark() {}

long long Benchmark::measure(void (*func)()) {
    clock_t start = clock();
    func();
    clock_t end = clock();
    // Convert clock ticks to microseconds (approximate)
    return (long long)((end - start) * 1000000.0 / CLOCKS_PER_SEC);
}

void Benchmark::benchmarkSets() {
    cout << "\nBenchmark: Set Operations\n";
    long long t = measure([]() {
        Set<string> A;
        for (int i = 0; i < 50; i++) A.add("Item" + to_string(i));
        Set<string> B = A;
        A.unionWith(B);
        A.intersectionWith(B);
        });
    cout << "Time: " << t << " microseconds\n";
}

void Benchmark::benchmarkScheduling() {
    cout << "\nBenchmark: Course Scheduling\n";
    long long t = measure([]() {
        CourseScheduler s;
        s.addCourse("A", "A", 3);
        s.addCourse("B", "B", 3);
        s.addCourse("C", "C", 3);
        s.addPrerequisite("C", "B");
        s.addPrerequisite("B", "A");
        s.displayTopologicalOrder();
        });
    cout << "Time: " << t << " microseconds\n";
}

void Benchmark::benchmarkRelations() {
    cout << "\nBenchmark: Relations\n";
    long long t = measure([]() {
        Relation<string, string> rel;
        rel.addPair("A", "B");
        rel.addPair("B", "C");
        rel.addPair("A", "C");
        rel.isTransitive();
        });
    cout << "Time: " << t << " microseconds\n";
}

void Benchmark::benchmarkLogic() {
    cout << "\nBenchmark: Logic Engine\n";
    long long t = measure([]() {
        InferenceEngine eng;
        eng.addRule("A", "B", "Rule1");
        eng.addFact("A");
        eng.forwardChaining();
        });
    cout << "Time: " << t << " microseconds\n";
}

void Benchmark::benchmarkInduction() {
    cout << "\nBenchmark: Induction Module\n";
    long long t = measure([]() {
        InductionProver p;
        PrerequisiteChain c;
        c.addCourse("CS101");
        c.addCourse("CS201");
        p.verifyPrerequisiteChain(c, "CS201");
        });
    cout << "Time: " << t << " microseconds\n";
}
