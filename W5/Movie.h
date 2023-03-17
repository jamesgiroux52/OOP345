/*************************************************************
// File    Movie.h
// Version 1.0
// Date    February 14, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Movie Header
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_MOVIE_H_
#define SDDS_MOVIE_H_

#include <iostream>
#include <string>
#include <sstream>

namespace sdds {

    class Movie {
        std::string m_title{};
        size_t m_year{};
        std::string m_description{};
        static std::string trim(const std::string& str,
            const std::string& whitespace) {
            const auto strBegin = str.find_first_not_of(whitespace);
            if (strBegin == std::string::npos)
                return ""; // no content
            const auto strEnd = str.find_last_not_of(whitespace);
            const auto strRange = strEnd - strBegin + 1;
            return str.substr(strBegin, strRange);
        }
        static void setPos(std::string::size_type& end, const char* ch, std::string& str) {
            str.erase(0, end + 1);
            end = str.find(ch);
        }
        static std::size_t stringToSize_t(std::string str) {
            std::stringstream sstream(str);
            size_t result;
            sstream >> result;
            return result;
        }
    public:
        Movie() {};
        Movie(const std::string& strMovie);
        const std::string& title() const;
        template <typename T>
        void fixSpelling(T& spellchecker);
        std::ostream& display(std::ostream& os) const;
    };
    std::ostream& operator<<(std::ostream& os, const Movie& M);

    template<typename T>
    void Movie::fixSpelling(T& spellChecker) {
        spellChecker(m_title);
        spellChecker(m_description);
    }
}

#endif // !SDDS_MOVIE_H_