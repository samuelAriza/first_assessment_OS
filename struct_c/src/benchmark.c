#define _POSIX_C_SOURCE 199309L
#include "../include/benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Para memoria (solo Linux con /proc)
#include <unistd.h>
#include <sys/resource.h>
#include <malloc.h>

double now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

double cpu_now_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

size_t memory_rss_kb(void)
{
    FILE *file = fopen("/proc/self/status", "r");
    if (!file)
        return 0;

    char line[256];
    size_t mem = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "VmRSS:", 6) == 0)
        {
            sscanf(line + 6, "%zu", &mem);
            break;
        }
    }
    fclose(file);
    return mem; // en KB
}

size_t memory_heap_kb(void)
{
    struct mallinfo2 mi = mallinfo2();
    return (size_t)(mi.uordblks / 1024); // bytes en uso -> KB
}

void print_table(const BenchmarkResult *results, size_t count)
{
    printf("\n%-10s | %-28s | %-10s | %-12s | %-12s | %-12s | %-12s\n",
           "Impl", "Función", "N", "Wall(ms)", "CPU(ms)", "HeapΔ(KB)", "RSSΔ(KB)");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    for (size_t i = 0; i < count; i++)
    {
        printf("%-10s | %-28s | %-10zu | %-12.3f | %-12.3f | %-12zu | %-12zu\n",
               results[i].impl, results[i].func, results[i].n,
               results[i].wall_ms, results[i].cpu_ms,
               results[i].heap_kb_delta, results[i].rss_kb_delta);
    }
}

void export_csv(const char *filename, const BenchmarkResult *results, size_t count)
{
    FILE *f = fopen(filename, "w");
    if (!f)
    {
        perror("fopen");
        return;
    }

    fprintf(f, "Implementation,Function,N,Wall_ms,CPU_ms,HeapKB_Delta,RSSKB_Delta\n");
    for (size_t i = 0; i < count; i++)
    {
        fprintf(f, "%s,%s,%zu,%.3f,%.3f,%zu,%zu\n",
                results[i].impl, results[i].func, results[i].n,
                results[i].wall_ms, results[i].cpu_ms,
                results[i].heap_kb_delta, results[i].rss_kb_delta);
    }

    fclose(f);
}