/*************************************************************
// File    Book.cpp
// Version 1.0
// Date    February 14, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Book Implimentation
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <iomanip>
#include "Book.h"

using namespace std;

namespace sdds {
    // one arg constructor
    Book::Book(const std::string& strBook) {
        string temp = strBook;
        // store values
        string::size_type end = temp.find(",");
        m_author = temp.substr(0, end);
        setPos(end, ",", temp);
        m_title = trim(temp.substr(0, end), " ");
        setPos(end, ",", temp);
        m_country = trim(temp.substr(0, end), " ");
        setPos(end, ",", temp);
        m_price = stod(trim(temp.substr(0, end), " "));
        setPos(end, ",", temp);
        m_year = stringToSize_t(trim(temp.substr(0, end), " "));
        setPos(end, ".", temp);
        m_description = trim(temp.substr(0, end + 1), " ");
    }

    // querries
    const std::string& Book::title() const {
        return m_title;
    }
    const std::string& Book::country() const {
        return m_country;
    }
    const size_t& Book::year() const {
        return m_year;
    }
    // so client can manipulate price
    double& Book::price() {
        return m_price;
    }
    
    // output
    std::ostream& Book::display(std::ostream& os) const{
        os << setw(20) << m_author << " | " << setw(22) << m_title << " | "
            << setw(5) << m_country << " | " << setw(4) << m_year << " | ";
        os.setf(ios::fixed);
        os << setprecision(2) << setw(6) << m_price << " | ";
        os.unsetf(ios::fixed);
        os << m_description << endl;
        return os;
    }
    std::ostream& operator<<(std::ostream& os, const Book& B) {
        return B.display(os);
    }
}