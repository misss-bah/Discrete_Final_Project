#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <iostream>
#include <string>
using namespace std;

class Benchmark {
private:
    long long measure(void (*func)());

public:
    Benchmark();

    void benchmarkSets();
    void benchmarkScheduling();
    void benchmarkRelations();
    void benchmarkInduction();
    void benchmarkLogic();
};

#endif
