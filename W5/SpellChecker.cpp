/*************************************************************
// File    SpellChecker.cpp
// Version 1.0
// Date    February 15, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// SpellChecker implimentation
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "SpellChecker.h"

using namespace std;

namespace sdds {
    // constructor loads words from file into array's
    SpellChecker::SpellChecker(const char* filename) {
        ifstream fs(filename);
        string tempBad{}, tempGood{};
        size_t cnt{};

        if (fs) {
            do {
                getline(fs, tempBad, ' ');
                getline(fs, tempGood, '\n');
                if (fs) {
                    m_badWords[cnt] = trim(tempBad, " "); // dont need trim here but whatever
                    m_goodWords[cnt] = trim(tempGood, " ");
                    ++cnt;
                }
            } while (fs);
            fs.close();
        } else {
            // throw error if file not found
            throw "Bad file name!";
        }
    }
    // operator() verload for functor
    // finds and replaces bad words in 'text'
    void SpellChecker::operator()(std::string& text) {
        size_t pos{ 0 };
        for (int i = 0; i < 6; ++i) {
            pos = text.find(m_badWords[i]);
            while (pos != string::npos) {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                ++m_replaceCount[i]; // array to keep track of # of replacements
                pos = text.find(m_badWords[i], pos + m_badWords[i].length());
            }
            pos = 0;
        }
    }
    // show stats using the counter array
    void SpellChecker::showStatistics(std::ostream& os) const {
        os << "Spellchecker Statistics\n";
        for (int i = 0; i < 6; ++i) {
            os << right << setw(15) << m_badWords[i] << ": "
                << m_replaceCount[i] << " replacements\n";
        }
    }
}