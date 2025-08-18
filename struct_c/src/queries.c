#include "../include/queries.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// En todo el país



// arr[index]

const Person *findOldest_ptr(const Person *persons, size_t n)
{
    if (!persons || n == 0)
        return NULL;
    const Person *oldest = persons;
    const Person *current = persons + 1;
    const Person *end = persons + n;
    for (; current < end; current++)
    {
        if (current->age > oldest->age)
            oldest = current;
    }
    return oldest;
}

Person findOldest_val(const Person persons[], size_t n)
{
    Person empty = {.age = -1}; // Indicador de error: edad negativa
    if (!persons || n == 0)
        return empty;
    Person oldest = persons[0]; // Copia inicial
    for (size_t i = 1; i < n; i++)
    {
        if (persons[i].age > oldest.age)
            oldest = persons[i]; // Copia de la estructura
    }
    return oldest;
}

// Por ciudad

// Devuelve un arreglo de punteros a las personas más longevas por ciudad y actualiza *cityCount.
// Libera memoria auxiliar internamente; el cliente debe liberar el arreglo devuelto.
const Person **findOldestByCity_ptr(const Person *persons, size_t n, size_t *cityCount)
{
    if (!persons || n == 0)
    {
        *cityCount = 0;
        return NULL;
    }

    char **seen = malloc(n * sizeof(char *)); // Máximo n ciudades
    const Person **results = malloc(n * sizeof(const Person *));
    size_t seenCount = 0;

    const Person *end = persons + n;
    for (const Person *current = persons; current < end; current++)
    {
        int found = -1;
        char **current_seen = seen;
        const Person **current_result = results;
        for (size_t j = 0; j < seenCount; j++, current_seen++, current_result++)
        {
            if (strcmp(current->residence, *current_seen) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(current->residence) + 1);
            strcpy(seen[seenCount], current->residence);
            results[seenCount] = current;
            seenCount++;
        }
        else
        {
            if (current->age > (*current_result)->age)
                *current_result = current;
        }
    }

    // Redimensionar results al tamaño real
    const Person **final_results = realloc(results, seenCount * sizeof(const Person *));
    if (!final_results)
        final_results = results; // Si realloc falla, usar results original

    // Liberar seen
    for (size_t i = 0; i < seenCount; i++)
        free(seen[i]);
    free(seen);

    *cityCount = seenCount;
    return final_results;
}

// Devuelve un arreglo de estructuras Person con las personas más longevas por ciudad y actualiza *cityCount.
// Libera memoria auxiliar internamente; el cliente debe liberar el arreglo devuelto.
Person *findOldestByCity_val(const Person persons[], size_t n, size_t *cityCount)
{
    if (!persons || n == 0)
    {
        *cityCount = 0;
        return NULL;
    }

    char **seen = malloc(n * sizeof(char *));
    Person *results = malloc(n * sizeof(Person));
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++)
    {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++)
        {
            if (strcmp(persons[i].residence, seen[j]) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(persons[i].residence) + 1);
            strcpy(seen[seenCount], persons[i].residence);
            results[seenCount] = persons[i]; // Copia
            seenCount++;
        }
        else
        {
            if (persons[i].age > results[found].age)
                results[found] = persons[i]; // Copia
        }
    }

    // Redimensionar results al tamaño real
    Person *final_results = realloc(results, seenCount * sizeof(Person));
    if (!final_results)
        final_results = results; // Si realloc falla, usar results original

    // Liberar seen
    for (size_t i = 0; i < seenCount; i++)
        free(seen[i]);
    free(seen);

    *cityCount = seenCount;
    return final_results;
}

// Devuelve un puntero a la persona con mayor patrimonio en el país, o NULL si el arreglo está vacío o es inválido.
const Person *findRichest_ptr(const Person *persons, size_t n)
{
    if (!persons || n == 0)
        return NULL;
    const Person *richest = persons;
    const Person *current = persons + 1;
    const Person *end = persons + n;
    for (; current < end; current++)
    {
        if (current->heritage > richest->heritage)
            richest = current;
    }
    return richest;
}

// Devuelve una copia de la persona con mayor patrimonio en el país, con age = -1 si el arreglo está vacío o es inválido.
Person findRichest_val(const Person persons[], size_t n)
{
    Person empty = {.age = -1}; // Indicador de error
    if (!persons || n == 0)
        return empty;
    Person richest = persons[0]; // Copia inicial
    for (size_t i = 1; i < n; i++)
    {
        if (persons[i].heritage > richest.heritage)
            richest = persons[i]; // Copia
    }
    return richest;
}

