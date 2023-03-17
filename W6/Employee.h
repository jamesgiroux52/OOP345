/*************************************************************
// File    Employee.h
// Version 1.0
// Date    March 2, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Employee header
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_EMPLOYEE_H_
#define SDDS_EMPLOYEE_H_

#include <iostream>
#include "Person.h"

namespace sdds {

    // Employee class inherits person
    class Employee : public Person {
        std::string m_name{};
        std::string m_age{};
        std::string m_id{};
        // trim 'whitespace' from begining and end of 'str'
        static std::string trim(const std::string& str,
                const std::string& whitespace) {
            const auto strBegin = str.find_first_not_of(whitespace);
            if (strBegin == std::string::npos)
                return ""; // no content
            const auto strEnd = str.find_last_not_of(whitespace);
            const auto strRange = strEnd - strBegin + 1;
            return str.substr(strBegin, strRange);
        }
    public:
        Employee(std::istream& is = std::cin);
        std::string status() const;
        std::string name() const;
        std::string id() const;
        std::string age() const;
        void display(std::ostream& os) const;
    };
}

#endif // !SDDS_EMPLOYEE_H_
