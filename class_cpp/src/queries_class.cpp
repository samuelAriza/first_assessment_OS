#include "queries_class.h"
#include <cstring> // strcmp, strcpy, strdup
#include <algorithm> // Para std::copy
#include <new>     // Para bad_alloc si aplica, pero no usado explícitamente

// Persona más longeva - País (_ptr)
const Persona *findOldest_ptr(const Persona *persons, size_t n) {
    if (!persons || n == 0) return nullptr;
    const Persona *oldest = persons;
    const Persona *current = persons + 1;
    const Persona *end = persons + n;
    for (; current < end; current++) {
        if (current->getEdad() > oldest->getEdad()) oldest = current;
    }
    return oldest;
}

// Persona más longeva - País (_val)
Persona findOldest_val(const Persona persons[], size_t n) {
    Persona empty; // Usa constructor por defecto (id="")
    if (!persons || n == 0) return empty;
    Persona oldest = persons[0]; // Copia
    for (size_t i = 1; i < n; i++) {
        if (persons[i].getEdad() > oldest.getEdad()) oldest = persons[i]; // Copia
    }
    return oldest;
}

// Persona más longeva - Por ciudad (_ptr)
const Persona **findOldestByCity_ptr(const Persona *persons, size_t n, size_t *cityCount) {
    if (!persons || n == 0) { *cityCount = 0; return nullptr; }
    char **seen = new char*[n];
    const Persona **results = new const Persona*[n];
    size_t seenCount = 0;

    const Persona *end = persons + n;
    for (const Persona *current = persons; current < end; current++) {
        int found = -1;
        char **current_seen = seen;
        const Persona **current_result = results;
        for (size_t j = 0; j < seenCount; j++, current_seen++, current_result++) {
            if (std::strcmp(current->getCiudadNacimiento().c_str(), *current_seen) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[current->getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], current->getCiudadNacimiento().c_str());
            results[seenCount] = current;
            seenCount++;
        } else {
            if (current->getEdad() > (*current_result)->getEdad()) *current_result = current;
        }
    }

    // Redimensionar results
    const Persona **final_results = new const Persona*[seenCount];
    std::memcpy(final_results, results, seenCount * sizeof(const Persona*));
    delete[] results; // Libera el grande

    // Libera seen
    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;

    *cityCount = seenCount;
    return final_results; // Cliente libera delete[] final_results
}

// Persona más longeva - Por ciudad (_val)
Persona *findOldestByCity_val(const Persona persons[], size_t n, size_t *cityCount) {
    if (!persons || n == 0) { *cityCount = 0; return nullptr; }
    char **seen = new char*[n];
    Persona *results = new Persona[n];
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++) {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++) {
            if (std::strcmp(persons[i].getCiudadNacimiento().c_str(), seen[j]) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[persons[i].getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], persons[i].getCiudadNacimiento().c_str());
            results[seenCount] = persons[i]; // Copia
            seenCount++;
        } else {
            if (persons[i].getEdad() > results[found].getEdad()) results[found] = persons[i]; // Copia
        }
    }

    // Redimensionar results usando copia elemento por elemento
    Persona *final_results = new Persona[seenCount];
    for (size_t i = 0; i < seenCount; i++) {
        final_results[i] = results[i]; // Copia segura
    }
    delete[] results; // Libera el grande

    // Libera seen
    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;

    *cityCount = seenCount;
    return final_results; // Cliente libera delete[] final_results
}

// Persona con mayor patrimonio - País (_ptr)
const Persona *findRichest_ptr(const Persona *persons, size_t n) {
    if (!persons || n == 0) return nullptr;
    const Persona *richest = persons;
    const Persona *current = persons + 1;
    const Persona *end = persons + n;
    for (; current < end; current++) {
        if (current->getPatrimonio() > richest->getPatrimonio()) richest = current;
    }
    return richest;
}

