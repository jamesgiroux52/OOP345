// ***********************************************************
// File    CustomerOrder.h
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

#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_

#include <iostream>
#include <string>
#include <sstream>
#include "Station.h"

namespace sdds {
    class CustomerOrder {
        struct Item {
            std::string m_itemName;
            size_t m_serialNumber{ 0 };
            bool m_isFilled{ false };

            Item(const std::string& src) : m_itemName(src) {};
        };
        std::string m_name{};
        std::string m_orderTitle{};
        size_t m_itemCnt{};
        Item** m_itemList{};
        static size_t m_fieldWidth;
        static std::size_t stringToSize_t(std::string str) {
            std::stringstream sstream(str);
            size_t result;
            sstream >> result;
            return result;
        }
    public:
        // constructors
        CustomerOrder() = default;
        CustomerOrder(const std::string str);
        // rule of 5
        CustomerOrder(const CustomerOrder& CO);
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        CustomerOrder(CustomerOrder&& CO) noexcept;
        CustomerOrder& operator=(CustomerOrder&& CO) noexcept;
        ~CustomerOrder();
        // member functions
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& S, std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif // !SDDS_CUSTOMERORDER_H_



