/*************************************************************
// File    foodorder.cpp
// Version 1.0
// Date    January 14, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// FoodOrder implementation
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include "foodorder.h"

using namespace std;

// initialize discount and tax rate to be redefined in main()
double g_dailydiscount;
double g_taxrate;

namespace sdds {
    
    int FoodOrder::strlen(const char* str) {
        int len = 0;
        while (str[len])
            len++;
        return len;
    }
    void FoodOrder::strcpy(char* des, const char* src, int len) {
        int i;
        for (i = 0; src[i] && (len < 0 || i < len); ++i)
            des[i] = src[i];
        des[i] = '\0';
    }
    void FoodOrder::getString(char*& str, std::istream& is) {
        string temp;
        getline(is, temp, ',');
        str = new char[temp.length() + 1];
        strcpy(str, temp.c_str());
    }

    // default constructor
    FoodOrder::FoodOrder() {}

    // copy assignment, copy constructor, and destructor for rule of 3
    FoodOrder& FoodOrder::operator=(const FoodOrder& F) {
        if (this != &F) {
            if (m_foodDesc) delete[] m_foodDesc;
            strcpy(m_custName, F.m_custName);
            m_price = F.m_price;
            m_special = F.m_special;
            if (F.m_foodDesc) {
                m_foodDesc = new char[strlen(F.m_foodDesc) + 1];
                strcpy(m_foodDesc, F.m_foodDesc);
            } else m_foodDesc = nullptr;
        }
        return *this;
    }
    FoodOrder::FoodOrder(const FoodOrder& F) {
        *this = F;
    }
    FoodOrder::~FoodOrder() {
        delete[] m_foodDesc;
    }

    // display current object
    void FoodOrder::display() const {
        // count increases each time display is called
        static int count = 0;
        count++;
        // display count - line item
        cout << left << setw(2) << count << ". ";
        // display order if the name is not empty
        if (strlen(m_custName)) {
            cout << setw(10) << m_custName << "|";
            cout << setw(25) << m_foodDesc << "|";
            cout.setf(ios::fixed);
            cout << setprecision(2) << setw(12) << m_price * 
                (g_taxrate + 1) << "|";
            if (m_special)
                cout << right << setw(13) << (m_price * 
                    (g_taxrate + 1)) - g_dailydiscount;
            cout << endl;
        } else cout << "No Order" << endl;
    }

    // read from input stream - in this case a file given in argv[]
    std::istream& FoodOrder::read(std::istream& is) {
        if (is) {
            char special{}; // for bool member
            // read in a single food order
            is.getline(m_custName, 10, ',');
            if (m_foodDesc) delete[] m_foodDesc;
            getString(m_foodDesc, is); // custom - see below
            is >> m_price;
            is.ignore(); // ,
            is >> special;
            if (special == 'Y') m_special = true;
            else m_special = false;
            is.ignore(); // \n
        }
        return is;
    }
}