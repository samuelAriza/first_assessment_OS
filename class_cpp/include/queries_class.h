#ifndef QUERIES_CLASS_H
#define QUERIES_CLASS_H

#include <cstddef> // For size_t
#include "persona.h"

/**
 * @file queries_class.h
 * @brief Query functions for people analysis - C++ Classes version.
 *
 * This file contains all query functions implemented both in
 * pointer mode (_ptr) and value mode (_val) to facilitate
 * performance comparison between different memory access approaches.
 */

/**
 * @brief Finds the oldest person in the country (pointer mode).
 * @param persons Array of Persona objects.
 * @param n Number of persons in the array.
 * @return Pointer to the oldest person, or nullptr if no persons exist.
 */
const Persona *findOldest_ptr(const Persona *persons, size_t n);

/**
 * @brief Finds the oldest person in the country (value mode).
 * @param persons Array of Persona objects.
 * @param n Number of persons in the array.
 * @return Copy of the oldest person, or an empty object if no persons exist.
 */
Persona findOldest_val(const Persona persons[], size_t n);

/**
 * @brief Finds the oldest person by city (pointer mode).
 * @param persons Array of Persona objects.
 * @param n Number of persons.
 * @param cityCount Output: number of cities found.
 * @return Array of pointers to the oldest persons by city.
 * @note The client must free the returned array with delete[].
 */
const Persona **findOldestByCity_ptr(const Persona *persons, size_t n, size_t *cityCount);

/**
 * @brief Finds the oldest person by city (value mode).
 * @param persons Array of Persona objects.
 * @param n Number of persons.
 * @param cityCount Output: number of cities found.
 * @return Array of Persona objects with the oldest persons by city.
 * @note The client must free the returned array with delete[].
 */
Persona *findOldestByCity_val(const Persona persons[], size_t n, size_t *cityCount);

/**
 * @brief Finds the wealthiest person in the country (pointer mode).
 */
const Persona *findRichest_ptr(const Persona *persons, size_t n);

/**
 * @brief Finds the wealthiest person in the country (value mode).
 */
Persona findRichest_val(const Persona persons[], size_t n);

/**
 * @brief Finds the wealthiest person by city (pointer mode).
 */
const Persona **findRichestByCity_ptr(const Persona *persons, size_t n, size_t *cityCount);

/**
 * @brief Finds the wealthiest person by city (value mode).
 */
Persona *findRichestByCity_val(const Persona persons[], size_t n, size_t *cityCount);

/**
 * @brief Finds the wealthiest person by tax group (pointer mode).
 * @param group Tax group ('A', 'B', or 'C').
 */
const Persona *findRichestByGroup_ptr(const Persona *persons, size_t n, char group);

/**
 * @brief Finds the wealthiest person by tax group (value mode).
 * @param group Tax group ('A', 'B', or 'C').
 */
Persona findRichestByGroup_val(const Persona persons[], size_t n, char group);

/**
 * @brief Lists all tax declarants by group (pointer mode).
 * @param group Tax group to query.
 * @param count Output: number of declarants found.
 */
const Persona **listTaxGroup_ptr(const Persona *persons, size_t n, char group, size_t *count);

/**
 * @brief Lists all tax declarants by group (value mode).
 */
Persona *listTaxGroup_val(const Persona persons[], size_t n, char group, size_t *count);

/**
 * @brief Counts tax declarants by group (pointer mode).
 */
size_t countTaxGroup_ptr(const Persona *persons, size_t n, char group);

/**
 * @brief Counts tax declarants by group (value mode).
 */
size_t countTaxGroup_val(const Persona persons[], size_t n, char group);

/**
 * @brief Validates the tax group assignment (pointer mode).
 * @return 1 if valid (A, B, or C), 0 otherwise.
 */
int validateTaxGroup_ptr(const Persona *p);

/**
 * @brief Validates the tax group assignment (value mode).
 */
int validateTaxGroup_val(Persona p);

/**
 * @brief Finds the city with the highest average heritage (pointer mode).
 * @return String with the name of the city (must be freed with delete[]).
 */
const char *cityWithHighestAvgHeritage_ptr(const Persona *persons, size_t n);

/**
 * @brief Finds the city with the highest average heritage (value mode).
 */
const char *cityWithHighestAvgHeritage_val(const Persona persons[], size_t n);

/**
 * @brief Calculates the percentage of people older than a given age by tax group (pointer mode).
 * @param age Minimum age for calculation.
 * @param group Tax group.
 * @return Percentage (0.0 - 100.0).
 */
double percentageOlderThanByGroup_ptr(const Persona *persons, size_t n, int age, char group);

/**
 * @brief Calculates the percentage of people older than a given age by tax group (value mode).
 */
double percentageOlderThanByGroup_val(const Persona persons[], size_t n, int age, char group);

/**
 * @brief Calculates total net wealth per city (pointer mode).
 * @param cityCount Output: number of cities processed.
 * @return Array of doubles with net wealth per city (must be freed with delete[]).
 */
double *netWealthByCity_ptr(const Persona *persons, size_t n, size_t *cityCount);

/**
 * @brief Calculates total net wealth per city (value mode).
 */
double *netWealthByCity_val(const Persona persons[], size_t n, size_t *cityCount);

#endif // QUERIES_CLASS_H
