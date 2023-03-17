/*************************************************************
// File    Utilities.h
// Version 1.0
// Date    March 2, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Utilities module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_

#include <iostream>
#include "Person.h"

namespace sdds {
    Person* buildInstance(std::istream& in);
}

#endif // !SDDS_UTILITIES_H_

