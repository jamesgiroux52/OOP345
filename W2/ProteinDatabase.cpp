/*************************************************************
// File    ProtienDatabase.cpp
// Version 1.0
// Date    January 22, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// ProtienDatabase implementation
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <fstream>
#include "ProteinDatabase.h"

using namespace std;

namespace sdds {

    ProteinDatabase::ProteinDatabase(const char* str) {
        if (str) {
            char ch{};
            size_t count{ 0 };

            ifstream f(str);
            while(f) {
                f.get(ch);
                if (ch == '>') ++count; // count num of records in file
            }
            // reset stream and go to begining of file
            f.clear();
            f.seekg(0, ios::beg);
            m_sequences = new string[count]; // allocate mem of size 'count'
            // loop file and build sequences
            for (auto i = 0u; i < count; ++i) {
                string temp{}, result{};
                getline(f, temp, '\n'); // ignore description
                getline(f, temp, '\n'); // get first line of sequence
                while (temp.length() == 60) {
                    result.append(temp);
                    getline(f, temp, '\n'); // build sequence
                }
                result.append(temp); // last line not 60 length
                m_sequences[i] = result; // assign built sequence to member string
                ++m_numStrings;
            }
        } else {
            m_sequences = new string[1];
            m_sequences[0] = '\0';
        }
    }

    // copy constructor and assignment operator
    ProteinDatabase::ProteinDatabase(const ProteinDatabase& P) { *this = P; }
    ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& P) {
        if (this != &P) {
            delete[] m_sequences; // clean
            m_numStrings = P.m_numStrings; // shallow
            m_sequences = new string[m_numStrings]; // allocate
            for (auto i = 0u; i < m_numStrings; ++i) { // deep
                m_sequences[i] = P.m_sequences[i];
            }
        }
        return *this;
    }

    // move constructor and move assignment operator
    ProteinDatabase::ProteinDatabase(ProteinDatabase&& P) noexcept { *this = move(P); }
    ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& P) noexcept {
        if (this != &P) {
            delete[] m_sequences; // clean
            m_numStrings = P.m_numStrings; //shallow
            m_sequences = P.m_sequences; // move
            P.m_sequences = nullptr; // free
            P.m_numStrings = 0;
        }
        return *this;
    }

    // destructor
    ProteinDatabase::~ProteinDatabase() { delete[] m_sequences; }

    // size query
    size_t sdds::ProteinDatabase::size() const {
        return m_numStrings;
    }

    // subscript operator returns element at index 'size' if it is 
    // a valid index
    std::string sdds::ProteinDatabase::operator[](size_t size) const {
        string res = "\0";
        if (size < m_numStrings){ 
            res = m_sequences[size];
        }
        return res;
    }
}