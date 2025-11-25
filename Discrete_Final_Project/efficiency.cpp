#include "Efficiency.h"
#include <fstream>

// Constructor
AlgorithmicEfficiency::AlgorithmicEfficiency() {
    fibCacheSize = 0;
    pathCacheSize = 0;
    benchmarkCount = 0;

    // Initialize caches
    for (int i = 0; i < MAX_CACHE_SIZE; i++) {
        fibCache[i].isValid = false;
        pathCache[i].isValid = false;
    }

    cout << "=== Algorithmic Efficiency Module Initialized ===" << endl;
    cout << "Cache size limit: " << MAX_CACHE_SIZE << endl;
}

// Destructor
AlgorithmicEfficiency::~AlgorithmicEfficiency() {
    clearAllCaches();
}

// ========== TIMING HELPERS ==========

void AlgorithmicEfficiency::startTimer() {
    startTime = clock();
}

double AlgorithmicEfficiency::stopTimer() {
    clock_t endTime = clock();
    return ((double)(endTime - startTime) / CLOCKS_PER_SEC) * 1000.0; // Convert to milliseconds
}

// ========== CACHE HELPERS ==========

bool AlgorithmicEfficiency::findInFibCache(int n, long long& result) {
    for (int i = 0; i < fibCacheSize; i++) {
        if (fibCache[i].isValid && fibCache[i].key == n) {
            result = fibCache[i].value;
            return true;
        }
    }
    return false;
}

void AlgorithmicEfficiency::addToFibCache(int n, long long value) {
    if (fibCacheSize < MAX_CACHE_SIZE) {
        fibCache[fibCacheSize].key = n;
        fibCache[fibCacheSize].value = value;
        fibCache[fibCacheSize].isValid = true;
        fibCacheSize++;
    }
}

bool AlgorithmicEfficiency::findInPathCache(int from, int to, bool& result) {
    for (int i = 0; i < pathCacheSize; i++) {
        if (pathCache[i].isValid &&
            pathCache[i].from == from &&
            pathCache[i].to == to) {
            result = pathCache[i].hasPath;
            return true;
        }
    }
    return false;
}

void AlgorithmicEfficiency::addToPathCache(int from, int to, bool hasPath) {
    if (pathCacheSize < MAX_CACHE_SIZE) {
        pathCache[pathCacheSize].from = from;
        pathCache[pathCacheSize].to = to;
        pathCache[pathCacheSize].hasPath = hasPath;
        pathCache[pathCacheSize].isValid = true;
        pathCacheSize++;
    }
}

// ========== FIBONACCI IMPLEMENTATIONS ==========

// Recursive (inefficient - for comparison)
long long AlgorithmicEfficiency::fibonacciRecursive(int n) {
    if (n <= 1) return n;
    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

// Memoized (optimized with caching)
long long AlgorithmicEfficiency::fibonacciMemoized(int n) {
    if (n <= 1) return n;

    long long cached;
    if (findInFibCache(n, cached)) {
        return cached;
    }

    long long result = fibonacciMemoized(n - 1) + fibonacciMemoized(n - 2);
    addToFibCache(n, result);
    return result;
}

// Iterative (most optimized)
long long AlgorithmicEfficiency::fibonacciIterative(int n) {
    if (n <= 1) return n;

    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long long temp = curr;
        curr = prev + curr;
        prev = temp;
    }
    return curr;
}

// Public Fibonacci function
long long AlgorithmicEfficiency::computeFibonacci(int n, bool useMemoization) {
    if (useMemoization) {
        return fibonacciMemoized(n);
    }
    else {
        return fibonacciIterative(n);
    }
}

// ========== SUBSET SUM WITH DYNAMIC PROGRAMMING ==========

