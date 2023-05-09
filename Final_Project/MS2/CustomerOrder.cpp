// ***********************************************************
// File    CustomerOrder.cpp
// Version 1.0
// Date    March 17, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// CustomerOrder Module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// ***********************************************************

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "CustomerOrder.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
    size_t CustomerOrder::m_fieldWidth{};

    // custom constructor
    CustomerOrder::CustomerOrder(const std::string str) {
        Utilities ut;
        size_t pos{ 0 };
        bool more{ true };
        vector<string> items{};
        m_name = ut.extractToken(str, pos, more);
        m_orderTitle = ut.extractToken(str, pos, more);
        while (more) {
            ++m_itemCnt;
            string item = ut.extractToken(str, pos, more);
            items.push_back(item);
        }
        // assign memory and load data from vector into m_itemList
        m_itemList = new Item * [m_itemCnt];
        for (auto i = 0u; i < m_itemCnt; ++i)
            m_itemList[i] = new Item(items[i]);
        // update field width if needed
        if (ut.getFieldWidth() > m_fieldWidth)
            m_fieldWidth = ut.getFieldWidth();

    }
    // throw exception if copy called
    CustomerOrder::CustomerOrder(const CustomerOrder& CO) {
        throw "Bad copy";
    }

    // move operations
    CustomerOrder::CustomerOrder(CustomerOrder&& CO) noexcept {
        *this = move(CO);
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& CO) noexcept {
        if (this != &CO) {
            // clean-up
            for (auto i = 0u; i < m_itemCnt; ++i)
                delete m_itemList[i];
            delete[] m_itemList;
            // shallow
            m_name = CO.m_name; 
            m_orderTitle = CO.m_orderTitle;
            m_itemCnt = CO.m_itemCnt;
            // move
            m_itemList = CO.m_itemList; 
            // clean CO
            CO.m_itemList = nullptr;
            CO.m_name.clear();
            CO.m_orderTitle.clear();
            CO.m_itemCnt = 0;
        }
        return *this;
    }

    // clean up memory
    CustomerOrder::~CustomerOrder() {
        for (auto i = 0u; i < m_itemCnt; ++i)
            delete m_itemList[i];
        delete[] m_itemList;
    }
    // check if whole order is filled
    bool CustomerOrder::isOrderFilled() const {
        bool ret{};
        size_t cnt{};
        for (auto i = 0u; i < m_itemCnt; ++i)
            if (m_itemList[i]->m_isFilled) 
                ++cnt;

        if (cnt == m_itemCnt) ret = true;

        return ret;
    }
    // check if an item is filled
    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        bool ret{};
        int cntItems{}, cntFilled{};

        // loop through item list 
        for (auto i = 0u; i < m_itemCnt; ++i) {
            if (m_itemList[i]->m_itemName == itemName) {
                ++cntItems; 
                if (m_itemList[i]->m_isFilled)
                    ++cntFilled;
            }
        }

        // if nothing was found
        if (cntItems == 0 || cntFilled == cntItems) ret = true;
        
        return ret;
    }
    // fill a single item
    void CustomerOrder::fillItem(Station& S, std::ostream& os) {
        bool filled{};
        for (auto i = 0u; i < m_itemCnt && !filled; ++i) {
            if (m_itemList[i]->m_itemName == S.getItemName()) {
                if (S.getQuantity() > 1) {
                    S.updateQuantity();
                    m_itemList[i]->m_isFilled = true;
                    m_itemList[i]->m_serialNumber = S.getNextSerialNumber();
                    os << "    Filled " << m_name << ", " << m_orderTitle << " ["
                        << m_itemList[i]->m_itemName << "]\n";
                    filled = true;
                } else {
                    os << "Unable to fill" << m_name << ", " << m_orderTitle << " ["
                        << m_itemList[i]->m_itemName << "]\n";
                }
            }
        }
    }
    // output order
    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_orderTitle << endl;
        for (auto i = 0u; i < m_itemCnt; ++i) {
            os << "[" << setfill('0') << setw(6) << m_itemList[i]->m_serialNumber << "] "
                << setfill(' ') << left << setw(m_fieldWidth) << m_itemList[i]->m_itemName << " - ";
            if (m_itemList[i]->m_isFilled) os << "FILLED" << endl;
            else os << "TO BE FILLED" << endl;
            os << right;
        }
    }
}