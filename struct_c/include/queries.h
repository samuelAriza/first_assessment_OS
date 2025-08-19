#ifndef QUERIES_H
#define QUERIES_H

#include <stddef.h>
#include "person.h"

/// @brief Finds the oldest person in the dataset (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @return Pointer to the oldest person, or NULL if none.
const Person* findOldest_ptr(const Person* persons, size_t n);

/// @brief Finds the oldest person in the dataset (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @return The oldest person structure.
Person findOldest_val(const Person persons[], size_t n);

/// @brief Finds the oldest person in each city (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param cityCount Output parameter for number of distinct cities.
/// @return Array of pointers to the oldest persons by city (must be freed).
const Person** findOldestByCity_ptr(const Person* persons, size_t n, size_t* cityCount);

/// @brief Finds the oldest person in each city (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param cityCount Output parameter for number of distinct cities.
/// @return Array of oldest persons by city (must be freed).
Person* findOldestByCity_val(const Person persons[], size_t n, size_t* cityCount);

/// @brief Finds the richest person in the dataset (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @return Pointer to the richest person, or NULL if none.
const Person* findRichest_ptr(const Person* persons, size_t n);

/// @brief Finds the richest person in the dataset (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @return The richest person structure.
Person findRichest_val(const Person persons[], size_t n);

/// @brief Finds the richest person in each city (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param cityCount Output parameter for number of distinct cities.
/// @return Array of pointers to the richest persons by city (must be freed).
const Person** findRichestByCity_ptr(const Person* persons, size_t n, size_t* cityCount);

/// @brief Finds the richest person in each city (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param cityCount Output parameter for number of distinct cities.
/// @return Array of richest persons by city (must be freed).
Person* findRichestByCity_val(const Person persons[], size_t n, size_t* cityCount);

/// @brief Finds the richest person in a given tax group (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param group Tax group to filter by.
/// @return Pointer to the richest person in the group, or NULL if none.
const Person* findRichestByGroup_ptr(const Person* persons, size_t n, char group);

/// @brief Finds the richest person in a given tax group (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param group Tax group to filter by.
/// @return The richest person structure in the group.
Person findRichestByGroup_val(const Person persons[], size_t n, char group);

/// @brief Lists all persons belonging to a specific tax group (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param group Tax group to filter by.
/// @param count Output parameter for number of persons in group.
/// @return Array of pointers to persons in the group (must be freed).
const Person** listByGroup_ptr(const Person* persons, size_t n, char group, size_t* count);

/// @brief Lists all persons belonging to a specific tax group (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param group Tax group to filter by.
/// @param count Output parameter for number of persons in group.
/// @return Array of persons in the group (must be freed).
Person* listByGroup_val(const Person persons[], size_t n, char group, size_t* count);

/// @brief Counts the number of persons in a given tax group (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param group Tax group to filter by.
/// @return Number of persons in the group.
size_t countByGroup_ptr(const Person* persons, size_t n, char group);

/// @brief Counts the number of persons in a given tax group (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param group Tax group to filter by.
/// @return Number of persons in the group.
size_t countByGroup_val(const Person persons[], size_t n, char group);

/// @brief Validates tax group assignment based on ID (pointer version).
/// @param p Pointer to a person.
/// @return 1 if valid, 0 otherwise.
int validateTaxGroup_ptr(const Person* p);

/// @brief Validates tax group assignment based on ID (by value version).
/// @param p Person structure.
/// @return 1 if valid, 0 otherwise.
int validateTaxGroup_val(Person p);

/// @brief Finds the city with the highest average net heritage (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @return Dynamically allocated string with city name (must be freed).
const char* cityWithHighestAvgHeritage_ptr(const Person* persons, size_t n);

/// @brief Finds the city with the highest average net heritage (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @return Dynamically allocated string with city name (must be freed).
const char* cityWithHighestAvgHeritage_val(const Person persons[], size_t n);

/// @brief Calculates the percentage of persons older than a given age within a tax group (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param age Age threshold.
/// @param group Tax group to filter by.
/// @return Percentage of persons meeting the criteria.
double percentageOlderThanByGroup_ptr(const Person* persons, size_t n, int age, char group);

/// @brief Calculates the percentage of persons older than a given age within a tax group (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param age Age threshold.
/// @param group Tax group to filter by.
/// @return Percentage of persons meeting the criteria.
double percentageOlderThanByGroup_val(const Person persons[], size_t n, int age, char group);

/// @brief Computes the net wealth (heritage - debts) by city (pointer version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param cityCount Output parameter for number of distinct cities.
/// @return Array of net wealth values per city (must be freed).
double* netWealthByCity_ptr(const Person* persons, size_t n, size_t* cityCount);

/// @brief Computes the net wealth (heritage - debts) by city (by value version).
/// @param persons Array of persons.
/// @param n Number of persons.
/// @param cityCount Output parameter for number of distinct cities.
/// @return Array of net wealth values per city (must be freed).
double* netWealthByCity_val(const Person persons[], size_t n, size_t* cityCount);

#endif