bool AlgorithmicEfficiency::subsetSumDP(const int set[], int setSize, int target) {
    // Create DP table: dp[i][j] = can we make sum j using first i elements
    bool dp[MAX_COURSES + 1][1001]; // Assuming max target is 1000

    // Initialize
    for (int i = 0; i <= setSize; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = false;
        }
    }

    // Base case: sum 0 is always possible
    for (int i = 0; i <= setSize; i++) {
        dp[i][0] = true;
    }

    // Fill DP table
    for (int i = 1; i <= setSize; i++) {
        for (int j = 1; j <= target; j++) {
            if (set[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - set[i - 1]];
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[setSize][target];
}

bool AlgorithmicEfficiency::findSubsetSum(const int set[], int setSize, int target) {
    return subsetSumDP(set, setSize, target);
}

// ========== PREREQUISITE PATH CHECKING ==========

bool AlgorithmicEfficiency::hasPrerequisitePath(int courseFrom, int courseTo,
    const int adjacencyList[][MAX_COURSES],
    const int adjacencyCount[],
    int numCourses) {
    // Check cache first
    bool cachedResult;
    if (findInPathCache(courseFrom, courseTo, cachedResult)) {
        return cachedResult;
    }

    if (courseFrom == courseTo) {
        addToPathCache(courseFrom, courseTo, true);
        return true;
    }

    // DFS using stack
    bool visited[MAX_COURSES] = { false };
    int stack[MAX_COURSES];
    int top = 0;

    stack[top++] = courseFrom;

    while (top > 0) {
        int current = stack[--top];

        if (current == courseTo) {
            addToPathCache(courseFrom, courseTo, true);
            return true;
        }

        if (!visited[current]) {
            visited[current] = true;

            // Add neighbors to stack
            for (int i = 0; i < adjacencyCount[current]; i++) {
                int neighbor = adjacencyList[current][i];
                if (!visited[neighbor]) {
                    stack[top++] = neighbor;
                }
            }
        }
    }

    addToPathCache(courseFrom, courseTo, false);
    return false;
}

// ========== GENERATE VALID COURSE SEQUENCES ==========

void AlgorithmicEfficiency::generateValidSequences(const int courses[], int courseCount,
    const int prerequisites[][MAX_COURSES],
    const int prereqCounts[], int maxSequences,
    int result[][MAX_COURSES], int& resultCount) {
    resultCount = 0;
    int currentSeq[MAX_COURSES];
    bool used[MAX_COURSES] = { false };

    // Helper lambda-like recursive function
    struct Helper {
        static void backtrack(int depth, int courseCount, const int courses[],
            const int prerequisites[][MAX_COURSES],
            const int prereqCounts[], int maxSequences,
            int currentSeq[], bool used[],
            int result[][MAX_COURSES], int& resultCount) {

            if (depth == courseCount) {
                if (resultCount < maxSequences) {
                    for (int i = 0; i < courseCount; i++) {
                        result[resultCount][i] = currentSeq[i];
                    }
                    resultCount++;
                }
                return;
            }

            for (int i = 0; i < courseCount; i++) {
                if (used[i]) continue;

                // Check if all prerequisites are satisfied
                bool canTake = true;
                for (int j = 0; j < prereqCounts[i]; j++) {
                    bool prereqSatisfied = false;
                    for (int k = 0; k < depth; k++) {
                        if (currentSeq[k] == prerequisites[i][j]) {
                            prereqSatisfied = true;
                            break;
                        }
                    }
                    if (!prereqSatisfied) {
                        canTake = false;
                        break;
                    }
                }

                if (canTake) {
                    used[i] = true;
                    currentSeq[depth] = courses[i];
                    backtrack(depth + 1, courseCount, courses, prerequisites,
                        prereqCounts, maxSequences, currentSeq, used, result, resultCount);
                    used[i] = false;
                }
            }
        }
    };

    Helper::backtrack(0, courseCount, courses, prerequisites, prereqCounts,
        maxSequences, currentSeq, used, result, resultCount);
}

// ========== ASSIGNMENT OPTIMIZATION ==========

int AlgorithmicEfficiency::optimizeAssignments(const int studentPreferences[][MAX_COURSES],
    int studentCount, const int courseLimits[],
    int courseCount) {
    int totalAssignments = 0;
    int currentEnrollment[MAX_COURSES] = { 0 };

    // Greedy approach: assign each student to their first available preference
    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < MAX_COURSES; j++) {
            int courseId = studentPreferences[i][j];
            if (courseId == -1) break; // No more preferences

            if (courseId < courseCount &&
                currentEnrollment[courseId] < courseLimits[courseId]) {
                currentEnrollment[courseId]++;
                totalAssignments++;
                break;
            }
        }
    }

    return totalAssignments;
}

// ========== EFFICIENT SET OPERATIONS ==========