// Devuelve un arreglo de punteros a las personas con mayor patrimonio por ciudad y actualiza *cityCount.
// Libera memoria auxiliar; el cliente debe liberar el arreglo devuelto.
const Person **findRichestByCity_ptr(const Person *persons, size_t n, size_t *cityCount)
{
    if (!persons || n == 0)
    {
        *cityCount = 0;
        return NULL;
    }

    char **seen = malloc(n * sizeof(char *)); // Máximo n ciudades
    const Person **results = malloc(n * sizeof(const Person *));
    size_t seenCount = 0;

    const Person *end = persons + n;
    for (const Person *current = persons; current < end; current++)
    {
        int found = -1;
        char **current_seen = seen;
        const Person **current_result = results;
        for (size_t j = 0; j < seenCount; j++, current_seen++, current_result++)
        {
            if (strcmp(current->residence, *current_seen) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(current->residence) + 1);
            strcpy(seen[seenCount], current->residence);
            results[seenCount] = current;
            seenCount++;
        }
        else
        {
            if (current->heritage > (*current_result)->heritage)
                *current_result = current;
        }
    }

    // Redimensionar results
    const Person **final_results = realloc(results, seenCount * sizeof(const Person *));
    if (!final_results)
        final_results = results;

    // Liberar seen
    for (size_t i = 0; i < seenCount; i++)
        free(seen[i]);
    free(seen);

    *cityCount = seenCount;
    return final_results;
}

// Devuelve un arreglo de estructuras Person con las personas con mayor patrimonio por ciudad y actualiza *cityCount.
// Libera memoria auxiliar; el cliente debe liberar el arreglo devuelto.
Person *findRichestByCity_val(const Person persons[], size_t n, size_t *cityCount)
{
    if (!persons || n == 0)
    {
        *cityCount = 0;
        return NULL;
    }

    char **seen = malloc(n * sizeof(char *));
    Person *results = malloc(n * sizeof(Person));
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++)
    {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++)
        {
            if (strcmp(persons[i].residence, seen[j]) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(persons[i].residence) + 1);
            strcpy(seen[seenCount], persons[i].residence);
            results[seenCount] = persons[i]; // Copia
            seenCount++;
        }
        else
        {
            if (persons[i].heritage > results[found].heritage)
                results[found] = persons[i]; // Copia
        }
    }

    // Redimensionar results
    Person *final_results = realloc(results, seenCount * sizeof(Person));
    if (!final_results)
        final_results = results;

    // Liberar seen
    for (size_t i = 0; i < seenCount; i++)
        free(seen[i]);
    free(seen);

    *cityCount = seenCount;
    return final_results;
}

// Devuelve un puntero a la persona con mayor patrimonio en el grupo de declaración especificado, o NULL si no hay personas en el grupo o la entrada es inválida.
const Person *findRichestByGroup_ptr(const Person *persons, size_t n, char group)
{
    if (!persons || n == 0 || (group != 'A' && group != 'B' && group != 'C'))
        return NULL;

    const Person *richest = NULL;
    const Person *current = persons;
    const Person *end = persons + n;
    for (; current < end; current++)
    {
        if (current->taxGroup == group)
        {
            if (!richest || current->heritage > richest->heritage)
                richest = current;
        }
    }
    return richest;
}

// Devuelve una copia de la persona con mayor patrimonio en el grupo de declaración especificado, con age = -1 si no hay personas en el grupo o la entrada es inválida.
Person findRichestByGroup_val(const Person persons[], size_t n, char group)
{
    Person empty = {.age = -1}; // Indicador de error
    if (!persons || n == 0 || (group != 'A' && group != 'B' && group != 'C'))
        return empty;

    Person richest = empty;
    int found = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (persons[i].taxGroup == group)
        {
            if (!found || persons[i].heritage > richest.heritage)
            {
                richest = persons[i]; // Copia
                found = 1;
            }
        }
    }
    return richest;
}

// Devuelve un arreglo de punteros a las personas en el grupo de declaración especificado y actualiza *count.
// Libera memoria auxiliar; el cliente debe liberar el arreglo devuelto.
// Retorna NULL si la entrada es inválida o group no es 'A', 'B', o 'C'.
const Person **listByGroup_ptr(const Person *persons, size_t n, char group, size_t *count)
{
    if (!persons || n == 0 || (group != 'A' && group != 'B' && group != 'C'))
    {
        *count = 0;
        return NULL;
    }

    const Person **results = malloc(n * sizeof(const Person *));
    size_t c = 0;
    const Person *current = persons;
    const Person *end = persons + n;
    for (; current < end; current++)
    {
        if (current->taxGroup == group)
            results[c++] = current;
    }

    // Redimensionar results
    const Person **final_results = realloc(results, c * sizeof(const Person *));
    if (!final_results)
        final_results = results;

    *count = c;
    return final_results;
}

