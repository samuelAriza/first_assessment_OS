#ifndef QUERIES_CLASS_H
#define QUERIES_CLASS_H

#include <cstddef>  // Para size_t
#include "persona.h"

/**
 * @file queries_class.h
 * @brief Funciones de consulta para análisis de personas - Versión C++ Classes
 * 
 * Este archivo contiene todas las funciones de consulta implementadas tanto
 * para modo punteros (_ptr) como modo valores (_val) para facilitar la
 * comparación de rendimiento entre diferentes enfoques de acceso a memoria.
 */

// =============================================================================
// CONSULTAS BÁSICAS - PERSONAS MÁS LONGEVAS
// =============================================================================

/**
 * @brief Encuentra la persona más longeva del país (modo punteros)
 * @param persons Array de punteros a Persona
 * @param n Número de personas en el array
 * @return Puntero a la persona más longeva, o nullptr si no hay personas
 */
const Persona* findOldest_ptr(const Persona* persons, size_t n);

/**
 * @brief Encuentra la persona más longeva del país (modo valores)
 * @param persons Array de objetos Persona
 * @param n Número de personas en el array
 * @return Copia de la persona más longeva, objeto vacío si no hay personas
 */
Persona findOldest_val(const Persona persons[], size_t n);

/**
 * @brief Encuentra la persona más longeva por ciudad (modo punteros)
 * @param persons Array de punteros a Persona
 * @param n Número de personas
 * @param cityCount Output: número de ciudades encontradas
 * @return Array de punteros a las personas más longevas por ciudad
 * @note El cliente debe liberar el array devuelto con delete[]
 */
const Persona** findOldestByCity_ptr(const Persona* persons, size_t n, size_t* cityCount);

/**
 * @brief Encuentra la persona más longeva por ciudad (modo valores)
 * @param persons Array de objetos Persona
 * @param n Número de personas
 * @param cityCount Output: número de ciudades encontradas
 * @return Array de objetos Persona con las personas más longevas por ciudad
 * @note El cliente debe liberar el array devuelto con delete[]
 */
Persona* findOldestByCity_val(const Persona persons[], size_t n, size_t* cityCount);

// =============================================================================
// CONSULTAS DE PATRIMONIO - PERSONAS MÁS RICAS
// =============================================================================

/**
 * @brief Encuentra la persona con mayor patrimonio del país (modo punteros)
 */
const Persona* findRichest_ptr(const Persona* persons, size_t n);

/**
 * @brief Encuentra la persona con mayor patrimonio del país (modo valores)
 */
Persona findRichest_val(const Persona persons[], size_t n);

/**
 * @brief Encuentra la persona más rica por ciudad (modo punteros)
 */
const Persona** findRichestByCity_ptr(const Persona* persons, size_t n, size_t* cityCount);

/**
 * @brief Encuentra la persona más rica por ciudad (modo valores)
 */
Persona* findRichestByCity_val(const Persona persons[], size_t n, size_t* cityCount);

/**
 * @brief Encuentra la persona más rica por grupo tributario (modo punteros)
 * @param group Grupo tributario ('A', 'B', o 'C')
 */
const Persona* findRichestByGroup_ptr(const Persona* persons, size_t n, char group);

/**
 * @brief Encuentra la persona más rica por grupo tributario (modo valores)
 * @param group Grupo tributario ('A', 'B', o 'C')
 */
Persona findRichestByGroup_val(const Persona persons[], size_t n, char group);

// =============================================================================
// CONSULTAS DE DECLARANTES DE RENTA
// =============================================================================

/**
 * @brief Lista todos los declarantes de renta por grupo (modo punteros)
 * @param group Grupo tributario a consultar
 * @param count Output: número de declarantes encontrados
 */
const Persona** listTaxGroup_ptr(const Persona* persons, size_t n, char group, size_t* count);

/**
 * @brief Lista todos los declarantes de renta por grupo (modo valores)
 */
Persona* listTaxGroup_val(const Persona persons[], size_t n, char group, size_t* count);

/**
 * @brief Cuenta los declarantes de renta por grupo (modo punteros)
 */
size_t countTaxGroup_ptr(const Persona* persons, size_t n, char group);

/**
 * @brief Cuenta los declarantes de renta por grupo (modo valores)
 */
size_t countTaxGroup_val(const Persona persons[], size_t n, char group);

/**
 * @brief Valida la asignación de grupo tributario (modo punteros)
 * @return 1 si es válido (A, B, o C), 0 en caso contrario
 */
int validateTaxGroup_ptr(const Persona* p);

/**
 * @brief Valida la asignación de grupo tributario (modo valores)
 */
int validateTaxGroup_val(Persona p);

// =============================================================================
// CONSULTAS ANALÍTICAS AVANZADAS
// =============================================================================

/**
 * @brief Encuentra la ciudad con mayor promedio de patrimonio (modo punteros)
 * @return String con el nombre de la ciudad (debe liberarse con delete[])
 */
const char* cityWithHighestAvgHeritage_ptr(const Persona* persons, size_t n);

/**
 * @brief Encuentra la ciudad con mayor promedio de patrimonio (modo valores)
 */
const char* cityWithHighestAvgHeritage_val(const Persona persons[], size_t n);

/**
 * @brief Calcula porcentaje de personas mayores de cierta edad por grupo (modo punteros)
 * @param age Edad mínima para el cálculo
 * @param group Grupo tributario
 * @return Porcentaje (0.0 - 100.0)
 */
double percentageOlderThanByGroup_ptr(const Persona* persons, size_t n, int age, char group);

/**
 * @brief Calcula porcentaje de personas mayores de cierta edad por grupo (modo valores)
 */
double percentageOlderThanByGroup_val(const Persona persons[], size_t n, int age, char group);

/**
 * @brief Calcula la riqueza neta total por ciudad (modo punteros)
 * @param cityCount Output: número de ciudades procesadas
 * @return Array de doubles con riqueza neta por ciudad (debe liberarse con delete[])
 */
double* netWealthByCity_ptr(const Persona* persons, size_t n, size_t* cityCount);

/**
 * @brief Calcula la riqueza neta total por ciudad (modo valores)
 */
double* netWealthByCity_val(const Persona persons[], size_t n, size_t* cityCount);

#endif // QUERIES_CLASS_H