void AlgorithmicEfficiency::efficientSetOperations(const int set1[], int size1,
    const int set2[], int size2,
    int maxElement) {
    if (maxElement <= 0 || maxElement > 1000) {
        cout << "Max element must be between 1 and 1000" << endl;
        return;
    }

    // Use bit arrays for efficient operations
    bool bits1[1001] = { false };
    bool bits2[1001] = { false };

    for (int i = 0; i < size1; i++) {
        if (set1[i] >= 0 && set1[i] <= maxElement) {
            bits1[set1[i]] = true;
        }
    }

    for (int i = 0; i < size2; i++) {
        if (set2[i] >= 0 && set2[i] <= maxElement) {
            bits2[set2[i]] = true;
        }
    }

    cout << "\n=== Efficient Set Operations Using Bit Arrays ===" << endl;

    // Union
    cout << "Union: { ";
    for (int i = 0; i <= maxElement; i++) {
        if (bits1[i] || bits2[i]) {
            cout << i << " ";
        }
    }
    cout << "}" << endl;

    // Intersection
    cout << "Intersection: { ";
    for (int i = 0; i <= maxElement; i++) {
        if (bits1[i] && bits2[i]) {
            cout << i << " ";
        }
    }
    cout << "}" << endl;

    // Difference (set1 - set2)
    cout << "Difference (Set1 - Set2): { ";
    for (int i = 0; i <= maxElement; i++) {
        if (bits1[i] && !bits2[i]) {
            cout << i << " ";
        }
    }
    cout << "}" << endl;

    // Symmetric Difference
    cout << "Symmetric Difference: { ";
    for (int i = 0; i <= maxElement; i++) {
        if ((bits1[i] && !bits2[i]) || (!bits1[i] && bits2[i])) {
            cout << i << " ";
        }
    }
    cout << "}" << endl;
}

// ========== POWER SET GENERATION ==========

void AlgorithmicEfficiency::generatePowerSet(const int set[], int setSize,
    int result[][MAX_POWERSET_SIZE], int& resultCount) {
    resultCount = 0;
    int powerSetSize = 1 << setSize; // 2^n

    for (int i = 0; i < powerSetSize && resultCount < MAX_BENCHMARKS; i++) {
        int subsetSize = 0;
        for (int j = 0; j < setSize; j++) {
            if (i & (1 << j)) {
                result[resultCount][subsetSize++] = set[j];
            }
        }
        // Mark end of subset with -1
        if (subsetSize < MAX_POWERSET_SIZE) {
            result[resultCount][subsetSize] = -1;
        }
        resultCount++;
    }
}

// ========== COMBINATION GENERATION ==========

void AlgorithmicEfficiency::generateCombinations(const int elements[], int n, int r,
    int result[][MAX_COURSES], int& resultCount) {
    resultCount = 0;
    int current[MAX_COURSES];

    struct Helper {
        static void backtrack(int start, int n, int r, int depth,
            const int elements[], int current[],
            int result[][MAX_COURSES], int& resultCount) {
            if (depth == r) {
                for (int i = 0; i < r; i++) {
                    result[resultCount][i] = current[i];
                }
                resultCount++;
                return;
            }

            for (int i = start; i < n; i++) {
                current[depth] = elements[i];
                backtrack(i + 1, n, r, depth + 1, elements, current, result, resultCount);
            }
        }
    };

    Helper::backtrack(0, n, r, 0, elements, current, result, resultCount);
}

// ========== BENCHMARKING ==========

void AlgorithmicEfficiency::addBenchmark(const string& operationName, double timeMs,
    int inputSize, int memUsed) {
    if (benchmarkCount < MAX_BENCHMARKS) {
        benchmarkResults[benchmarkCount].operationName = operationName;
        benchmarkResults[benchmarkCount].executionTimeMs = timeMs;
        benchmarkResults[benchmarkCount].inputSize = inputSize;
        benchmarkResults[benchmarkCount].memoryUsed = memUsed;
        benchmarkCount++;
    }
}

void AlgorithmicEfficiency::compareImplementations(const string& operation1Name,
    const string& operation2Name,
    int inputSize) {
    cout << "\n=== Comparing Implementations ===" << endl;
    cout << "Operation 1: " << operation1Name << endl;
    cout << "Operation 2: " << operation2Name << endl;
    cout << "Input Size: " << inputSize << endl;

    // Example: Compare recursive vs iterative Fibonacci
    if (inputSize <= 40) {
        startTimer();
        long long result1 = fibonacciRecursive(inputSize);
        double time1 = stopTimer();

        clearAllCaches();

        startTimer();
        long long result2 = fibonacciIterative(inputSize);
        double time2 = stopTimer();

        cout << "Result 1: " << result1 << " (Time: " << time1 << " ms)" << endl;
        cout << "Result 2: " << result2 << " (Time: " << time2 << " ms)" << endl;

        if (time1 > 0) {
            cout << "Speedup: " << (time1 / time2) << "x" << endl;
        }
    }
}

