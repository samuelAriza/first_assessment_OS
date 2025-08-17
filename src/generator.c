#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static const char *femaleNames[] = {
    "María", "Luisa", "Carmen", "Ana", "Sofía", "Isabel",
    "Laura", "Andrea", "Paula", "Valentina", "Camila",
    "Daniela", "Carolina", "Fernanda", "Gabriela",
    "Patricia", "Claudia", "Diana", "Lucía", "Ximena"};

static const char *maleNames[] = {
    "Juan", "Carlos", "José", "James", "Andrés", "Miguel", "Luis", "Pedro", "Alejandro", "Ricardo",
    "Felipe", "David", "Jorge", "Santiago", "Daniel", "Fernando", "Diego", "Rafael", "Martín", "Óscar",
    "Edison", "Sofia", "Camila", "Juana", "Ana", "Laura", "Karla", "Andrea", "Daniela", "Alejandra", "Martina",
    "Nelly", "María", "Nestor", "Trinidad", "Fernanda", "Carolina", "Lina", "Gertridis"};

static const char *lastNames[] = {
    "Gómez",
    "Rodríguez",
    "Martínez",
    "López",
    "García",
    "Pérez",
    "González",
    "Sánchez",
    "Ramírez",
    "Torres",
    "Díaz",
    "Vargas",
    "Castro",
    "Ruiz",
    "Álvarez",
    "Romero",
    "Suárez",
    "Rojas",
    "Moreno",
    "Muñoz",
    "Valencia",
};

static const char *citesOfColombia[] = {
    "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga", "Pereira", "Santa Marta", "Cúcuta", "Ibagué",
    "Manizales", "Pasto", "Neiva", "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"};

static const size_t femaleCount = (sizeof(femaleNames) / sizeof(femaleNames[0]));
static const size_t maleCount = (sizeof(maleNames) / sizeof(maleNames[0]));
static const size_t lastNameCount = (sizeof(lastNames) / sizeof(lastNames[0]));
static const size_t citiesOfColombiaCount = (sizeof(citesOfColombia) / sizeof(citesOfColombia[0]));

static int randomInt(int min, int max)
{
    return min + rand() % (max - min + 1);
}

static double randomDouble(double min, double max)
{
    return min + (rand() / (double)RAND_MAX) * (max - min);
}

static void generateBirthDate(char *buffer, size_t size)
{
    int day = randomInt(1, 28);
    int month = randomInt(1, 12);
    int year = randomInt(1960, 2010);
    snprintf(buffer, size, "%02d/%02d/%04d", day, month, year);
}

static void generateID(char *buffer, size_t size)
{
    static long currentID = 1000000000;
    snprintf(buffer, size, "%010ld", currentID++);
}

Person *generatePersons(size_t n)
{
    srand((unsigned int)time(NULL));

    Person *persons = malloc(n * sizeof(Person));
    if (!persons)
    {
        fprintf(stderr, "Error: no se pudo asignar memoria para %zu personas\n", n);
        return NULL;
    }

    for (size_t i = 0; i < n; i++)
    {
        int isMale = rand() % 2;

        const char *name = isMale
                               ? maleNames[randomInt(0, (int)maleCount - 1)]
                               : femaleNames[randomInt(0, (int)femaleCount - 1)];

        const char *firstLastName = lastNames[randomInt(0, (int)lastNameCount - 1)];
        const char *secondLastName = lastNames[randomInt(0, (int)lastNameCount - 1)];
        const char *residence = citesOfColombia[randomInt(0, (int)citiesOfColombiaCount - 1)];

        char birthDate[16];
        generateBirthDate(birthDate, sizeof(birthDate));

        char id[11];
        generateID(id, sizeof(id));

        double heritage = randomDouble(0, 2000000000.0);
        double debts = randomDouble(0, heritage * 0.7);

        persons[i] = createPerson(name, firstLastName, secondLastName, birthDate, residence, heritage, debts, id);
    }

    return persons;
}