// Devuelve un arreglo de estructuras Person con las personas en el grupo de declaración especificado y actualiza *count.
// Libera memoria auxiliar; el cliente debe liberar el arreglo devuelto.
// Retorna NULL si la entrada es inválida o group no es 'A', 'B', o 'C'.
Person *listByGroup_val(const Person persons[], size_t n, char group, size_t *count)
{
    if (!persons || n == 0 || (group != 'A' && group != 'B' && group != 'C'))
    {
        *count = 0;
        return NULL;
    }

    Person *results = malloc(n * sizeof(Person));
    size_t c = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (persons[i].taxGroup == group)
            results[c++] = persons[i]; // Copia
    }

    // Redimensionar results
    Person *final_results = realloc(results, c * sizeof(Person));
    if (!final_results)
        final_results = results;

    *count = c;
    return final_results;
}

// Cuenta las personas en el grupo de declaración especificado.
// Retorna 0 si la entrada es inválida o group no es 'A', 'B', o 'C'.
size_t countByGroup_ptr(const Person *persons, size_t n, char group)
{
    if (!persons || n == 0 || (group != 'A' && group != 'B' && group != 'C'))
        return 0;

    size_t c = 0;
    const Person *current = persons;
    const Person *end = persons + n;
    for (; current < end; current++)
    {
        if (current->taxGroup == group)
            c++;
    }
    return c;
}

// Cuenta las personas en el grupo de declaración especificado.
// Retorna 0 si la entrada es inválida o group no es 'A', 'B', o 'C'.
size_t countByGroup_val(const Person persons[], size_t n, char group)
{
    if (!persons || n == 0 || (group != 'A' && group != 'B' && group != 'C'))
        return 0;

    size_t c = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (persons[i].taxGroup == group)
            c++;
    }
    return c;
}

int validateTaxGroup_ptr(const Person *p)
{
    return p && (p->taxGroup == 'A' || p->taxGroup == 'B' || p->taxGroup == 'C');
}

int validateTaxGroup_val(Person p)
{
    return (p.taxGroup == 'A' || p.taxGroup == 'B' || p.taxGroup == 'C');
}

// Aditional queries

// Devuelve una copia dinámica de la ciudad con el mayor promedio de patrimonio.
// El cliente debe liberar el resultado con free().
// Retorna NULL si la entrada es inválida o no hay ciudades.
const char *cityWithHighestAvgHeritage_ptr(const Person *persons, size_t n)
{
    if (!persons || n == 0)
        return NULL;

    char **seen = malloc(n * sizeof(char *));
    double *sum = calloc(n, sizeof(double));
    size_t *count = calloc(n, sizeof(size_t));
    size_t seenCount = 0;

    const Person *current = persons;
    const Person *end = persons + n;
    for (; current < end; current++)
    {
        int found = -1;
        char **current_seen = seen;
        for (size_t j = 0; j < seenCount; j++, current_seen++)
        {
            if (strcmp(current->residence, *current_seen) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(current->residence) + 1);
            strcpy(seen[seenCount], current->residence);
            sum[seenCount] = current->heritage;
            count[seenCount] = 1;
            seenCount++;
        }
        else
        {
            sum[found] += current->heritage;
            count[found]++;
        }
    }

    char *result = NULL;
    if (seenCount > 0)
    {
        size_t best = 0;
        double bestAvg = sum[0] / count[0];
        for (size_t j = 1; j < seenCount; j++)
        {
            double avg = sum[j] / count[j];
            if (avg > bestAvg)
            {
                bestAvg = avg;
                best = j;
            }
        }
        result = strdup(seen[best]);
    }

    for (size_t i = 0; i < seenCount; i++)
        free(seen[i]);
    free(seen);
    free(sum);
    free(count);

    return result;
}

