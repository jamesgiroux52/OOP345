// ***********************************************************
// File    Utilities.h
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

#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_

#include <string>

namespace sdds {
    class Utilities {
        size_t m_fieldWidth{ 1 };
        static char m_delimiter;
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
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelim);
        static char getDelimiter();
    };
}

#endif // !SDDS_UTILITIES_H_