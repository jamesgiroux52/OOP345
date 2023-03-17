/*************************************************************
// File    Collection.h
// Version 1.0
// Date    February 1, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Set header file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_SET_H_
#define SDDS_SET_H_

#include <cmath>
#include "Collection.h"

namespace sdds {

    // derrived Set class template from Collection
    template <typename T>
    class Set : public Collection<T, 100> {
    public:
        bool add(const T& item);
    };

    // overridden add function from collection
    // to only add new items and not duplicate
    template<typename T>
    bool Set<T>::add(const T& item) {
        bool res{}, found{};
        size_t size = this->size();
        for (auto i = 0ul; i < size && !found; ++i)
            if ((*this)[i] == item) found = true;
        if (!found) {
            Collection<T, 100>::add(item);
            res = true;
        }
        return res;
    }

    // specialization for the double Set
    template<>
    bool Set<double>::add(const double& item) {
        bool res{}, found{};
        size_t size = this->size();
        for (auto i = 0ul; i < size && !found; ++i)
            if (fabs((*this)[i] - item) < 0.01) found = true;
        if (!found) {
            Collection<double, 100>::add(item);
            res = true;
        }
        return res;
    }
}

#endif // !SDDS_SET_H_