// Devuelve una copia dinámica de la ciudad con el mayor promedio de patrimonio.
// El cliente debe liberar el resultado con free().
// Retorna NULL si la entrada es inválida o no hay ciudades.
const char *cityWithHighestAvgHeritage_val(const Person persons[], size_t n)
{
    if (!persons || n == 0)
        return NULL;

    char **seen = malloc(n * sizeof(char *));
    double *sum = calloc(n, sizeof(double));
    size_t *count = calloc(n, sizeof(size_t));
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++)
    {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++)
        {
            if (strcmp(persons[i].residence, seen[j]) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(persons[i].residence) + 1);
            strcpy(seen[seenCount], persons[i].residence);
            sum[seenCount] = persons[i].heritage;
            count[seenCount] = 1;
            seenCount++;
        }
        else
        {
            sum[found] += persons[i].heritage;
            count[found]++;
        }
    }

    char *result = NULL;
    if (seenCount > 0)
    {
        size_t best = 0;
        double bestAvg = sum[0] / count[0];
        for (size_t j = 1; j < seenCount; j++)
        {
            double avg = sum[j] / count[j];
            if (avg > bestAvg)
            {
                bestAvg = avg;
                best = j;
            }
        }
        result = strdup(seen[best]);
    }

    for (size_t i = 0; i < seenCount; i++)
        free(seen[i]);
    free(seen);
    free(sum);
    free(count);

    return result;
}

double percentageOlderThanByGroup_ptr(const Person *persons, size_t n, int age, char group)
{
    size_t total = 0, older = 0;
    const Person *end = persons + n; // Puntero al final del arreglo

    for (const Person *p = persons; p < end; p++) // Aritmética de punteros
    {
        if (p->taxGroup == group) // Acceso con notación de puntero
        {
            total++;
            if (p->age >= age)
                older++;
        }
    }
    return total > 0 ? (100.0 * older / total) : 0.0;
}

double percentageOlderThanByGroup_val(const Person persons[], size_t n, int age, char group)
{
    size_t total = 0, older = 0;

    for (size_t i = 0; i < n; i++) // Acceso por índices
    {
        if (persons[i].taxGroup == group) // Acceso por índice
        {
            total++;
            if (persons[i].age >= age)
                older++;
        }
    }
    return total > 0 ? (100.0 * older / total) : 0.0;
}

double *netWealthByCity_ptr(const Person *persons, size_t n, size_t *cityCount)
{
    char **seen = malloc(n * sizeof(char *));  // Máximo n ciudades únicas
    double *total = calloc(n, sizeof(double)); // Inicializado en 0
    size_t seenCount = 0;

    const Person *end = persons + n;
    for (const Person *p = persons; p < end; p++) // Aritmética de punteros
    {
        int found = -1;
        char **current_seen = seen;
        double *current_total = total;
        for (size_t j = 0; j < seenCount; j++, current_seen++, current_total++)
        {
            if (strcmp(p->residence, *current_seen) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(p->residence) + 1); // Asignar solo para ciudades nuevas
            strcpy(seen[seenCount], p->residence);
            total[seenCount] = p->heritage - p->debts;
            seenCount++;
        }
        else
        {
            *current_total += p->heritage - p->debts;
        }
    }

    double *results = malloc(seenCount * sizeof(double));
    double *current_result = results;
    double *current_total = total;
    for (size_t j = 0; j < seenCount; j++, current_result++, current_total++)
    {
        *current_result = *current_total;
    }

    // Liberar memoria auxiliar
    for (size_t i = 0; i < seenCount; i++)
    {
        free(seen[i]);
    }
    free(seen);
    free(total);

    *cityCount = seenCount;
    return results; // El cliente debe liberar results
}

double *netWealthByCity_val(const Person persons[], size_t n, size_t *cityCount)
{
    char **seen = malloc(n * sizeof(char *));  // Máximo n ciudades únicas
    double *total = calloc(n, sizeof(double)); // Inicializado en 0
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++) // Acceso por índices
    {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++)
        {
            if (strcmp(persons[i].residence, seen[j]) == 0)
            {
                found = j;
                break;
            }
        }
        if (found == -1)
        {
            seen[seenCount] = malloc(strlen(persons[i].residence) + 1); // Asignar solo para ciudades nuevas
            strcpy(seen[seenCount], persons[i].residence);
            total[seenCount] = persons[i].heritage - persons[i].debts;
            seenCount++;
        }
        else
        {
            total[found] += persons[i].heritage - persons[i].debts;
        }
    }

    double *results = malloc(seenCount * sizeof(double));
    for (size_t j = 0; j < seenCount; j++)
    {
        results[j] = total[j];
    }

    // Liberar memoria auxiliar
    for (size_t i = 0; i < seenCount; i++)
    {
        free(seen[i]);
    }
    free(seen);
    free(total);

    *cityCount = seenCount;
    return results; // El cliente debe liberar results
}