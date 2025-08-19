#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stddef.h> // size_t

#ifdef __cplusplus
extern "C"
{
#endif

    /// @struct BenchmarkResult
    /// @brief Holds the results of a single benchmark execution.
    typedef struct
    {
        const char *impl;          ///< Implementation type, e.g., "C" or "C++".
        const char *func;          ///< Function name being benchmarked.
        size_t n;                  ///< Number of elements processed.
        double wall_ms;            ///< Wall-clock time in milliseconds.
        double cpu_ms;             ///< CPU time in milliseconds.
        size_t heap_kb_delta;      ///< Change in heap usage in KB (mallinfo2).
        size_t rss_kb_delta;       ///< Change in resident set size (RSS) in KB.
    } BenchmarkResult;

    // --- Timing utilities ---

    /// @brief Returns the current wall-clock time in milliseconds.
    /// Uses CLOCK_MONOTONIC to avoid issues with system time changes.
    double now_ms(void);

    /// @brief Returns the current process CPU time in milliseconds.
    /// Uses CLOCK_PROCESS_CPUTIME_ID for high-resolution CPU usage measurement.
    double cpu_now_ms(void);

    // --- Memory usage utilities ---

    /// @brief Returns the current resident set size (RSS) in KB.
    /// Reads VmRSS from /proc/self/status.
    size_t memory_rss_kb(void);

    /// @brief Returns the current heap usage in KB.
    /// Uses mallinfo2().uordblks to calculate bytes currently allocated on the heap.
    size_t memory_heap_kb(void);

    /// @brief Prints benchmark results in a formatted table.
    /// @param results Pointer to an array of BenchmarkResult.
    /// @param count Number of results in the array.
    void print_table(const BenchmarkResult *results, size_t count);

    /// @brief Exports benchmark results to a CSV file.
    /// @param filename Output CSV file path.
    /// @param results Pointer to an array of BenchmarkResult.
    /// @param count Number of results in the array.
    void export_csv(const char *filename, const BenchmarkResult *results, size_t count);

#ifdef __cplusplus
}
#endif

#endif // BENCHMARK_H