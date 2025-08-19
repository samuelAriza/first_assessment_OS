#ifndef PERSONA_H
#define PERSONA_H

#include <string>

/// Class representing a person with personal and fiscal data.
class Persona
{
private:
    /// Basic identification data.
    std::string nombre;           ///< First name.
    std::string apellido;         ///< Last name(s).
    std::string id;               ///< Unique identifier.
    std::string ciudadNacimiento; ///< Birth city (in Colombia).
    std::string fechaNacimiento;  ///< Birthdate in DD/MM/YYYY format.

    /// Fiscal and economic data.
    double ingresosAnuales; ///< Annual income in Colombian pesos.
    double patrimonio;      ///< Total value of assets and property.
    double deudas;          ///< Outstanding debts.
    bool declaranteRenta;   ///< Whether the person is required to declare taxes.

public:
    /// Constructor: Initializes all fields of the person.
    /// @param nom First name.
    /// @param ape Last name(s).
    /// @param id Unique identifier.
    /// @param ciudad Birth city.
    /// @param fecha Birthdate.
    /// @param ingresos Annual income.
    /// @param patri Net worth (assets).
    /// @param deud Outstanding debts.
    /// @param declara Whether the person is required to declare taxes.
    Persona(std::string nom, std::string ape, std::string id,
            std::string ciudad, std::string fecha, double ingresos,
            double patri, double deud, bool declara);

    /// Default constructor: Initializes an empty person object.
    Persona();

    // --- Access methods (getters) ---
    /// Allow access to private fields without exposing implementation.

    /// @return First name.
    std::string getNombre() const;
    /// @return Last name(s).
    std::string getApellido() const;
    /// @return Unique identifier.
    std::string getId() const;
    /// @return Birth city.
    std::string getCiudadNacimiento() const;
    /// @return Birthdate in DD/MM/YYYY format.
    std::string getFechaNacimiento() const;
    /// @return Annual income.
    double getIngresosAnuales() const;
    /// @return Net worth (assets).
    double getPatrimonio() const;
    /// @return Outstanding debts.
    double getDeudas() const;
    /// @return Whether the person is required to declare taxes.
    bool getDeclaranteRenta() const;

    //--------------------------
    /// Calculates age based on birthdate and the reference date 17/08/2025.
    /// @return The calculated age.
    int getEdad() const;

    /// Determines the tax group based on the last two digits of the ID.
    /// 'A' (00-39), 'B' (40-79), 'C' (80-99).
    /// @return Tax group character.
    char getTaxGroup() const;
    //--------------------------

    // --- Display methods ---

    /// Displays all detailed information about the person.
    void mostrar() const;

    /// Displays a compact summary (for listings).
    void mostrarResumen() const;
};

#endif // PERSONA_H