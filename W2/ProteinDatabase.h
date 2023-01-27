/*************************************************************
// File    ProtienDatabase.h
// Version 1.0
// Date    January 22, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// ProtienDatabase header file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_PROTEINDATABASE_H_
#define SDDS_PROTEINDATABASE_H_

#include <string>

namespace sdds {
    class ProteinDatabase {
        std::string* m_sequences{};
        size_t m_numStrings{};
    public:
        // default / one arg constructor
        ProteinDatabase(const char* str = nullptr);
        // rule of 5 for classes with a resource
        ProteinDatabase(const ProteinDatabase& P);
        ProteinDatabase& operator=(const ProteinDatabase& P);
        ProteinDatabase(ProteinDatabase&& P) noexcept;
        ProteinDatabase& operator=(ProteinDatabase&& P )noexcept;
        ~ProteinDatabase();
        // size query - number of strings stored
        size_t size() const;
        // subscript operator - return index at 'size'
        std::string operator[](size_t size) const;
    };
}
#endif // !SDDS_PROTEINDATABASE_H_