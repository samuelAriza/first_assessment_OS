#ifndef PERSONA_H
#define PERSONA_H

/// @struct Person
/// @brief Represents an individual with personal, financial, and tax-related data.
typedef struct {
    char firstName[50];       ///< First name of the person.
    char firstLastName[50];   ///< First surname of the person.
    char secondLastName[50];  ///< Second surname of the person.
    char birthDate[16];       ///< Date of birth in format "DD/MM/YYYY".
    int age;                  ///< Age of the person (derived from birthDate).
    char residence[50];       ///< City or place of residence.
    double heritage;          ///< Total assets and wealth of the person.
    double debts;             ///< Outstanding debts.
    char id[11];              ///< Unique identifier (e.g., numeric string).
    char taxGroup;            ///< Tax group classification ('A', 'B', 'C').
} Person;

/// @brief Creates and initializes a Person object with provided attributes.
/// @param firstName First name.
/// @param firstLastName First surname.
/// @param secondLastName Second surname.
/// @param birthDate Date of birth (format "DD/MM/YYYY").
/// @param residence City or residence place.
/// @param heritage Total assets and wealth.
/// @param debts Outstanding debts.
/// @param id Unique identifier.
/// @return Initialized Person structure.
Person createPerson(const char* firstName,
                    const char* firstLastName,
                    const char* secondLastName,
                    const char* birthDate,
                    const char* residence,
                    double heritage,
                    double debts,
                    const char* id);

/// @brief Displays all relevant information of a Person on stdout.
/// @param p Pointer to a Person object to display.
void show(const Person* p);

#endif
