/*************************************************************
// File    foodorder.h
// Version 1.0
// Date    January 14, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// FoodOrder header with extern variables for tax and discount
// -----------------------------------------------------------
// I have done all the coding by myself and only copied the
// code that my professor provided to complete this workshop.
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_FOODORDER_H_
#define SDDS_FOODORDER_H_

#include <iostream>

namespace sdds {

    class FoodOrder {
        char m_custName[10]{};
        char* m_foodDesc{}; // dynamic
        double m_price{};
        bool m_special{};
        // my cstring functions for length and copy
        static int strlen(const char* str);
        static void strcpy(char* des, const char* src, int len = -1);
        // get a string of an unknown length and 
        // store the result in str dynamically
        static void getString(char*& str, std::istream& is = std::cin);
    public:
        FoodOrder();
        // rule of three for class w/resource
        FoodOrder(const FoodOrder& F);
        FoodOrder& operator=(const FoodOrder& F);
        ~FoodOrder();
        // I/O
        std::istream& read(std::istream& is = std::cin);
        void display() const;
    };
}

// declare external variables
extern double g_taxrate;
extern double g_dailydiscount;

#endif // SDDS_FOODORDER_H_
