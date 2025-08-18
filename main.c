#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "queries.h"

int main()
{
    size_t n = 100000; // cantidad de personas de prueba
    Person *persons = generatePersons(n);

    if (!persons)
    {
        fprintf(stderr, "Error: no se pudieron generar personas\n");
        return 1;
    }

    printf("\n=== Prueba de findOldest_ptr ===\n");
    const Person *oldest_ptr = findOldest_ptr(persons, n);
    if (oldest_ptr)
        show(oldest_ptr);

    printf("\n=== Prueba de findOldest_val ===\n");
    Person oldest_val = findOldest_val(persons, n);
    if (oldest_val.age != -1)
        show(&oldest_val);

    printf("\n==== Personas más longevas por ciudad (punteros) ====\n");
    size_t cityCountPtrOldest = 0; // nombre único
    const Person **oldestPtr = findOldestByCity_ptr(persons, n, &cityCountPtrOldest);
    if (oldestPtr)
    {
        for (size_t i = 0; i < cityCountPtrOldest; i++)
            show(oldestPtr[i]);
        free(oldestPtr);
    }

    printf("\n==== Personas más longevas por ciudad (valores) ====\n");
    size_t cityCountValOldest = 0; //  nombre único
    Person *oldestVal = findOldestByCity_val(persons, n, &cityCountValOldest);
    if (oldestVal)
    {
        for (size_t i = 0; i < cityCountValOldest; i++)
            show(&oldestVal[i]);
        free(oldestVal);
    }

    printf("\n==== Persona más rica en el país (puntero) ====\n");
    const Person *richestPtr = findRichest_ptr(persons, n);
    if (richestPtr)
        show(richestPtr);

    printf("\n==== Persona más rica en el país (valor) ====\n");
    Person richestVal = findRichest_val(persons, n);
    if (richestVal.age != -1)
        show(&richestVal);

    printf("\n==== Personas más ricas por ciudad (punteros) ====\n");
    size_t cityCountPtrRich = 0; // nombre único
    const Person **richestByCityPtr = findRichestByCity_ptr(persons, n, &cityCountPtrRich);
    if (richestByCityPtr)
    {
        for (size_t i = 0; i < cityCountPtrRich; i++)
            show(richestByCityPtr[i]);
        free(richestByCityPtr);
    }

    printf("\n==== Personas más ricas por ciudad (valores) ====\n");
    size_t cityCountValRich = 0; // nombre único
    Person *richestByCityVal = findRichestByCity_val(persons, n, &cityCountValRich);
    if (richestByCityVal)
    {
        for (size_t i = 0; i < cityCountValRich; i++)
            show(&richestByCityVal[i]);
        free(richestByCityVal);
    }

    printf("\n==== Persona más rica por grupo (puntero) ====\n");
    const Person *richestGroupPtr = findRichestByGroup_ptr(persons, n, 'A');
    if (richestGroupPtr)
        show(richestGroupPtr);

    printf("\n==== Persona más rica por grupo (valor) ====\n");
    Person richestGroupVal = findRichestByGroup_val(persons, n, 'A');
    if (richestGroupVal.age != -1)
        show(&richestGroupVal);

    printf("\n==== Personas del grupo A (punteros) ====\n");
    size_t countGroupPtr = 0;
    const Person **groupPtr = listByGroup_ptr(persons, n, 'A', &countGroupPtr);
    if (groupPtr)
    {
        for (size_t i = 0; i < countGroupPtr; i++)
            show(groupPtr[i]);
        free(groupPtr);
    }

    printf("\n==== Personas del grupo A (valores) ====\n");
    size_t countGroupVal = 0;
    Person *groupVal = listByGroup_val(persons, n, 'A', &countGroupVal);
    if (groupVal)
    {
        for (size_t i = 0; i < countGroupVal; i++)
            show(&groupVal[i]);
        free(groupVal);
    }

    printf("\n==== Conteo de personas por grupo (puntero) ====\n");
    printf("Grupo A: %zu\n", countByGroup_ptr(persons, n, 'A'));
    printf("Grupo B: %zu\n", countByGroup_ptr(persons, n, 'B'));
    printf("Grupo C: %zu\n", countByGroup_ptr(persons, n, 'C'));

    printf("\n==== Conteo de personas por grupo (valor) ====\n");
    printf("Grupo A: %zu\n", countByGroup_val(persons, n, 'A'));
    printf("Grupo B: %zu\n", countByGroup_val(persons, n, 'B'));
    printf("Grupo C: %zu\n", countByGroup_val(persons, n, 'C'));

    printf("\n==== Validación de grupo tributario (puntero y valor) ====\n");
    if (n > 0)
    {
        printf("Persona 0 (ptr): %s\n", validateTaxGroup_ptr(&persons[0]) ? "válido" : "inválido");
        printf("Persona 0 (val): %s\n", validateTaxGroup_val(persons[0]) ? "válido" : "inválido");
    }

    printf("\n==== Ciudad con mayor promedio de patrimonio (puntero) ====\n");
    char *cityPtr = (char *)cityWithHighestAvgHeritage_ptr(persons, n);
    if (cityPtr)
    {
        printf("Ciudad: %s\n", cityPtr);
        free(cityPtr);
    }

    printf("\n==== Ciudad con mayor promedio de patrimonio (valor) ====\n");
    char *cityVal = (char *)cityWithHighestAvgHeritage_val(persons, n);
    if (cityVal)
    {
        printf("Ciudad: %s\n", cityVal);
        free(cityVal);
    }

    printf("\n==== Porcentaje de personas mayores de 40 por grupo (puntero) ====\n");
    printf("Grupo A: %.2f%%\n", percentageOlderThanByGroup_ptr(persons, n, 40, 'A'));
    printf("Grupo B: %.2f%%\n", percentageOlderThanByGroup_ptr(persons, n, 40, 'B'));
    printf("Grupo C: %.2f%%\n", percentageOlderThanByGroup_ptr(persons, n, 40, 'C'));

    printf("\n==== Porcentaje de personas mayores de 40 por grupo (valor) ====\n");
    printf("Grupo A: %.2f%%\n", percentageOlderThanByGroup_val(persons, n, 40, 'A'));
    printf("Grupo B: %.2f%%\n", percentageOlderThanByGroup_val(persons, n, 40, 'B'));
    printf("Grupo C: %.2f%%\n", percentageOlderThanByGroup_val(persons, n, 40, 'C'));

    printf("\n==== Riqueza neta total por ciudad (puntero) ====\n");
    size_t cityCountPtrNW = 0;
    double *netWealthPtr = netWealthByCity_ptr(persons, n, &cityCountPtrNW);
    if (netWealthPtr)
    {
        for (size_t i = 0; i < cityCountPtrNW; i++)
            printf("Ciudad %zu: %.2f\n", i + 1, netWealthPtr[i]);
        free(netWealthPtr);
    }

    printf("\n==== Riqueza neta total por ciudad (valor) ====\n");
    size_t cityCountValNW = 0;
    double *netWealthVal = netWealthByCity_val(persons, n, &cityCountValNW);
    if (netWealthVal)
    {
        for (size_t i = 0; i < cityCountValNW; i++)
            printf("Ciudad %zu: %.2f\n", i + 1, netWealthVal[i]);
        free(netWealthVal);
    }

    free(persons);
    return 0;
}