void AlgorithmicEfficiency::runAllBenchmarks() {
    cout << "\n========== Running All Benchmarks ==========" << endl;

    // Benchmark 1: Fibonacci
    cout << "\n1. Fibonacci Computation" << endl;
    int fibTests[] = { 10, 20, 30, 40 };
    for (int i = 0; i < 4; i++) {
        startTimer();
        computeFibonacci(fibTests[i], true);
        double time = stopTimer();
        addBenchmark("Fibonacci_" + to_string(fibTests[i]), time, fibTests[i],
            estimateMemoryUsage());
        cout << "  n=" << fibTests[i] << ": " << time << " ms" << endl;
    }

    // Benchmark 2: Subset Sum
    cout << "\n2. Subset Sum" << endl;
    int testSet[] = { 3, 34, 4, 12, 5, 2 };
    startTimer();
    findSubsetSum(testSet, 6, 9);
    double time2 = stopTimer();
    addBenchmark("SubsetSum", time2, 6, estimateMemoryUsage());
    cout << "  Set size=6: " << time2 << " ms" << endl;

    // Benchmark 3: Power Set Generation
    cout << "\n3. Power Set Generation" << endl;
    int sizes[] = { 5, 10, 15 };
    for (int i = 0; i < 3; i++) {
        int set[20];
        for (int j = 0; j < sizes[i]; j++) set[j] = j;

        int resultSet[MAX_BENCHMARKS][MAX_POWERSET_SIZE];
        int count;

        startTimer();
        generatePowerSet(set, sizes[i], resultSet, count);
        double time3 = stopTimer();

        addBenchmark("PowerSet_" + to_string(sizes[i]), time3, sizes[i],
            estimateMemoryUsage());
        cout << "  Set size=" << sizes[i] << ": " << time3 << " ms" << endl;
    }

    // Benchmark 4: Combinations
    cout << "\n4. Combination Generation" << endl;
    int elements[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int rValues[] = { 2, 3, 4 };

    for (int i = 0; i < 3; i++) {
        int resultCombs[MAX_BENCHMARKS][MAX_COURSES];
        int count;

        startTimer();
        generateCombinations(elements, 8, rValues[i], resultCombs, count);
        double time4 = stopTimer();

        addBenchmark("Combinations_C(8," + to_string(rValues[i]) + ")",
            time4, 8, estimateMemoryUsage());
        cout << "  C(8," << rValues[i] << "): " << time4 << " ms" << endl;
    }
}

void AlgorithmicEfficiency::displayBenchmarkResults() const {
    cout << "\n========== Benchmark Results ==========" << endl;
    cout << "Operation                      Input Size  Time (ms)   Memory (bytes)" << endl;
    cout << "----------------------------------------------------------------------" << endl;

    for (int i = 0; i < benchmarkCount; i++) {
        cout.width(30);
        cout << left << benchmarkResults[i].operationName;
        cout.width(12);
        cout << benchmarkResults[i].inputSize;
        cout.width(12);
        cout << benchmarkResults[i].executionTimeMs;
        cout << benchmarkResults[i].memoryUsed << endl;
    }
}

void AlgorithmicEfficiency::exportBenchmarksToFile(const string& filename) const {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    file << "Operation,InputSize,ExecutionTime(ms),Memory(bytes)\n";
    for (int i = 0; i < benchmarkCount; i++) {
        file << benchmarkResults[i].operationName << ","
            << benchmarkResults[i].inputSize << ","
            << benchmarkResults[i].executionTimeMs << ","
            << benchmarkResults[i].memoryUsed << "\n";
    }

    file.close();
    cout << "Benchmark results exported to " << filename << endl;
}

// ========== CACHE MANAGEMENT ==========

void AlgorithmicEfficiency::clearAllCaches() {
    for (int i = 0; i < MAX_CACHE_SIZE; i++) {
        fibCache[i].isValid = false;
        pathCache[i].isValid = false;
    }
    fibCacheSize = 0;
    pathCacheSize = 0;
}

int AlgorithmicEfficiency::getTotalCacheSize() const {
    return fibCacheSize + pathCacheSize;
}

int AlgorithmicEfficiency::estimateMemoryUsage() const {
    int total = 0;

    // Fibonacci cache
    total += fibCacheSize * (sizeof(int) + sizeof(long long) + sizeof(bool));

    // Path cache
    total += pathCacheSize * (sizeof(int) * 2 + sizeof(bool) * 2);

    // Benchmark results
    total += benchmarkCount * sizeof(BenchmarkResult);

    return total;
}

// ========== PERFORMANCE METRICS ==========

double AlgorithmicEfficiency::getAverageExecutionTime(const string& operationName) const {
    double total = 0;
    int count = 0;

    for (int i = 0; i < benchmarkCount; i++) {
        // Simple string containment check
        if (benchmarkResults[i].operationName.find(operationName) != string::npos) {
            total += benchmarkResults[i].executionTimeMs;
            count++;
        }
    }

    return count > 0 ? total / count : 0.0;
}

void AlgorithmicEfficiency::displayPerformanceMetrics() const {
    cout << "\n========== Performance Metrics ==========" << endl;
    cout << "Total Benchmarks Run: " << benchmarkCount << endl;
    cout << "Cache Entries: " << getTotalCacheSize() << endl;
    cout << "Estimated Memory Usage: " << estimateMemoryUsage() << " bytes" << endl;

    if (benchmarkCount > 0) {
        double minTime = benchmarkResults[0].executionTimeMs;
        double maxTime = benchmarkResults[0].executionTimeMs;
        double totalTime = 0;

        for (int i = 0; i < benchmarkCount; i++) {
            if (benchmarkResults[i].executionTimeMs < minTime) {
                minTime = benchmarkResults[i].executionTimeMs;
            }
            if (benchmarkResults[i].executionTimeMs > maxTime) {
                maxTime = benchmarkResults[i].executionTimeMs;
            }
            totalTime += benchmarkResults[i].executionTimeMs;
        }

        cout << "Min Execution Time: " << minTime << " ms" << endl;
        cout << "Max Execution Time: " << maxTime << " ms" << endl;
        cout << "Avg Execution Time: " << (totalTime / benchmarkCount) << " ms" << endl;
    }
}

void AlgorithmicEfficiency::analyzeAndRecommend() const {
    cout << "\n========== Optimization Analysis ==========" << endl;

    int cacheSize = getTotalCacheSize();
    int memUsage = estimateMemoryUsage();

    cout << "Current Performance Status:" << endl;

    if (cacheSize > 400) {
        cout << "  [WARNING] Large cache size detected (" << cacheSize << " entries)" << endl;
        cout << "  Recommendation: Consider implementing cache eviction policy" << endl;
    }
    else {
        cout << "  [OK] Cache size is optimal (" << cacheSize << " entries)" << endl;
    }

    if (memUsage > 100000) {
        cout << "  [WARNING] High memory usage (" << memUsage << " bytes)" << endl;
        cout << "  Recommendation: Clear caches periodically" << endl;
    }
    else {
        cout << "  [OK] Memory usage is acceptable (" << memUsage << " bytes)" << endl;
    }

    cout << "\nOptimization Techniques Currently Applied:" << endl;
    cout << "  - Memoization for recursive computations" << endl;
    cout << "  - Dynamic Programming for subset problems" << endl;
    cout << "  - Bit manipulation for power set generation" << endl;
    cout << "  - Iterative approaches where possible" << endl;
    cout << "  - Efficient data structures (arrays, caches)" << endl;
}

// ========== STRESS TESTING ==========

void AlgorithmicEfficiency::stressTestFibonacci(int maxN) {
    cout << "\n=== Stress Testing Fibonacci ===" << endl;
    cout << "Testing up to n=" << maxN << endl;

    startTimer();
    for (int i = 1; i <= maxN; i++) {
        computeFibonacci(i, true);
    }
    double totalTime = stopTimer();

    cout << "Total time for " << maxN << " computations: " << totalTime << " ms" << endl;
    cout << "Average time per computation: " << (totalTime / maxN) << " ms" << endl;
    cout << "Cache size after test: " << fibCacheSize << " entries" << endl;
}

void AlgorithmicEfficiency::stressTestSubsetSum(int maxSetSize, int maxTarget) {
    cout << "\n=== Stress Testing Subset Sum ===" << endl;
    cout << "Testing set size: " << maxSetSize << ", target: " << maxTarget << endl;

    int testSet[MAX_COURSES];
    for (int i = 0; i < maxSetSize; i++) {
        testSet[i] = i + 1;
    }

    startTimer();
    bool result = findSubsetSum(testSet, maxSetSize, maxTarget);
    double time = stopTimer();

    cout << "Result: " << (result ? "True" : "False") << endl;
    cout << "Execution time: " << time << " ms" << endl;
}

void AlgorithmicEfficiency::stressTestCombinations(int maxN, int maxR) {
    cout << "\n=== Stress Testing Combinations ===" << endl;
    cout << "Testing C(" << maxN << "," << maxR << ")" << endl;

    int elements[MAX_COURSES];
    for (int i = 0; i < maxN; i++) {
        elements[i] = i + 1;
    }

    int result[MAX_BENCHMARKS][MAX_COURSES];
    int count;

    startTimer();
    generateCombinations(elements, maxN, maxR, result, count);
    double time = stopTimer();

    cout << "Generated " << count << " combinations" << endl;
    cout << "Execution time: " << time << " ms" << endl;
}