// Persona con mayor patrimonio - País (_val)
Persona findRichest_val(const Persona persons[], size_t n) {
    Persona empty; // Usa constructor por defecto
    if (!persons || n == 0) return empty;
    Persona richest = persons[0]; // Copia
    for (size_t i = 1; i < n; i++) {
        if (persons[i].getPatrimonio() > richest.getPatrimonio()) richest = persons[i]; // Copia
    }
    return richest;
}

// Persona con mayor patrimonio - Por ciudad (_ptr)
const Persona **findRichestByCity_ptr(const Persona *persons, size_t n, size_t *cityCount) {
    if (!persons || n == 0) { *cityCount = 0; return nullptr; }
    char **seen = new char*[n];
    const Persona **results = new const Persona*[n];
    size_t seenCount = 0;

    const Persona *end = persons + n;
    for (const Persona *current = persons; current < end; current++) {
        int found = -1;
        char **current_seen = seen;
        const Persona **current_result = results;
        for (size_t j = 0; j < seenCount; j++, current_seen++, current_result++) {
            if (std::strcmp(current->getCiudadNacimiento().c_str(), *current_seen) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[current->getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], current->getCiudadNacimiento().c_str());
            results[seenCount] = current;
            seenCount++;
        } else {
            if (current->getPatrimonio() > (*current_result)->getPatrimonio()) *current_result = current;
        }
    }

    const Persona **final_results = new const Persona*[seenCount];
    std::memcpy(final_results, results, seenCount * sizeof(const Persona*));
    delete[] results;

    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;

    *cityCount = seenCount;
    return final_results;
}

// Persona con mayor patrimonio - Por ciudad (_val)
Persona *findRichestByCity_val(const Persona persons[], size_t n, size_t *cityCount) {
    if (!persons || n == 0) { *cityCount = 0; return nullptr; }
    char **seen = new char*[n];
    Persona *results = new Persona[n];
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++) {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++) {
            if (std::strcmp(persons[i].getCiudadNacimiento().c_str(), seen[j]) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[persons[i].getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], persons[i].getCiudadNacimiento().c_str());
            results[seenCount] = persons[i]; // Copia
            seenCount++;
        } else {
            if (persons[i].getPatrimonio() > results[found].getPatrimonio()) results[found] = persons[i]; // Copia
        }
    }

    Persona *final_results = new Persona[seenCount];
    for (size_t i = 0; i < seenCount; i++) {
        final_results[i] = results[i]; // Copia segura
    }
    delete[] results;

    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;

    *cityCount = seenCount;
    return final_results;
}

// Persona con mayor patrimonio - Por grupo (_ptr)
const Persona *findRichestByGroup_ptr(const Persona *persons, size_t n, char group) {
    if (!persons || n == 0) return nullptr;
    const Persona *richest = nullptr;
    const Persona *current = persons;
    const Persona *end = persons + n;
    for (; current < end; current++) {
        if (current->getTaxGroup() == group) {
            if (!richest || current->getPatrimonio() > richest->getPatrimonio()) richest = current;
        }
    }
    return richest;
}

// Persona con mayor patrimonio - Por grupo (_val)
Persona findRichestByGroup_val(const Persona persons[], size_t n, char group) {
    Persona empty; // Usa constructor por defecto
    if (!persons || n == 0) return empty;
    Persona richest = empty;
    for (size_t i = 0; i < n; i++) {
        if (persons[i].getTaxGroup() == group) {
            if (richest.getId().empty() || persons[i].getPatrimonio() > richest.getPatrimonio()) richest = persons[i]; // Copia
        }
    }
    return richest;
}

// Listar declarantes por grupo (_ptr)
const Persona **listTaxGroup_ptr(const Persona *persons, size_t n, char group, size_t *count) {
    if (!persons || n == 0) { *count = 0; return nullptr; }
    const Persona **results = new const Persona*[n]; // Max n
    size_t c = 0;

    const Persona *end = persons + n;
    for (const Persona *p = persons; p < end; p++) {
        if (p->getTaxGroup() == group && p->getDeclaranteRenta()) results[c++] = p;
    }

    const Persona **final_results = new const Persona*[c];
    std::memcpy(final_results, results, c * sizeof(const Persona*));
    delete[] results;

    *count = c;
    return final_results;
}

