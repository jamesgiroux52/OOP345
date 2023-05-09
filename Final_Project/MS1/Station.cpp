// ***********************************************************
// File    Station.cpp
// Version 1.0
// Date    March 4, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Station Module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// ***********************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

using namespace std;


namespace sdds {
    size_t Station::m_idGenerator = 0;
    size_t Station::m_fieldWidth = 0;

    Station::Station(const std::string& str) {
        Utilities ut;
        size_t pos{ 0 };
        bool more{};
        m_stationId = ++m_idGenerator;
        m_itemName = ut.extractToken(str, pos, more);
        m_nextSerial = stringToSize_t(ut.extractToken(str, pos, more));
        m_stockCount = stringToSize_t(ut.extractToken(str, pos, more));
        if (ut.getFieldWidth() > m_fieldWidth)
            m_fieldWidth = ut.getFieldWidth();
        m_description = ut.extractToken(str, pos, more); 
    }
    const std::string& Station::getItemName() const {
        return m_itemName;
    }
    size_t Station::getNextSerialNumber() {
        return m_nextSerial++;
    }
    size_t Station::getQuantity() const {
        return m_stockCount;
    }
    void Station::updateQuantity() {
        if (m_stockCount > 0) --m_stockCount;
    }
    void Station::display(std::ostream& os, bool full) const {
        if (full) {
            os << setfill('0') << right << setw(3) << m_stationId << setfill(' ') << " | " << left
                << setw(m_fieldWidth) << m_itemName << " | " << right << setfill('0') << setw(6)
                << m_nextSerial << " | " << setfill(' ') << setw(4) << m_stockCount << " | "
                << m_description << endl;;
        } else {
            os << setfill('0') << right << setw(3) << m_stationId << setfill(' ') << " | " << left
                << setw(m_fieldWidth) << m_itemName << " | " << right << setfill('0') << setw(6)
                << m_nextSerial << " | \n";
        }
        
    }
}