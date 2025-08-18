#ifndef QUERIES_H
#define QUERIES_H

#include <stddef.h>
#include "person.h"

// Oldest person
const Person* findOldest_ptr(const Person* persons, size_t n);
Person findOldest_val(const Person persons[], size_t n);

//Longest-lived person in each city
const Person** findOldestByCity_ptr(const Person* persons, size_t n, size_t* cityCount);
Person* findOldestByCity_val(const Person persons[], size_t n, size_t* cityCount);

//Person with greater wealth

// Person with the greatest assets in the entire country
const Person* findRichest_ptr(const Person* persons, size_t n);
Person findRichest_val(const Person persons[], size_t n);

// Person with the greatest wealth by city
const Person** findRichestByCity_ptr(const Person* persons, size_t n, size_t* cityCount);
Person* findRichestByCity_val(const Person persons[], size_t n, size_t* cityCount);

// Person with the greatest assets by declaration group
const Person* findRichestByGroup_ptr(const Person* persons, size_t n, char group);
Person findRichestByGroup_val(const Person persons[], size_t n, char group);

//Income tax returnees

// List people by group
const Person** listByGroup_ptr(const Person* persons, size_t n, char group, size_t* count);
Person* listByGroup_val(const Person persons[], size_t n, char group, size_t* count);

// Count people per group
size_t countByGroup_ptr(const Person* persons, size_t n, char group);
size_t countByGroup_val(const Person persons[], size_t n, char group);

// Validate group assignment based on document completion
int validateTaxGroup_ptr(const Person* p);
int validateTaxGroup_val(Person p);

//Additional queries

// City with the highest average net worth
const char* cityWithHighestAvgHeritage_ptr(const Person* persons, size_t n);
const char* cityWithHighestAvgHeritage_val(const Person persons[], size_t n);

// Percentage of people over a certain age by tax bracket
double percentageOlderThanByGroup_ptr(const Person* persons, size_t n, int age, char group);
double percentageOlderThanByGroup_val(const Person persons[], size_t n, int age, char group);

// Total net worth (assets - liabilities) by city
double* netWealthByCity_ptr(const Person* persons, size_t n, size_t* cityCount);
double* netWealthByCity_val(const Person persons[], size_t n, size_t* cityCount);

#endif
