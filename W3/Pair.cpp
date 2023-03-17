/*************************************************************
// File    Pair.cpp
// Version 1.0
// Date    January 31, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Pair implementation file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <iomanip>
#include "Pair.h"

using namespace std;

namespace sdds {

    // default constructor
    Pair::Pair() {}

    // used to eliminate duplicates in Set
    bool Pair::operator==(const Pair& P) {
        return this->getKey() == P.m_key;
    }

    // display key and value
    std::ostream& Pair::display(std::ostream& os) const {
        os << right << setw(20) << m_key << ": " << left << m_value;
        return os;
    }

    // insertion helper for display
    std::ostream& operator<<(std::ostream& os, const Pair& P) {
        return P.display(os);
    }
}