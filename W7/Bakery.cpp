/*************************************************************
// File    Bakery.cpp
// Version 1.0
// Date    March 13, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Bakery module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <algorithm>
#include <numeric>
#include "Bakery.h"

using namespace std;

namespace sdds {

    // Bakery custom constructor
    Bakery::Bakery(const char* file) {
        ifstream fs(file);
        if (fs) {
            string str{};
            getline(fs, str, '\n');
            while (fs) {
                BakedGood bg;
                // build local 'bg'
                if (str[0] == 'B') bg.m_type = BakedType::BREAD;
                else bg.m_type = BakedType::PASTERY;
                str.erase(0, 8);
                bg.m_desc = trim(str.substr(0, 20), " ");
                str.erase(0, 20);
                bg.m_shelfLife = stringToSize_t(str.substr(0, 14));
                str.erase(0, 14);
                bg.m_stockCount = stringToSize_t(str.substr(0, 8));
                str.erase(0, 8);
                bg.m_itemPrice = stod(str.substr(0, 6));
                // populate vector m_bakedGoods
                m_bakedGoods.push_back(bg);
                // get next record
                getline(fs, str, '\n');
            }
            fs.close();
        } else {
            cout << "Filename not found in command line!\n";
        }
    }

    // display goods in Bakery
    void Bakery::showGoods(std::ostream& os) const {
        // print lambda for for_each - uses insertion overload to display
        auto print = [&os](const BakedGood& B) { os << B << endl; };
        // display collection
        std::for_each(m_bakedGoods.begin(), m_bakedGoods.end(), print);

        // accumulate stock
        auto stock = [](size_t cnt, const BakedGood& B) {return cnt 
            + B.m_stockCount; };
        size_t totalStock = std::accumulate(m_bakedGoods.begin(), 
            m_bakedGoods.end(), (size_t)0, stock);
        // accumulate value
        auto value = [](double value, const BakedGood& B) {
            return value + B.m_itemPrice; };
        double totalValue = std::accumulate(m_bakedGoods.begin(), 
            m_bakedGoods.end(), 0.0, value);
        
        // totals
        os << "Total Stock: " << totalStock << endl;
        os.setf(ios::fixed);
        os << "Total Price: " << setprecision(2) << totalValue << endl;
        os.unsetf(ios::fixed);
    }

    // sort collection based on parameter
    void Bakery::sortBakery(const std::string str) {
        // sort based on 'str'
        if (str == "Description") {
            auto desc = [](const BakedGood& A, const BakedGood& B) { 
                return A.m_desc < B.m_desc; 
            };
            std::sort(m_bakedGoods.begin(), m_bakedGoods.end(), desc);
        } else if (str == "Shelf") {
            auto shelfLife = [](const BakedGood& A, const BakedGood& B) { 
                return A.m_shelfLife < B.m_shelfLife; 
            };
            std::sort(m_bakedGoods.begin(), m_bakedGoods.end(), shelfLife);
        } else if (str == "Stock") {
            auto stockCount = [](const BakedGood& A, const BakedGood& B) { 
                return A.m_stockCount < B.m_stockCount; 
            };
            std::sort(m_bakedGoods.begin(), m_bakedGoods.end(), stockCount);
        } else if (str == "Price") {
            auto price = [](const BakedGood& A, const BakedGood& B) { 
                return A.m_itemPrice < B.m_itemPrice; 
            };
            std::sort(m_bakedGoods.begin(), m_bakedGoods.end(), price);
        }
    }

    // combine current object and parameter
    std::vector<BakedGood> Bakery::combine(Bakery& B) {
        // temp vector
        std::vector<BakedGood> combined(m_bakedGoods.size() + B.m_bakedGoods.size());
        
        // sort by price - merge needs a sorted collection
        sortBakery("Price"); // Run-Time crash -- "sequence not ordered"
        
        // merge vectors
        auto price = [](const BakedGood& A, const BakedGood& B) { 
            return A.m_itemPrice < B.m_itemPrice; };
        std::merge(m_bakedGoods.begin(), m_bakedGoods.end(), B.m_bakedGoods.begin(),
            B.m_bakedGoods.end(), combined.begin(), price);

        // send back combined vectors
        return combined; 
    }

    // find stock item if it is in stock
    bool Bakery::inStock(const char* desc, const BakedType& type) const {
        
        auto found = [&](const BakedGood& B){ 
            return (B.m_desc == desc && B.m_type == type && B.m_stockCount > 0);
        };
        auto res = std::any_of(m_bakedGoods.begin(), m_bakedGoods.end(), found);

        return res;
    }

    std::list<BakedGood> Bakery::outOfStock(const BakedType& type) const {

        // lambda for count_if and copy_if
        auto found = [&](const BakedGood& B) {
            return (B.m_type == type && B.m_stockCount == 0);
        };
        // used calculate size of list to return
        auto count = std::count_if(m_bakedGoods.begin(), m_bakedGoods.end(), found);

        // create and populate list of out of stock items
        std::list<BakedGood> temp(count);

        // copy out of stock items into the new list using the same lambda for calculating the size
        std::copy_if(m_bakedGoods.begin(), m_bakedGoods.end(), temp.begin(), found);

        return temp;
    }

    // insertion free helper for output
    std::ostream& operator<<(std::ostream& os, const BakedGood& B) {
        os << left;
        os << "* " << setw(10) << (B.m_type == BakedType::BREAD ? "Bread" : "Pastry");
        os << " * " << setw(20) << B.m_desc << " * " << setw(5) << B.m_shelfLife
            << " * " << setw(5) << B.m_stockCount << " * ";
        os.setf(ios::fixed);
        os << setprecision(2) << right << setw(8) << B.m_itemPrice << " * ";
        os.unsetf(ios::fixed);
        return os;
    }
}