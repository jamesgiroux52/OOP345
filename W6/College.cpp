/*************************************************************
// File    College.cpp
// Version 1.0
// Date    March 2, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// College module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <iomanip>
#include "College.h"
#include "Employee.h"
#include "Person.h"

using namespace std;

namespace sdds {

    // add Person pointer to the vector
    College& College::operator+=(Person* thePerson) {
        m_persons.push_back(thePerson);
        return *this;
    }

    // Display tests one and two
    void College::display(std::ostream& os) const {
        os << "------------------------------------------------------------------------------------------------------------------------\n";
        os << "|                                        Test #1 Persons in the college!                                               |\n";
        os << "------------------------------------------------------------------------------------------------------------------------\n";
        for (auto it = m_persons.begin(); it != m_persons.end(); ++it) {
            (*it)->display(os);
            cout << endl;
        }
        os << "------------------------------------------------------------------------------------------------------------------------\n";
        os << "|                                        Test #2 Persons in the college!                                               |\n";
        os << "------------------------------------------------------------------------------------------------------------------------\n";
        for (auto it = m_persons.begin(); it != m_persons.end(); ++it)
            os << "| " << setw(10) << (*it)->status() << "| " << setw(10) << (*it)->id() << "| " << setw(20) << (*it)->name()
            << " | " << setw(3) << (*it)->age() << " |\n";
        os << "------------------------------------------------------------------------------------------------------------------------\n";
    }

    // ensure no memory leaks of m_persons
    College::~College() {
        for (auto it = m_persons.begin(); it != m_persons.end(); ++it) {
            delete *it;
        }
    }
}