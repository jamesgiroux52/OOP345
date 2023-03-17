/*************************************************************
// File    Child.h
// Version 1.0
// Date    February 7, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Child header file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_CHILD_H_
#define SDDS_CHILD_H_

#include <iostream>
#include <string>
#include "Toy.h"

namespace sdds {

    class Child {
        std::string m_name{};
        int m_age{};
        const Toy** m_toys{};
        size_t m_numToys{};
    public:
        // constructors
        Child() {}
        Child(std::string name, int age, const Toy* toys[], size_t count);
        // rule of 5
        Child(const Child& C);
        Child& operator=(const Child& C);
        Child(Child&& C) noexcept;
        Child& operator=(Child&& C) noexcept;
        ~Child();
        // size query
        size_t size() const;
        // output
        std::ostream& display(std::ostream& os = std::cout) const;
    };
    std::ostream& operator<<(std::ostream& os, const Child& C);
}
#endif // !SDDS_CHILD_H_
