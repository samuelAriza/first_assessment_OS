#include <stdio.h>
#include <string.h>
#include "person.h"
#include <stdlib.h>
#include <time.h>

static int calculateAge(const char *birthDate)
{
    int day, month, year;
    sscanf(birthDate, "%d/%d/%d", &day, &month, &year);
    time_t t = time(NULL);
    struct tm tm_now = *localtime(&t);
    int age = (tm_now.tm_year + 1900) - year;
    if ((month > (tm_now.tm_mon + 1)) ||
        (month == (tm_now.tm_mon + 1) && day > tm_now.tm_mday))
    {
        age--;
    }

    return age;
}

static char calculateTaxGroup(const char *id)
{
    size_t len = strlen(id);
    char lastTwo[3]; // 2 dígitos + '\0'
    lastTwo[0] = id[len - 2];
    lastTwo[1] = id[len - 1];
    lastTwo[2] = '\0';

    int num = atoi(lastTwo);
    
    if (num >= 0 && num <= 39)
    {
        return 'A';
    }
    else if (num >= 40 && num <= 79)
    {
        return 'B';
    }
    else
    {
        return 'C';
    }
}

Person createPerson(const char *firstName, const char *firstLastName, const char *secondLastName, const char *birthDate, const char *residence, double heritage, double debts, const char *id)
{

    Person p;
    strncpy(p.firstName, firstName, sizeof(p.firstName) - 1);
    p.firstName[sizeof(p.firstName) - 1] = '\0';

    strncpy(p.firstLastName, firstLastName, sizeof(p.firstLastName) - 1);
    p.firstLastName[sizeof(p.firstLastName) - 1] = '\0';

    strncpy(p.secondLastName, secondLastName, sizeof(p.secondLastName) - 1);
    p.secondLastName[sizeof(p.secondLastName) - 1] = '\0';

    strncpy(p.birthDate, birthDate, sizeof(p.birthDate) - 1);
    p.birthDate[sizeof(p.birthDate) - 1] = '\0';

    p.age = calculateAge(birthDate);

    strncpy(p.residence, residence, sizeof(p.residence) - 1);
    p.residence[sizeof(p.residence) - 1] = '\0';

    p.heritage = heritage;
    p.debts = debts;

    strncpy(p.id, id, sizeof(p.id) - 1);
    p.id[sizeof(p.id) - 1] = '\0';

    p.taxGroup = calculateTaxGroup(p.id);

    return p;
}

void show(const Person *p)
{
    printf("-------------------------------------\n");
    printf("[%s] Name: %s %s %s\n", p->id, p->firstName, p->firstLastName, p->secondLastName);
    printf("   - Birthdate: %s\n", p->birthDate);
    printf("   - Age: %d\n", p->age);
    printf("   - City: %s\n", p->residence);
    printf("   - Heritage: $%.2f\n", p->heritage);
    printf("   - Debts: $%.2f\n", p->debts);
    printf("   - Tax group: %c\n", p->taxGroup);
    fflush(stdout);
}