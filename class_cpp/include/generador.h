#ifndef GENERADOR_H
#define GENERADOR_H

#include "persona.h"
#include <vector>

/// --- Functions for random data generation ---

/// Generates a random date between 1960-2010.
/// @return A string representing the generated date.
std::string generarFechaNacimiento();

/// Generates a unique sequential ID.
/// @return A string representing the generated ID.
std::string generarID();

/// Generates a random decimal number within the range [min, max].
/// @param min Minimum value.
/// @param max Maximum value.
/// @return A random double within the specified range.
double randomDouble(double min, double max);

/// Creates a person with random data.
/// @return A Persona object with generated attributes.
Persona generarPersona();

/// Generates a collection of n persons.
/// @param n Number of persons to generate.
/// @return A vector containing the generated persons.
std::vector<Persona> generarColeccion(int n);

/// Searches for a person by ID within a vector.
/// @param personas Vector of persons to search.
/// @param id The ID to search for.
/// @return A pointer to the found person, or nullptr if not found.
const Persona* buscarPorID(const std::vector<Persona>& personas, const std::string& id);

#endif // GENERADOR_H