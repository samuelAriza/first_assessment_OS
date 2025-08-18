#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stddef.h> // size_t

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        const char *impl;          // "C" o "C++"
        const char *func;          // nombre de la función
        size_t n;                  // número de elementos
        double wall_ms;            // tiempo de pared en ms
        double cpu_ms;             // tiempo de CPU en ms
        size_t heap_kb_delta;      // delta de heap en KB (mallinfo2)
        size_t rss_kb_delta;       // delta de RSS en KB (VmRSS)
    } BenchmarkResult;

    // Tiempo
    double now_ms(void);           // CLOCK_MONOTONIC (pared)
    double cpu_now_ms(void);       // CLOCK_PROCESS_CPUTIME_ID (CPU proceso)

    // Memoria
    size_t memory_rss_kb(void);    // /proc/self/status VmRSS (memoria residente actual)
    size_t memory_heap_kb(void);   // mallinfo2().uordblks (bytes de heap en uso)
    void print_table(const BenchmarkResult *results, size_t count);
    void export_csv(const char *filename, const BenchmarkResult *results, size_t count);

#ifdef __cplusplus
}
#endif

#endif // BENCHMARK_H
