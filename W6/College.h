/*************************************************************
// File    College.h
// Version 1.0
// Date    March 2, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// College module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_COLLEGE_H_
#define SDDS_COLLEGE_H_

#include <iostream>
#include <vector>
#include <list>
#include "Person.h"

namespace sdds {

    class College {
        // persons vector
        std::vector<Person*> m_persons{};
    public:
        // deleted copy operations
        College() = default;
        College(const College&) = delete;
        College& operator=(const College&) = delete;
        College(College&&) = delete;
        // operator overloads
        College& operator=(College&&) = delete;
        College& operator+=(Person* thePerson);
        void display(std::ostream& os) const;
        virtual ~College();
        
        // select template function
        template <typename T>
        void select(const T& test, std::list<const Person*>& persons);
    };
    // select certian persons based on test condition and add them to the list
    template<typename T>
    void College::select(const T& test, std::list<const Person*>& persons) {
        for (auto it = m_persons.begin(); it != m_persons.end(); ++it) 
            if (test(*it))
                persons.push_back(*it);
    }
}


#endif // !SDDS_COLLEGE_H_

