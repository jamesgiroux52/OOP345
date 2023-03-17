/*************************************************************
// File    Pair.h
// Version 1.0
// Date    January 31, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Pair header file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_PAIR_H_
#define SDDS_PAIR_H_

#include <string>

namespace sdds {

    class Pair {
        std::string m_key{};
        std::string m_value{};
    public:
        const std::string& getKey() { return m_key; }
        const std::string& getValue() { return m_value; }
        Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value } {};

        // TODO: Add here the missing prototypes for the members
        //           that are necessary if this class is to be used
        //           with the template classes described below.
        //        Implement them in the Pair.cpp file.
        Pair(); 
        bool operator==(const Pair& P);
        std::ostream& display(std::ostream& os) const;
    };
    // I/O helper for display
    std::ostream& operator<<(std::ostream& os, const Pair& P);
}

#endif // !SDDS_PAIR_H
