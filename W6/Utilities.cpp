/*************************************************************
// File    Utilities.cpp
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

#include "Employee.h"
#include "Student.h"
#include "Professor.h"
#include "Utilities.h"
#include "Person.h"

namespace sdds {
    
    // builds an instance of a person depending on the KEY from input file
    Person* buildInstance(std::istream& in) {
        char ch{};
        Person* p{};
        in >> ch;
        in.ignore(); 
        if (ch == 'e' || ch == 'E')
            p = new Employee(in);
        else if (ch == 's' || ch == 'S')
            p = new Student(in);
        else if (ch == 'p' || ch == 'P')
            p = new Professor(in);        
        return p;
    }
}