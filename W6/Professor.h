/*************************************************************
// File    Professor.h
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

#ifndef SDDS_PROFESSOR_H_
#define SDDS_PROFESSOR_H_

#include <iostream>
#include <string>
#include "Employee.h"

namespace sdds {
    // professor class inherits Employee
    class Professor : public Employee {
        std::string m_department{};
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
        Professor(std::istream& is = std::cin);
        void display(std::ostream& os) const;
        std::string status() const;
        std::string department() const;
    };
}

#endif // !SDDS_PROFESSOR_H_


