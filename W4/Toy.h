/*************************************************************
// File    Toy.h
// Version 1.0
// Date    February 7, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Toy header file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_TOY_H_
#define SDDS_TOY_H_

#include <iostream>
#include <string>

namespace sdds {

    class Toy {
        int m_orderID{};
        std::string m_name{};
        int m_numOrdered{};
        double m_pricePer{};
        double m_hst{ 0.13 };
        // string functions to deal with whitespace
        static std::string trim(const std::string& str,
            const std::string& whitespace);
        static std::string reduce(const std::string& str,
            const std::string& fill, const std::string& whitespace);
        static void setPos(std::string::size_type& end, 
            const char* ch, std::string& str);
    public:
        Toy();
        void update(int numToys);
        Toy(const std::string& T);
        std::ostream& display(std::ostream& os = std::cout) const;
    };
    std::ostream& operator<<(std::ostream& os, const Toy& T);
}
#endif // !SDDS_TOY_H_
