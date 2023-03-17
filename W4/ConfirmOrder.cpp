/*************************************************************
// File    ConfirmOrder.cpp
// Version 1.0
// Date    February 7, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// ConfirmOrder implementation file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include "ConfirmOrder.h"
#include "Toy.h"

using namespace std;

namespace sdds {
    ConfirmOrder::ConfirmOrder() {}
    ConfirmOrder::~ConfirmOrder() { delete[] m_toys; }

    // copy and assignment
    ConfirmOrder::ConfirmOrder(const ConfirmOrder& C) {
        *this = C;
    }
    ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& C) {
        if (this != &C) {
            delete[] m_toys;
            m_numToys = C.m_numToys;
            m_toys = new const Toy * [m_numToys];
            for (auto i = 0ul; i < m_numToys; ++i)
                m_toys[i] = C.m_toys[i];
        }
        return *this;
    }

    // move copy and assignment
    ConfirmOrder::ConfirmOrder(ConfirmOrder&& C) noexcept {
        *this = move(C);
    }
    ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& C) noexcept {
        if (this != &C) {
            delete[] m_toys;
            m_numToys = C.m_numToys;
            m_toys = C.m_toys; // here
            // dont do this.. all you need is to copy the address of the pointer to the array
            //for (auto i = 0ul; i < m_numToys; ++i)
            //    m_toys[i] = C.m_toys[i];
            C.m_toys = nullptr;
            C.m_numToys = 0;
        }
        return *this;
    }

    // add toy pointer
    ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy) {
        bool found{};
        size_t spot{ 0 };
        // check if toy is already added
        for (auto i = 0ul; i < m_numToys && !found; ++i) {
            if (m_toys[i] == &toy) found = true;
        }
        if (!found) {
            // check if there is an empty spot
            for (auto i = 0ul; i < m_numToys && !spot; ++i) {
                if (m_toys[i] == nullptr) spot = i;
            }
            if (spot)
                m_toys[spot] = &toy;
            else {
                // resize the array and add the new toy
                const Toy** temp{};
                temp = new const Toy * [m_numToys + 1];
                for (auto i = 0ul; i < m_numToys; ++i)
                    temp[i] = m_toys[i];
                temp[m_numToys++] = &toy;
                delete[] m_toys;
                //m_toys = new const Toy * [m_numToys];
                m_toys = temp;
            }
        }
        return *this;
    }
    // remove a toy pointer from the array
    ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy) {
        for (auto i = 0ul; i < m_numToys; ++i)
            if (m_toys[i] == &toy) m_toys[i] = nullptr;
        return *this;
    }

    // output
    std::ostream& ConfirmOrder::display(std::ostream& os) const {
        os << "--------------------------" << endl;
        os << "Confirmations to Send" << endl;
        os << "--------------------------" << endl;
        if (m_toys != nullptr) {
            for (auto i = 0ul; i < m_numToys && m_toys[i]; ++i)
                os << *m_toys[i];
        } else {
            os << "There are no confirmations to send!" << endl;
        }
        os << "--------------------------" << endl;

        return os;
    }
    std::ostream& operator<<(std::ostream& os, const ConfirmOrder& C) {
        return C.display(os);
    }
}