// Listar declarantes por grupo (_val)
Persona *listTaxGroup_val(const Persona persons[], size_t n, char group, size_t *count) {
    if (!persons || n == 0) { *count = 0; return nullptr; }
    Persona *results = new Persona[n]; // Max n
    size_t c = 0;

    for (size_t i = 0; i < n; i++) {
        if (persons[i].getTaxGroup() == group && persons[i].getDeclaranteRenta()) results[c++] = persons[i]; // Copia
    }

    Persona *final_results = new Persona[c];
    for (size_t i = 0; i < c; i++) {
        final_results[i] = results[i]; // Copia segura
    }
    delete[] results;

    *count = c;
    return final_results;
}

// Contar declarantes por grupo (_ptr)
size_t countTaxGroup_ptr(const Persona *persons, size_t n, char group) {
    size_t c = 0;
    const Persona *end = persons + n;
    for (const Persona *p = persons; p < end; p++) {
        if (p->getTaxGroup() == group && p->getDeclaranteRenta()) c++;
    }
    return c;
}

// Contar declarantes por grupo (_val)
size_t countTaxGroup_val(const Persona persons[], size_t n, char group) {
    size_t c = 0;
    for (size_t i = 0; i < n; i++) {
        if (persons[i].getTaxGroup() == group && persons[i].getDeclaranteRenta()) c++;
    }
    return c;
}

// Validar asignación de grupo (_ptr)
int validateTaxGroup_ptr(const Persona *p) {
    return p && (p->getTaxGroup() == 'A' || p->getTaxGroup() == 'B' || p->getTaxGroup() == 'C');
}

// Validar asignación de grupo (_val)
int validateTaxGroup_val(Persona p) {
    return (p.getTaxGroup() == 'A' || p.getTaxGroup() == 'B' || p.getTaxGroup() == 'C');
}

// Ciudad con mayor promedio patrimonio (_ptr)
const char *cityWithHighestAvgHeritage_ptr(const Persona *persons, size_t n) {
    if (!persons || n == 0) return nullptr;
    char **seen = new char*[n];
    double *sum = new double[n](); // Inicializado 0
    size_t *count = new size_t[n](); // Inicializado 0
    size_t seenCount = 0;

    const Persona *end = persons + n;
    for (const Persona *current = persons; current < end; current++) {
        int found = -1;
        char **current_seen = seen;
        for (size_t j = 0; j < seenCount; j++, current_seen++) {
            if (std::strcmp(current->getCiudadNacimiento().c_str(), *current_seen) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[current->getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], current->getCiudadNacimiento().c_str());
            sum[seenCount] = current->getPatrimonio();
            count[seenCount] = 1;
            seenCount++;
        } else {
            sum[found] += current->getPatrimonio();
            count[found]++;
        }
    }

    char *result = nullptr;
    if (seenCount > 0) {
        size_t best = 0;
        double bestAvg = sum[0] / count[0];
        for (size_t j = 1; j < seenCount; j++) {
            double avg = sum[j] / count[j];
            if (avg > bestAvg) {
                bestAvg = avg;
                best = j;
            }
        }
        result = new char[std::strlen(seen[best]) + 1];
        std::strcpy(result, seen[best]);
    }

    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;
    delete[] sum;
    delete[] count;

    return result; // Cliente libera delete[] result
}

