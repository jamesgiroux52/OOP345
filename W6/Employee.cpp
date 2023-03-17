/*************************************************************
// File    Employee.cpp
// Version 1.0
// Date    March 2, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Employee Module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include "Employee.h"

using namespace std;

namespace sdds {

    // Employee constructor - alsu used by professor constructor
    Employee::Employee(std::istream& is) {
        string str{}, str2{};
        getline(is, str, ',');
        m_name = trim(str, " ");
        getline(is, str, ',');
        m_age = trim(str, " ");
        char ch{};
        is.get(ch);
        do {
            str2 += ch;
            is.get(ch);
        } while (ch != '\n' && ch != ',');
        m_id = trim(str2, " ");
        if (m_id[0] != 'E')
            throw(m_name + "++Invalid record!");
    }

    // queries
    std::string Employee::status() const {
        return std::string("Employee");
    }
    std::string Employee::name() const {
        return m_name;
    }
    std::string Employee::id() const {
        return m_id;
    }
    std::string Employee::age() const {
        return m_age;
    }

    // display
    void Employee::display(std::ostream& os) const{
        os << "| " << left << setw(10) << "Employee" << "| " 
            << setw(10) << m_id << "| " << setw(20) << m_name 
            << " | " << setw(3) << m_age << " |";
    }
}