#ifndef EFFICIENCY_H
#define EFFICIENCY_H

#include <iostream>
#include <string>
#include <ctime>
#define MAX_ROOMS 50
#define MAX_CREDITS 21
#define MAX_COURSES 50
#define MAX_STUDENTS 200
#define MAX_FACULTY 50
#define MAX_PREREQS_PER_COURSE 10
#define MAX_ENROLLED_PER_STUDENT 10
#define MAX_ASSIGNED_PER_FACULTY 10
using namespace std;

const int MAX_CACHE_SIZE = 500;
const int MAX_BENCHMARKS = 100;
const int MAX_SEQUENCE_SIZE = 50;
const int MAX_POWERSET_SIZE = 20;

// Benchmark result structure
struct BenchmarkResult {
    string operationName;
    double executionTimeMs;
    int inputSize;
    int memoryUsed;
};

// Cache entry for memoization
template<typename K, typename V>
struct CacheEntry {
    K key;
    V value;
    bool isValid;
};

class AlgorithmicEfficiency {
private:
    // Fibonacci memoization cache
    CacheEntry<int, long long> fibCache[MAX_CACHE_SIZE];
    int fibCacheSize;

    // Path cache for prerequisite checking
    struct PathCacheEntry {
        int from;
        int to;
        bool hasPath;
        bool isValid;
    };
    PathCacheEntry pathCache[MAX_CACHE_SIZE];
    int pathCacheSize;

    // Benchmark results storage
    BenchmarkResult benchmarkResults[MAX_BENCHMARKS];
    int benchmarkCount;

    // Timing helper
    clock_t startTime;

    // Helper functions for caching
    bool findInFibCache(int n, long long& result);
    void addToFibCache(int n, long long value);
    bool findInPathCache(int from, int to, bool& result);
    void addToPathCache(int from, int to, bool hasPath);

    // Recursive implementations (for comparison)
    long long fibonacciRecursive(int n);

    // Optimized implementations
    long long fibonacciMemoized(int n);
    long long fibonacciIterative(int n);
    bool subsetSumDP(const int set[], int setSize, int target);

    // Bitwise operations helper
    void bitwiseSetOperations(bool set1[], bool set2[], int maxElement);

    // Timing helpers
    void startTimer();
    double stopTimer();

public:
    // Constructor & Destructor
    AlgorithmicEfficiency();
    ~AlgorithmicEfficiency();

    // Core optimization functions

    // 1. Fibonacci with memoization vs iteration
    long long computeFibonacci(int n, bool useMemoization = true);

    // 2. Subset sum with dynamic programming
    bool findSubsetSum(const int set[], int setSize, int target);

    // 3. Course prerequisite path checking with memoization
    bool hasPrerequisitePath(int courseFrom, int courseTo,
        const int adjacencyList[][MAX_COURSES],
        const int adjacencyCount[], int numCourses);

    // 4. Generate valid course sequences (optimized with backtracking)
    void generateValidSequences(const int courses[], int courseCount,
        const int prerequisites[][MAX_COURSES],
        const int prereqCounts[], int maxSequences,
        int result[][MAX_COURSES], int& resultCount);

    // 5. Student-course assignment optimization
    int optimizeAssignments(const int studentPreferences[][MAX_COURSES],
        int studentCount, const int courseLimits[],
        int courseCount);

    // 6. Efficient set operations using bit arrays
    void efficientSetOperations(const int set1[], int size1,
        const int set2[], int size2,
        int maxElement);

    // 7. Fast power set generation using bit manipulation
    void generatePowerSet(const int set[], int setSize,
        int result[][MAX_POWERSET_SIZE], int& resultCount);

    // 8. Optimized combination generation
    void generateCombinations(const int elements[], int n, int r,
        int result[][MAX_COURSES], int& resultCount);

    // Benchmarking functions

    // Add benchmark result
    void addBenchmark(const string& operationName, double timeMs,
        int inputSize, int memUsed);

    // Compare two implementations
    void compareImplementations(const string& operation1Name,
        const string& operation2Name,
        int inputSize);

    // Benchmark all operations
    void runAllBenchmarks();

    // Display benchmark results
    void displayBenchmarkResults() const;

    // Export benchmark results to file
    void exportBenchmarksToFile(const string& filename) const;

    // Cache management
    void clearAllCaches();
    int getTotalCacheSize() const;

    // Memory usage estimation
    int estimateMemoryUsage() const;

    // Performance metrics
    double getAverageExecutionTime(const string& operationName) const;
    void displayPerformanceMetrics() const;

    // Optimization recommendations
    void analyzeAndRecommend() const;

    // Stress testing
    void stressTestFibonacci(int maxN);
    void stressTestSubsetSum(int maxSetSize, int maxTarget);
    void stressTestCombinations(int maxN, int maxR);
};

#endif // ALGORITHMIC_EFFICIENCY_H