// Ciudad con mayor promedio patrimonio (_val)
const char *cityWithHighestAvgHeritage_val(const Persona persons[], size_t n) {
    if (!persons || n == 0) return nullptr;
    char **seen = new char*[n];
    double *sum = new double[n](); 
    size_t *count = new size_t[n](); 
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++) {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++) {
            if (std::strcmp(persons[i].getCiudadNacimiento().c_str(), seen[j]) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[persons[i].getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], persons[i].getCiudadNacimiento().c_str());
            sum[seenCount] = persons[i].getPatrimonio();
            count[seenCount] = 1;
            seenCount++;
        } else {
            sum[found] += persons[i].getPatrimonio();
            count[found]++;
        }
    }

    char *result = nullptr;
    if (seenCount > 0) {
        size_t best = 0;
        double bestAvg = sum[0] / count[0];
        for (size_t j = 1; j < seenCount; j++) {
            double avg = sum[j] / count[j];
            if (avg > bestAvg) {
                bestAvg = avg;
                best = j;
            }
        }
        result = new char[std::strlen(seen[best]) + 1];
        std::strcpy(result, seen[best]);
    }

    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;
    delete[] sum;
    delete[] count;

    return result;
}

// Porcentaje > edad por grupo (_ptr)
double percentageOlderThanByGroup_ptr(const Persona *persons, size_t n, int age, char group) {
    size_t total = 0, older = 0;
    const Persona *end = persons + n;
    for (const Persona *p = persons; p < end; p++) {
        if (p->getTaxGroup() == group) {
            total++;
            if (p->getEdad() >= age) older++;
        }
    }
    return total > 0 ? (100.0 * older / total) : 0.0;
}

// Porcentaje > edad por grupo (_val)
double percentageOlderThanByGroup_val(const Persona persons[], size_t n, int age, char group) {
    size_t total = 0, older = 0;
    for (size_t i = 0; i < n; i++) {
        if (persons[i].getTaxGroup() == group) {
            total++;
            if (persons[i].getEdad() >= age) older++;
        }
    }
    return total > 0 ? (100.0 * older / total) : 0.0;
}

// Riqueza neta por ciudad (_ptr)
double *netWealthByCity_ptr(const Persona *persons, size_t n, size_t *cityCount) {
    if (!persons || n == 0) { *cityCount = 0; return nullptr; }
    char **seen = new char*[n];
    double *total = new double[n](); 
    size_t seenCount = 0;

    const Persona *end = persons + n;
    for (const Persona *p = persons; p < end; p++) {
        int found = -1;
        char **current_seen = seen;
        double *current_total = total;
        for (size_t j = 0; j < seenCount; j++, current_seen++, current_total++) {
            if (std::strcmp(p->getCiudadNacimiento().c_str(), *current_seen) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[p->getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], p->getCiudadNacimiento().c_str());
            total[seenCount] = p->getPatrimonio() - p->getDeudas();
            seenCount++;
        } else {
            *current_total += p->getPatrimonio() - p->getDeudas();
        }
    }

    double *results = new double[seenCount];
    std::memcpy(results, total, seenCount * sizeof(double));
    delete[] total;

    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;

    *cityCount = seenCount;
    return results; // Cliente libera delete[] results
}

// Riqueza neta por ciudad (_val)
double *netWealthByCity_val(const Persona persons[], size_t n, size_t *cityCount) {
    if (!persons || n == 0) { *cityCount = 0; return nullptr; }
    char **seen = new char*[n];
    double *total = new double[n](); 
    size_t seenCount = 0;

    for (size_t i = 0; i < n; i++) {
        int found = -1;
        for (size_t j = 0; j < seenCount; j++) {
            if (std::strcmp(persons[i].getCiudadNacimiento().c_str(), seen[j]) == 0) {
                found = j;
                break;
            }
        }
        if (found == -1) {
            seen[seenCount] = new char[persons[i].getCiudadNacimiento().length() + 1];
            std::strcpy(seen[seenCount], persons[i].getCiudadNacimiento().c_str());
            total[seenCount] = persons[i].getPatrimonio() - persons[i].getDeudas();
            seenCount++;
        } else {
            total[found] += persons[i].getPatrimonio() - persons[i].getDeudas();
        }
    }

    double *results = new double[seenCount];
    std::memcpy(results, total, seenCount * sizeof(double));
    delete[] total;

    for (size_t i = 0; i < seenCount; i++) delete[] seen[i];
    delete[] seen;

    *cityCount = seenCount;
    return results;
}