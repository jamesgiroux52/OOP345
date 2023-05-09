// ***********************************************************
// File    Workstation.h
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

#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_

#include <iostream>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {

    // global variables accessable from other transation units that include Workstation.h
    // orders be placed into assembly line at first station
    extern std::deque<sdds::CustomerOrder> g_pending;
    // orders that have been removed from the last station completely filled
    extern std::deque<sdds::CustomerOrder> g_completed;
    // orders that have been removed from the last station NOT completely filled
    extern std::deque<sdds::CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{};
    public:
        // one arg constructor
        Workstation(const std::string& str);
        void fill(std::ostream& os);
        bool attemptToMoveOrder(); // to next station
        void setNextStation(Workstation* station = nullptr);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
        // no copy or move operations allowed
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;
    };
}

#endif // !SDDS_WORKSTATION_H_