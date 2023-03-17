/*************************************************************
// File    Professor.cpp
// Version 1.0
// Date    March 7, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Professor module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <string>
#include "Professor.h"
#include "Employee.h"

using namespace std;

namespace sdds {

    // build a professor using the employee constructor
    Professor::Professor(std::istream& is) : Employee(is){
        string dept{};
        getline(is, dept, '\n');
        m_department = trim(dept, " ");
    }
    // display professor using the display from Employee and adding the department
    void Professor::display(std::ostream& os) const {
        Employee::display(os); 
        os << m_department << "| Professor";
    }

    // queries
    std::string Professor::status() const {
        return "Professor";
    }
    std::string Professor::department() const {
        return m_department;
    }
}
