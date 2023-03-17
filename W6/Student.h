/*************************************************************
// File    Student.h
// Version 1.0
// Date    March 9, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Student module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_STUDENT_H_
#define SDDS_STUDENT_H_

#include <iostream>
#include <string>
#include "Person.h"

namespace sdds {
    class Student : public Person {
        std::string m_name{};
        std::string m_age{};
        std::string m_id{};
        std::string* m_courses{};
        int m_numCourses{};
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
        // deleted copy/move operations
        Student(const Student& S) = delete;
        Student& operator=(const Student& S) = delete;
        Student(Student&& S) = delete;
        Student& operator=(Student&& S) = delete;

        Student(std::istream& is = std::cin);
        std::string status() const;
        std::string name() const;
        std::string age() const;
        std::string id() const;
        void display(std::ostream& os) const;
        ~Student();
    };
}

#endif // !SDDS_STUDENT_H_
