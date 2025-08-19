#include "generador.h"
#include <cstdlib> // rand(), srand()
#include <ctime>   // time()
#include <random>  // Modern random generators
#include <vector>
#include <algorithm> // For find_if

// --- Databases for realistic generation ---

/// Common female names in Colombia.
const std::vector<std::string> nombresFemeninos = {
    "María", "Luisa", "Carmen", "Ana", "Sofía", "Isabel", "Laura", "Andrea", "Paula", "Valentina",
    "Camila", "Daniela", "Carolina", "Fernanda", "Gabriela", "Patricia", "Claudia", "Diana", "Lucía", "Ximena"};

/// Common male names in Colombia.
const std::vector<std::string> nombresMasculinos = {
    "Juan", "Carlos", "José", "James", "Andrés", "Miguel", "Luis", "Pedro", "Alejandro", "Ricardo",
    "Felipe", "David", "Jorge", "Santiago", "Daniel", "Fernando", "Diego", "Rafael", "Martín", "Óscar",
    "Edison", "Sofia", "Camila", "Juana", "Ana", "Laura", "Karla", "Andrea", "Daniela", "Alejandra", "Martina",
    "Nelly", "María", "Nestor", "Trinidad", "Fernanda", "Carolina", "Lina", "Gertridis"};

/// Common last names in Colombia.
const std::vector<std::string> apellidos = {
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

/// Main Colombian cities.
const std::vector<std::string> ciudadesColombia = {
    "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga", "Pereira", "Santa Marta", "Cúcuta", "Ibagué",
    "Manizales", "Pasto", "Neiva", "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"};

// --- Generator function implementations ---

std::string generarFechaNacimiento()
{
    /// Generates a random day (1-28 for simplification).
    int dia = 1 + rand() % 28;
    /// Random month (1-12).
    int mes = 1 + rand() % 12;
    /// Year between 1960-2010.
    int anio = 1960 + rand() % 50;

    /// Converts to string in DD/MM/YYYY format.
    return std::to_string(dia) + "/" + std::to_string(mes) + "/" + std::to_string(anio);
}

std::string generarID()
{
    static long contador = 1000000000; ///< Initial ID.
    return std::to_string(contador++); ///< Increment after use.
}

double randomDouble(double min, double max)
{
    /// Modern Mersenne Twister generator.
    static std::mt19937 generator(time(nullptr));
    /// Uniform distribution in range [min, max].
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

Persona generarPersona()
{
    /// Randomly decide gender.
    bool esHombre = rand() % 2;

    /// Select name based on gender.
    std::string nombre = esHombre ? nombresMasculinos[rand() % nombresMasculinos.size()] : nombresFemeninos[rand() % nombresFemeninos.size()];

    /// Combine two random last names.
    std::string apellido = apellidos[rand() % apellidos.size()] + " " +
                           apellidos[rand() % apellidos.size()];

    /// Generate unique identifiers.
    std::string id = generarID();
    /// Random city from Colombia.
    std::string ciudad = ciudadesColombia[rand() % ciudadesColombia.size()];
    /// Random birth date.
    std::string fecha = generarFechaNacimiento();

    // --- Realistic economic data generation ---
    /// Income between 10 million and 500 million COP.
    double ingresos = randomDouble(10000000, 500000000);
    /// Heritage between 0 and 2 billion COP.
    double patrimonio = randomDouble(0, 2000000000);
    /// Debts up to 70% of heritage.
    double deudas = randomDouble(0, patrimonio * 0.7);
    /// 70% probability of being a tax declarant if income > 50 million.
    bool declarante = (ingresos > 50000000) && (rand() % 100 > 30);

    /// Builds and returns a Persona object.
    return Persona(nombre, apellido, id, ciudad, fecha, ingresos, patrimonio, deudas, declarante);
}

std::vector<Persona> generarColeccion(int n)
{
    std::vector<Persona> personas;
    /// Reserve space for n persons (optimization).
    personas.reserve(n);

    /// Generate n persons and add them to the vector.
    for (int i = 0; i < n; ++i)
    {
        personas.push_back(generarPersona());
    }

    return personas;
}

const Persona *buscarPorID(const std::vector<Persona> &personas, const std::string &id)
{
    /// Linear search by ID (simple solution for medium collections).
    for (const auto &persona : personas)
    {
        if (persona.getId() == id)
        {
            return &persona; ///< Return address if a match is found.
        }
    }
    return nullptr; ///< Return null if not found.
}