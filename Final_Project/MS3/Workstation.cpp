// ***********************************************************
// File    Workstation.cpp
// Version 1.0
// Date    March 29, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Workstation Module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// ***********************************************************

#include <iostream>
#include <deque>
#include "Workstation.h"

using namespace std;

namespace sdds {

    // global double ended queue's to store orders
    deque<CustomerOrder> g_pending{};
    deque<CustomerOrder> g_completed{};
    deque<CustomerOrder> g_incomplete{};

    // pass str to base constructor
    Workstation::Workstation(const std::string& str) : Station(str) {}

    // attempt to fill an item in the order
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty())
            m_orders.front().fillItem(*this, os);
    }

    // move an order along the assembly line or if it is at the last station 
    // add the order to the appropriate global deque
    bool Workstation::attemptToMoveOrder() {
        bool ret{};
        if (!m_orders.empty()) {
            // check if order is filled or there is no more stock to fill
            if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() <= 0) {
                // if there is a next station move the order along the line
                if (m_pNextStation) {
                    *m_pNextStation += std::move(m_orders.front());
                    m_orders.pop_front();
                } else {
                    // if not then add the order to either g_completed or g_incomplete global deque's
                    m_orders.front().isOrderFilled() ?
                        g_completed.push_back(std::move(m_orders.front())) :
                        g_incomplete.push_back(std::move(m_orders.front()));
                    m_orders.pop_front();
                }
                ret = true;
            }
        }
        return ret;
    }

    // set the next station pointer
    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    // return the pointer to the next station
    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    // display stations
    void Workstation::display(std::ostream& os) const {
        if (m_pNextStation)
            os << getItemName() << " --> " << getNextStation()->getItemName() << endl;
        else
            os << getItemName() << " --> End of Line" << endl;
    }

    // move an order to a workstation
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}