/*************************************************************
// File    Toy.cpp
// Version 1.0
// Date    February 7, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Toy implementation file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include "Toy.h"

using namespace std;

namespace sdds {

    // I built these functions while working on OOP244 project
    // They werent needed for the final submission, but I wanted to
    // accept input with spaces and only store one space between words
    // and also remove any leading or trailing whitespace
    // eg. "  ASDF   123   " will become "ASDF 123"
    std::string Toy::trim(const std::string& str, 
            const std::string& whitespace) {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return ""; // no content
        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;
        return str.substr(strBegin, strRange);
    }
    std::string Toy::reduce(const std::string& str, 
            const std::string& fill, const std::string& whitespace) {
        // trim first
        auto result = trim(str, whitespace);
        // replace sub ranges
        auto beginSpace = result.find_first_of(whitespace);
        while (beginSpace != std::string::npos) {
            const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
            const auto range = endSpace - beginSpace;
            result.replace(beginSpace, range, fill);
            const auto newStart = beginSpace + fill.length();
            beginSpace = result.find_first_of(whitespace, newStart);
        }
        return result;
    }
    
    // find next delimiter (ch) and delete data already collected
    void Toy::setPos(std::string::size_type& end, 
            const char* ch, string& str) {
        str.erase(0, end + 1);
        end = str.find(ch);
    }

    // default constructor
    Toy::Toy() {}
    
    // update number of toys in order
    void Toy::update(int numToys) {
        m_numOrdered = numToys;
    }

    // save order from string parameter removing any spaces
    Toy::Toy(const std::string& T) {
        // first remove most whitespaces from string
        string temp = reduce(T, " ", " ");
        // store values
        string::size_type end = temp.find(":");
        m_orderID = stoi(temp.substr(0, end));
        setPos(end, ":", temp);
        m_name = trim(temp.substr(0, end), " ");
        setPos(end, ":", temp);
        m_numOrdered = stoi(temp.substr(0, end));
        setPos(end, "\0", temp);
        m_pricePer = stof(temp.substr(0, end - 1));
    }

    // I/O
    std::ostream& Toy::display(std::ostream& os) const {
        os.setf(ios::fixed);
        os << setprecision(2);
        os << "Toy" << setw(8) << m_orderID << ":" << right << setw(18)
            << m_name << setw(3) << m_numOrdered << " items" << setw(8)
            << m_pricePer << "/item  subtotal:" << setw(7)
            << m_numOrdered * m_pricePer << " tax:" << setw(6)
            << m_numOrdered * m_pricePer * m_hst << " total:"
            << setw(7) << m_numOrdered * m_pricePer * (m_hst + 1) << endl;
        os.unsetf(ios::fixed);
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const Toy& T) {
        return T.display(os);
    }
}