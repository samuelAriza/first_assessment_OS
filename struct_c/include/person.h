#ifndef PERSONA_H
#define PERSONA_H

typedef struct {
    char firstName[50];
    char firstLastName[50];
    char secondLastName[50];
    char birthDate[16];
    int age;
    char residence[50];
    double heritage;
    double debts;
    char id[11];
    char taxGroup;
} Person;

Person createPerson(const char* firstName, const char* firstLastName, const char* secondLastName, const char* birthDate, const char* residence, double heritage, double debts, const char* id);
void show(const Person* p);

#endif