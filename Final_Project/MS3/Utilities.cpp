// ***********************************************************
// File    Utilities.cpp
// Version 1.0
// Date    March 4, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Utilities Module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// ***********************************************************

#include <string>
#include "Utilities.h"

using namespace std;

namespace sdds {

    char Utilities::m_delimiter{};

    void Utilities::setFieldWidth(size_t newWidth) {
        m_fieldWidth = newWidth;
    }
    size_t Utilities::getFieldWidth() const {
        return m_fieldWidth;
    }
    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string ret{};
        char ch = str[next_pos];
        // check if delimiter is at 'next_pos'
        if (ch == m_delimiter) {
            more = false;
            throw "Error";
        }
        // build 'ret' until a delimiter or the end of 'str' is found
        while (ch != m_delimiter && ch != '\0') {
            ret += ch;
            ch = str[++next_pos];
        }
        // update width for output
        if (m_fieldWidth < ret.length())
            m_fieldWidth = ret.length();
        // if we reached the end of the 'str' change 'more' so
        // the client wont try to extract again
        if (ch == '\0')
            more = false;
        else
            ++next_pos; // skip delimiter

        return trim(ret, " ");
    }
    void Utilities::setDelimiter(char newDelim) {
        m_delimiter = newDelim;
    }
    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}