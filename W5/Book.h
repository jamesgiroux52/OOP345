/*************************************************************
// File    Book.h
// Version 1.0
// Date    February 14, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Book Header
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_BOOK_H_
#define SDDS_BOOK_H_

#include <iostream>
#include <string>
#include <sstream>

namespace sdds {
    class Book {
        std::string m_author{};
        std::string m_title{};
        std::string m_country{};
        size_t m_year{};
        double m_price{};
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
        // finds location of next ch
        static void setPos(std::string::size_type& end, const char* ch, std::string& str){ 
            str.erase(0, end + 1);
            end = str.find(ch);
        }
        // convert string to size_t
        static std::size_t stringToSize_t(std::string str) {
            std::stringstream sstream(str);
            size_t result;
            sstream >> result;
            return result;
        }
    public:
        Book() {};
        Book(const std::string& strBook);
        const std::string& title() const;
        const std::string& country() const;
        const size_t& year() const;
        double& price();
        std::ostream& display(std::ostream& os) const;
        template <typename T>
        void fixSpelling(T& spellChecker);
    };
    std::ostream& operator<<(std::ostream& os, const Book& B);

    template<typename T>
    void Book::fixSpelling(T& spellChecker) {
        spellChecker(m_description);
    }
}

#endif // !SDDS_BOOK_H_
