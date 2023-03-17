/*************************************************************
// File    Movie.cpp
// Version 1.0
// Date    February 14, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Movie implimentation
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include "Movie.h"

using namespace std;

namespace sdds {
    // Constructor - one arg
    Movie::Movie(const std::string& strMovie) {
        string temp = strMovie;
        // store values
        string::size_type end = temp.find(",");
        m_title = trim(temp.substr(0, end), " ");
        setPos(end, ",", temp);
        m_year = stringToSize_t(trim(temp.substr(0, end), " "));
        setPos(end, ".", temp);
        m_description = trim(temp.substr(0, end + 1), " ");
    }
    // title query
    const std::string& Movie::title() const {
        return m_title;
    }
    // output
    std::ostream& Movie::display(std::ostream& os) const {
        os << setw(40) << m_title << " | " << setw(4) << m_year
            << " | " << m_description << endl;
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const Movie& M) {
        return M.display(os);
    }
}
