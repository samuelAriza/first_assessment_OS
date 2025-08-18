#include "persona.h"
#include <iostream>
#include <iomanip>  // Para formato de salida (setprecision, fixed)
#include <sstream> // Para parseo de strings

// Implementación del constructor
Persona::Persona(std::string nom, std::string ape, std::string id, 
                 std::string ciudad, std::string fecha, double ingresos, 
                 double patri, double deud, bool declara)
    : nombre(nom), apellido(ape), id(id), ciudadNacimiento(ciudad),
      fechaNacimiento(fecha), ingresosAnuales(ingresos), patrimonio(patri),
      deudas(deud), declaranteRenta(declara) 
{
    // Inicialización mediante lista de inicialización para eficiencia
}

// --- Implementación de getters ---
// Devuelven valores de campos privados sin permitir modificación (const)

std::string Persona::getNombre() const { return nombre; }
std::string Persona::getApellido() const { return apellido; }
std::string Persona::getId() const { return id; }
std::string Persona::getCiudadNacimiento() const { return ciudadNacimiento; }
std::string Persona::getFechaNacimiento() const { return fechaNacimiento; }
double Persona::getIngresosAnuales() const { return ingresosAnuales; }
double Persona::getPatrimonio() const { return patrimonio; }
double Persona::getDeudas() const { return deudas; }
bool Persona::getDeclaranteRenta() const { return declaranteRenta; }

int Persona::getEdad() const {
    // Parsea fechaNacimiento "DD/MM/AAAA"
    std::istringstream ss(fechaNacimiento);
    int dia, mes, anio;
    char delim1, delim2;
    ss >> dia >> delim1 >> mes >> delim2 >> anio;
    if (ss.fail() || delim1 != '/' || delim2 != '/') return -1; // Error si formato inválido

    // Fecha fija: 17/08/2025
    const int diaActual = 17, mesActual = 8, anioActual = 2025;
    int edad = anioActual - anio;
    if (mesActual < mes || (mesActual == mes && diaActual < dia)) edad--; // Ajuste cumpleaños
    return edad;
}

char Persona::getTaxGroup() const {
    if (id.length() < 2) return ' '; // Error si ID inválido
    std::string last2 = id.substr(id.length() - 2);
    int digitos = std::stoi(last2);
    if (digitos <= 39) return 'A';
    else if (digitos <= 79) return 'B';
    else return 'C';
}

// En persona.cpp (agrega después de getTaxGroup)
Persona::Persona() 
    : nombre(""), apellido(""), id(""), ciudadNacimiento(""), fechaNacimiento(""), 
      ingresosAnuales(0.0), patrimonio(0.0), deudas(0.0), declaranteRenta(false) 
{
    // Inicialización vacía mediante lista de inicialización
}


// Muestra información detallada de la persona
void Persona::mostrar() const {
    std::cout << "-------------------------------------\n";
    // Encabezado con ID y nombre completo
    std::cout << "[" << id << "] Nombre: " << nombre << " " << apellido << "\n";
    // Datos personales
    std::cout << "   - Ciudad de nacimiento: " << ciudadNacimiento << "\n";
    std::cout << "   - Fecha de nacimiento: " << fechaNacimiento << "\n\n";
    
    // Formato para valores monetarios (2 decimales)
    std::cout << std::fixed << std::setprecision(2);
    
    // Datos económicos
    std::cout << "   - Ingresos anuales: $" << ingresosAnuales << "\n";
    std::cout << "   - Patrimonio: $" << patrimonio << "\n";
    std::cout << "   - Deudas: $" << deudas << "\n";
    // Operador ternario para mostrar Sí/No según condición booleana
    std::cout << "   - Declarante de renta: " << (declaranteRenta ? "Sí" : "No") << "\n";
}

// Versión compacta para mostrar en listados
void Persona::mostrarResumen() const {
    // ID, nombre completo, ciudad e ingresos en una sola línea
    std::cout << "[" << id << "] " << nombre << " " << apellido
              << " | " << ciudadNacimiento 
              << " | $" << std::fixed << std::setprecision(2) << ingresosAnuales;
}