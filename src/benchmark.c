#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "person.h"
#include <stddef.h>

// Mide tiempo de ejecución de una función que procesa persons
double benchmark_time(const char *label,
                      void (*func)(const Person *, size_t),
                      const Person *persons,
                      size_t n);

// Mide tiempo de ejecución de una función que retorna algo dinámico
// y libera el resultado con freeFunc
double benchmark_time_with_result(const char *label,
                                  void *(*func)(const Person *, size_t, void *),
                                  void (*freeFunc)(void *),
                                  const Person *persons,
                                  size_t n);

// Reporta uso de memoria (via /proc/self/statm o valgrind externo)
size_t benchmark_memory();

// Exporta resultados de benchmarks a CSV
void benchmark_export_csv(const char *filename,
                          const char *testName,
                          double timeSeconds,
                          size_t memoryBytes);

#endif
