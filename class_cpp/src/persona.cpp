#include "persona.h"
#include <iostream>
#include <iomanip> // For output formatting (setprecision, fixed)
#include <sstream> // For string parsing

// Constructor implementation
Persona::Persona(std::string nom, std::string ape, std::string id,
                 std::string ciudad, std::string fecha, double ingresos,
                 double patri, double deud, bool declara)
    : nombre(nom), apellido(ape), id(id), ciudadNacimiento(ciudad),
      fechaNacimiento(fecha), ingresosAnuales(ingresos), patrimonio(patri),
      deudas(deud), declaranteRenta(declara)
{
    // Initialization through initializer list for efficiency
}

// --- Getters implementation ---
// Return private field values without allowing modification (const)

std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }
std::string Persona::getId() const { return id; }
std::string Persona::getCiudadNacimiento() const { return ciudadNacimiento; }
std::string Persona::getFechaNacimiento() const { return fechaNacimiento; }
double Persona::getIngresosAnuales() const { return ingresosAnuales; }
double Persona::getPatrimonio() const { return patrimonio; }
double Persona::getDeudas() const { return deudas; }
bool Persona::getDeclaranteRenta() const { return declaranteRenta; }

int Persona::getEdad() const
{
    // Parse fechaNacimiento "DD/MM/YYYY"
    std::istringstream ss(fechaNacimiento);
    int dia, mes, anio;
    char delim1, delim2;
    ss >> dia >> delim1 >> mes >> delim2 >> anio;
    if (ss.fail() || delim1 != '/' || delim2 != '/')
        return -1; // Error if invalid format

    // Fixed date: 17/08/2025
    const int diaActual = 17, mesActual = 8, anioActual = 2025;
    int edad = anioActual - anio;
    if (mesActual < mes || (mesActual == mes && diaActual < dia))
        edad--; // Adjust for birthday
    return edad;
}

char Persona::getTaxGroup() const
{
    if (id.length() < 2)
        return ' '; // Error if invalid ID
    std::string last2 = id.substr(id.length() - 2);
    int digitos = std::stoi(last2);
    if (digitos <= 39)
        return 'A';
    else if (digitos <= 79)
        return 'B';
    else
        return 'C';
}

// In persona.cpp (added after getTaxGroup)
Persona::Persona()
    : nombre(""), apellido(""), id(""), ciudadNacimiento(""), fechaNacimiento(""),
      ingresosAnuales(0.0), patrimonio(0.0), deudas(0.0), declaranteRenta(false)
{
    // Empty initialization through initializer list
}

// Displays detailed information of the person
void Persona::mostrar() const
{
    std::cout << "-------------------------------------\n";
    // Header with ID and full name
    std::cout << "[" << id << "] Name: " << nombre << " " << apellido << "\n";
    // Personal data
    std::cout << "   - Birth city: " << ciudadNacimiento << "\n";
    std::cout << "   - Birth date: " << fechaNacimiento << "\n\n";

    // Format for monetary values (2 decimals)
    std::cout << std::fixed << std::setprecision(2);

    // Economic data
    std::cout << "   - Annual income: $" << ingresosAnuales << "\n";
    std::cout << "   - Net worth: $" << patrimonio << "\n";
    std::cout << "   - Debts: $" << deudas << "\n";
    // Ternary operator to show Yes/No depending on boolean condition
    std::cout << "   - Tax declarant: " << (declaranteRenta ? "Yes" : "No") << "\n";
}

// Compact version for list display
void Persona::mostrarResumen() const
{
    // ID, full name, city, and income in a single line
    std::cout << "[" << id << "] " << nombre << " " << apellido
              << " | " << ciudadNacimiento
              << " | $" << std::fixed << std::setprecision(2) << ingresosAnuales;
}