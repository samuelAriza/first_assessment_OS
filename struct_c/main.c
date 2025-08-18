#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./include/benchmark.h"
#include "./include/generator.h"
#include "./include/queries.h"

// Función auxiliar para obtener timestamp
void get_timestamp(char *buffer, size_t size)
{
    time_t now = time(0);
    struct tm *tm_info = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Función auxiliar para imprimir información de persona usando punteros
void log_person_info(FILE *file, const char *label, const Person *person)
{
    if (person && person->age != -1)
    {
        fprintf(file, "%s:\n", label);
        fprintf(file, "  [%s] Name: %s %s %s\n", person->id, person->firstName, person->firstLastName, person->secondLastName);
        fprintf(file, "     - Age: %d\n", person->age);
        fprintf(file, "     - City: %s\n", person->residence);
        fprintf(file, "     - Heritage: $%.2f\n", person->heritage);
        fprintf(file, "     - Debts: $%.2f\n", person->debts);
        fprintf(file, "     - Tax group: %c\n", person->taxGroup);
    }
    else
    {
        fprintf(file, "%s: No encontrado\n", label);
    }
}

// Función auxiliar para imprimir información de persona usando valores
void log_person_info_val(FILE *file, const char *label, Person person)
{
    if (person.age != -1)
    {
        fprintf(file, "%s:\n", label);
        fprintf(file, "  [%s] Name: %s %s %s\n", person.id, person.firstName, person.firstLastName, person.secondLastName);
        fprintf(file, "     - Age: %d\n", person.age);
        fprintf(file, "     - City: %s\n", person.residence);
        fprintf(file, "     - Heritage: $%.2f\n", person.heritage);
        fprintf(file, "     - Debts: $%.2f\n", person.debts);
        fprintf(file, "     - Tax group: %c\n", person.taxGroup);
    }
    else
    {
        fprintf(file, "%s: No encontrado\n", label);
    }
}

int main()
{
    size_t sizes[] = {10000}; // puedes añadir 10M si tu PC lo soporta
    size_t n_sizes = sizeof(sizes) / sizeof(sizes[0]);

    BenchmarkResult results[1000]; // espacio suficiente para todos los benchmarks
    size_t rcount = 0;

    // Crear archivos de log
    FILE *log_ptr = fopen("results_ptr.log", "w");
    FILE *log_val = fopen("results_val.log", "w");
    FILE *log_combined = fopen("results_combined.log", "w");

    if (!log_ptr || !log_val || !log_combined)
    {
        fprintf(stderr, "Error: No se pudieron crear los archivos de log\n");
        return 1;
    }

    char timestamp[64];
    get_timestamp(timestamp, sizeof(timestamp));

    // Headers de los archivos de log
    fprintf(log_ptr, "=== RESULTADOS DE FUNCIONES CON PUNTEROS ===\n");
    fprintf(log_ptr, "Fecha: %s\n\n", timestamp);

    fprintf(log_val, "=== RESULTADOS DE FUNCIONES CON VALORES ===\n");
    fprintf(log_val, "Fecha: %s\n\n", timestamp);

    fprintf(log_combined, "=== COMPARATIVA COMPLETA DE RESULTADOS ===\n");
    fprintf(log_combined, "Fecha: %s\n\n", timestamp);

    for (size_t i = 0; i < n_sizes; i++)
    {
        size_t n = sizes[i];
        Person *persons = generatePersons(n);
        if (!persons)
        {
            fprintf(stderr, "Error: generatePersons devolvió NULL para n=%zu\n", n);
            continue;
        }

        fprintf(log_ptr, "--- DATASET DE %zu PERSONAS ---\n\n", n);
        fprintf(log_val, "--- DATASET DE %zu PERSONAS ---\n\n", n);
        fprintf(log_combined, "--- DATASET DE %zu PERSONAS ---\n\n", n);

        // 1. findOldest - Encontrar persona más longeva del país
        size_t rss_before = memory_rss_kb();
        size_t heap_before = memory_heap_kb();
        double start = now_ms();
        double cpu_start = cpu_now_ms();
        const Person *oldestPtr = findOldest_ptr(persons, n);
        double end = now_ms();
        double cpu_end = cpu_now_ms();
        size_t rss_after = memory_rss_kb();
        size_t heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "findOldest_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Person oldestVal = findOldest_val(persons, n);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "findOldest_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log resultados findOldest
        log_person_info(log_ptr, "Persona más longeva (ptr)", oldestPtr);
        log_person_info_val(log_val, "Persona más longeva (val)", oldestVal);
        fprintf(log_combined, "PERSONA MÁS LONGEVA:\n");
        log_person_info(log_combined, "  PTR", oldestPtr);
        log_person_info_val(log_combined, "  VAL", oldestVal);

        // 2. findOldestByCity - Encontrar persona más longeva por ciudad
        size_t cityCount;
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Person **oldestByCityPtr = findOldestByCity_ptr(persons, n, &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "findOldestByCity_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Person *oldestByCityVal = findOldestByCity_val(persons, n, &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "findOldestByCity_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log basic (count to use variable)
        fprintf(log_ptr, "Número de ciudades con longevos (ptr): %zu\n", cityCount);
        fprintf(log_val, "Número de ciudades con longevos (val): %zu\n", cityCount);
        fprintf(log_combined, "\nNÚMERO DE CIUDADES CON LONGEVOS: PTR=%zu, VAL=%zu\n", cityCount, cityCount);

        // Free to avoid leak and use variable
        free((void *)oldestByCityPtr);
        free(oldestByCityVal);

        // 3. findRichest - Persona con mayor patrimonio en el país
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Person *richestPtr = findRichest_ptr(persons, n);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "findRichest_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Person richestVal = findRichest_val(persons, n);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "findRichest_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log to use variable
        log_person_info(log_ptr, "Persona más rica (ptr)", richestPtr);
        log_person_info_val(log_val, "Persona más rica (val)", richestVal);
        fprintf(log_combined, "\nPERSONA MÁS RICA:\n");
        log_person_info(log_combined, "  PTR", richestPtr);
        log_person_info_val(log_combined, "  VAL", richestVal);

        // 4. findRichestByCity - Persona con mayor patrimonio por ciudad
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Person **richestByCityPtr = findRichestByCity_ptr(persons, n, &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "findRichestByCity_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Person *richestByCityVal = findRichestByCity_val(persons, n, &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "findRichestByCity_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log basic
        fprintf(log_ptr, "Número de ciudades con ricos (ptr): %zu\n", cityCount);
        fprintf(log_val, "Número de ciudades con ricos (val): %zu\n", cityCount);
        fprintf(log_combined, "\nNÚMERO DE CIUDADES CON RICOS: PTR=%zu, VAL=%zu\n", cityCount, cityCount);

        // Free
        free((void *)richestByCityPtr);
        free(richestByCityVal);

        // 5. findRichestByGroup - Persona con mayor patrimonio por grupo
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Person *richestByGroupPtr = findRichestByGroup_ptr(persons, n, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "findRichestByGroup_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Person richestByGroupVal = findRichestByGroup_val(persons, n, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "findRichestByGroup_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log to use variable
        log_person_info(log_ptr, "Persona más rica en grupo A (ptr)", richestByGroupPtr);
        log_person_info_val(log_val, "Persona más rica en grupo A (val)", richestByGroupVal);
        fprintf(log_combined, "\nPERSONA MÁS RICA EN GRUPO A:\n");
        log_person_info(log_combined, "  PTR", richestByGroupPtr);
        log_person_info_val(log_combined, "  VAL", richestByGroupVal);

        // 6. listByGroup - Lista de personas por grupo
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Person **listPtr = listByGroup_ptr(persons, n, 'A', &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "listByGroup_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Person *listVal = listByGroup_val(persons, n, 'A', &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "listByGroup_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log basic (count)
        fprintf(log_ptr, "Número de personas en grupo A (list ptr): %zu\n", cityCount);
        fprintf(log_val, "Número de personas en grupo A (list val): %zu\n", cityCount);
        fprintf(log_combined, "\nNÚMERO DE PERSONAS EN GRUPO A (LIST): PTR=%zu, VAL=%zu\n", cityCount, cityCount);

        // Free
        free((void *)listPtr);
        free(listVal);

        // 7. countByGroup - Conteo de personas por grupo
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        size_t countPtr = countByGroup_ptr(persons, n, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "countByGroup_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        size_t countVal = countByGroup_val(persons, n, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "countByGroup_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        fprintf(log_ptr, "\nCONTEO GRUPO A (ptr): %zu\n", countPtr);
        fprintf(log_val, "\nCONTEO GRUPO A (val): %zu\n", countVal);
        fprintf(log_combined, "\nCONTEO GRUPO A: PTR=%zu, VAL=%zu\n", countPtr, countVal);

        // 8. cityWithHighestAvgHeritage - Ciudad con mayor promedio de patrimonio
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const char *cityPtr = cityWithHighestAvgHeritage_ptr(persons, n);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "cityWithHighestAvgHeritage_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const char *cityVal = cityWithHighestAvgHeritage_val(persons, n);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "cityWithHighestAvgHeritage_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log resultados cityWithHighestAvgHeritage
        fprintf(log_ptr, "Ciudad con mayor promedio de patrimonio (ptr): %s\n",
                cityPtr ? cityPtr : "No encontrada");
        fprintf(log_val, "Ciudad con mayor promedio de patrimonio (val): %s\n",
                cityVal ? cityVal : "No encontrada");
        fprintf(log_combined, "\nCIUDAD CON MAYOR PROMEDIO DE PATRIMONIO:\n");
        fprintf(log_combined, "  PTR: %s\n  VAL: %s\n",
                cityPtr ? cityPtr : "No encontrada",
                cityVal ? cityVal : "No encontrada");

        free((void *)cityPtr);
        free((void *)cityVal);

        // 9. percentageOlderThanByGroup - Porcentaje de personas mayores que cierta edad por grupo
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double percentPtr = percentageOlderThanByGroup_ptr(persons, n, 65, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "percentageOlderThanByGroup_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double percentVal = percentageOlderThanByGroup_val(persons, n, 65, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "percentageOlderThanByGroup_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log resultados percentageOlderThanByGroup
        fprintf(log_ptr, "Porcentaje >=65 años en grupo A (ptr): %.2f%%\n", percentPtr);
        fprintf(log_val, "Porcentaje >=65 años en grupo A (val): %.2f%%\n", percentVal);
        fprintf(log_combined, "\nPORCENTAJE >=65 AÑOS EN GRUPO A:\n");
        fprintf(log_combined, "  PTR: %.2f%%\n  VAL: %.2f%%\n", percentPtr, percentVal);

        // 10. netWealthByCity - Patrimonio neto por ciudad
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double *netWealthPtr = netWealthByCity_ptr(persons, n, &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "netWealthByCity_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double *netWealthVal = netWealthByCity_val(persons, n, &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "netWealthByCity_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log resultados netWealthByCity (solo totales)
        double totalPtr = 0, totalVal = 0;
        if (netWealthPtr)
        {
            for (size_t j = 0; j < cityCount; j++)
                totalPtr += netWealthPtr[j];
        }
        if (netWealthVal)
        {
            for (size_t j = 0; j < cityCount; j++)
                totalVal += netWealthVal[j];
        }

        fprintf(log_ptr, "Patrimonio neto total por ciudades (ptr): %.2f\n", totalPtr);
        fprintf(log_val, "Patrimonio neto total por ciudades (val): %.2f\n", totalVal);
        fprintf(log_combined, "\nPATRIMONIO NETO TOTAL:\n");
        fprintf(log_combined, "  PTR: %.2f\n  VAL: %.2f\n", totalPtr, totalVal);

        free(netWealthPtr);
        free(netWealthVal);

        // 11. validateTaxGroup - Validar asignación de grupo fiscal
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        int validPtr = validateTaxGroup_ptr(&persons[0]);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (ptr)",
            .func = "validateTaxGroup_ptr",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        int validVal = validateTaxGroup_val(persons[0]);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = (BenchmarkResult){
            .impl = "C (val)",
            .func = "validateTaxGroup_val",
            .n = n,
            .wall_ms = end - start,
            .cpu_ms = cpu_end - cpu_start,
            .heap_kb_delta = (heap_after > heap_before) ? heap_after - heap_before : 0,
            .rss_kb_delta = (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        fprintf(log_ptr, "Validación de grupo fiscal (ptr): %d\n", validPtr);
        fprintf(log_val, "Validación de grupo fiscal (val): %d\n", validVal);
        fprintf(log_combined, "\nVALIDACIÓN DE GRUPO FISCAL:\n");
        fprintf(log_combined, "  PTR: %d\n  VAL: %d\n", validPtr, validVal);

        // Separador entre datasets
        fprintf(log_ptr, "\n");
        fprintf(log_val, "\n");
        fprintf(log_combined, "\n");

        free(persons);
    }

    // Cerrar archivos de log
    fclose(log_ptr);
    fclose(log_val);
    fclose(log_combined);

    printf("Total de benchmarks realizados: %zu\n", rcount);
    printf("Archivos de log generados:\n");
    printf("  - results_ptr.log (solo funciones con punteros)\n");
    printf("  - results_val.log (solo funciones con valores)\n");
    printf("  - results_combined.log (comparativa completa)\n");

    print_table(results, rcount);
    export_csv("results_c.csv", results, rcount); // Changed filename to match script expectation

    return 0;
}