#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream> // Para verificar archivo CSV
#include "./include/persona.h"
#include "./include/generador.h"
#include "./include/benchmark.h"
#include "./include/queries_class.h"

int main()
{
    size_t sizes[] = {10000, 1000000, 5000000};
    size_t n_sizes = sizeof(sizes) / sizeof(sizes[0]);

    BenchmarkResult results[1000];
    size_t rcount = 0;

    // Verificar si podemos escribir el archivo CSV desde el inicio
    std::ofstream test_csv("results_cpp.csv", std::ios::app);
    if (!test_csv.is_open())
    {
        std::cerr << "Error: No se pudo abrir results_cpp.csv para escritura\n";
        return 1;
    }
    test_csv.close();

    for (size_t i = 0; i < n_sizes; i++)
    {
        size_t n = sizes[i];
        std::vector<Persona> persons = generarColeccion(n);
        if (persons.empty())
        {
            std::cerr << "Error: generarColeccion falló para n=" << n << "\n";
            continue;
        }

        std::cout << "--- DATASET DE " << n << " PERSONAS ---\n\n";

        // 1. findOldest
        size_t rss_before = memory_rss_kb();
        size_t heap_before = memory_heap_kb();
        double start = now_ms();
        double cpu_start = cpu_now_ms();
        const Persona *oldestPtr = findOldest_ptr(persons.data(), persons.size());
        double end = now_ms();
        double cpu_end = cpu_now_ms();
        size_t rss_after = memory_rss_kb();
        size_t heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findOldest_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Persona oldestVal = findOldest_val(persons.data(), persons.size());
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findOldest_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        std::cout << "Persona más longeva (ptr):\n";
        if (oldestPtr)
        {
            oldestPtr->mostrar();
        }
        else
        {
            std::cout << "No encontrada\n";
        }
        std::cout << "Persona más longeva (val):\n";
        oldestVal.mostrar();

        // 2. findOldestByCity
        size_t cityCount = 0;
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Persona **oldestByCityPtr = findOldestByCity_ptr(persons.data(), persons.size(), &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findOldestByCity_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Persona *oldestByCityVal = findOldestByCity_val(persons.data(), persons.size(), &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findOldestByCity_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log count
        std::cout << "Número de ciudades con longevos (ptr/val): " << cityCount << "\n";

        // Free
        if (oldestByCityPtr)
            delete[] oldestByCityPtr;
        if (oldestByCityVal)
            delete[] oldestByCityVal;

        // 3. findRichest
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Persona *richestPtr = findRichest_ptr(persons.data(), persons.size());
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findRichest_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Persona richestVal = findRichest_val(persons.data(), persons.size());
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findRichest_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        std::cout << "Persona más rica (ptr):\n";
        if (richestPtr)
        {
            richestPtr->mostrar();
        }
        else
        {
            std::cout << "No encontrada\n";
        }
        std::cout << "Persona más rica (val):\n";
        richestVal.mostrar();

        // 4. findRichestByCity
        cityCount = 0;
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Persona **richestByCityPtr = findRichestByCity_ptr(persons.data(), persons.size(), &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findRichestByCity_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Persona *richestByCityVal = findRichestByCity_val(persons.data(), persons.size(), &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findRichestByCity_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log count
        std::cout << "Número de ciudades con ricos (ptr/val): " << cityCount << "\n";

        // Free
        if (richestByCityPtr)
            delete[] richestByCityPtr;
        if (richestByCityVal)
            delete[] richestByCityVal;

        // 5. findRichestByGroup
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Persona *richestByGroupPtr = findRichestByGroup_ptr(persons.data(), persons.size(), 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findRichestByGroup_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Persona richestByGroupVal = findRichestByGroup_val(persons.data(), persons.size(), 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "findRichestByGroup_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        std::cout << "Persona más rica en grupo A (ptr):\n";
        if (richestByGroupPtr)
        {
            richestByGroupPtr->mostrar();
        }
        else
        {
            std::cout << "No encontrada\n";
        }
        std::cout << "Persona más rica en grupo A (val):\n";
        richestByGroupVal.mostrar();

        // 6. listTaxGroup
        cityCount = 0;
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const Persona **listPtr = listTaxGroup_ptr(persons.data(), persons.size(), 'A', &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "listTaxGroup_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        Persona *listVal = listTaxGroup_val(persons.data(), persons.size(), 'A', &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "listTaxGroup_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log count
        std::cout << "Número de personas en grupo A (list ptr/val): " << cityCount << "\n";

        // Free
        if (listPtr)
            delete[] listPtr;
        if (listVal)
            delete[] listVal;

        // 7. countTaxGroup
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        size_t countPtr = countTaxGroup_ptr(persons.data(), persons.size(), 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "countTaxGroup_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        size_t countVal = countTaxGroup_val(persons.data(), persons.size(), 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "countTaxGroup_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        std::cout << "Conteo grupo A (ptr): " << countPtr << "\n";
        std::cout << "Conteo grupo A (val): " << countVal << "\n";

        // 8. cityWithHighestAvgHeritage
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const char *cityPtr = cityWithHighestAvgHeritage_ptr(persons.data(), persons.size());
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "cityWithHighestAvgHeritage_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        const char *cityVal = cityWithHighestAvgHeritage_val(persons.data(), persons.size());
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "cityWithHighestAvgHeritage_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        std::cout << "Ciudad con mayor promedio de patrimonio (ptr): " << (cityPtr ? cityPtr : "No encontrada") << "\n";
        std::cout << "Ciudad con mayor promedio de patrimonio (val): " << (cityVal ? cityVal : "No encontrada") << "\n";

        // Free
        if (cityPtr)
            delete[] cityPtr;
        if (cityVal)
            delete[] cityVal;

        // 9. percentageOlderThanByGroup
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double percentPtr = percentageOlderThanByGroup_ptr(persons.data(), persons.size(), 65, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "percentageOlderThanByGroup_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double percentVal = percentageOlderThanByGroup_val(persons.data(), persons.size(), 65, 'A');
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "percentageOlderThanByGroup_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        std::cout << "Porcentaje >=65 años en grupo A (ptr): " << std::fixed << std::setprecision(2) << percentPtr << "%\n";
        std::cout << "Porcentaje >=65 años en grupo A (val): " << std::fixed << std::setprecision(2) << percentVal << "%\n";

        // 10. netWealthByCity
        cityCount = 0;
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double *netWealthPtr = netWealthByCity_ptr(persons.data(), persons.size(), &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "netWealthByCity_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        double *netWealthVal = netWealthByCity_val(persons.data(), persons.size(), &cityCount);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "netWealthByCity_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log total
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
        std::cout << "Patrimonio neto total por ciudades (ptr): " << std::fixed << std::setprecision(2) << totalPtr << "\n";
        std::cout << "Patrimonio neto total por ciudades (val): " << std::fixed << std::setprecision(2) << totalVal << "\n";

        // Free
        if (netWealthPtr)
            delete[] netWealthPtr;
        if (netWealthVal)
            delete[] netWealthVal;

        // 11. validateTaxGroup
        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        int validPtr = persons.empty() ? 0 : validateTaxGroup_ptr(&persons[0]);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "validateTaxGroup_ptr",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        rss_before = memory_rss_kb();
        heap_before = memory_heap_kb();
        start = now_ms();
        cpu_start = cpu_now_ms();
        int validVal = persons.empty() ? 0 : validateTaxGroup_val(persons[0]);
        end = now_ms();
        cpu_end = cpu_now_ms();
        rss_after = memory_rss_kb();
        heap_after = memory_heap_kb();
        results[rcount++] = {
            "C++ (class)",
            "validateTaxGroup_val",
            n,
            end - start,
            cpu_end - cpu_start,
            (heap_after > heap_before) ? heap_after - heap_before : 0,
            (rss_after > rss_before) ? rss_after - rss_before : 0};

        // Log
        std::cout << "Validación de grupo fiscal (ptr): " << validPtr << "\n";
        std::cout << "Validación de grupo fiscal (val): " << validVal << "\n";

        std::cout << "\n";
    }

    // Confirmar número de benchmarks
    std::cout << "Total de benchmarks realizados (C++): " << rcount << "\n";

    // Export results
    print_table(results, rcount);
    export_csv("results_cpp.csv", results, rcount);

    return 0;
}