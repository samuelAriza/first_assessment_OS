#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int main() {
    size_t n = 1000000; // cantidad de personas de prueba
    Person* persons = generatePersons(n);

    if (!persons) {
        fprintf(stderr, "Error: no se pudieron generar personas\n");
        return 1;
    }

    for (size_t i = 0; i < n; i++) {
        show(&persons[i]);
    }

    free(persons);
    return 0;
}
