/*************************************************************
// File    Collection.h
// Version 1.0
// Date    January 31, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Collection header file
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_COLLECTION_H_
#define SDDS_COLLECTION_H_

#include <iostream>
#include <iomanip>
#include "Pair.h"

namespace sdds {

    // Collection class template
    template <typename T, size_t CAPACITY>
    class Collection {
        T m_data[CAPACITY]{};
        static T m_dummy; // class variable
        size_t m_count{};
    public:
        Collection();
        // virtual bc its a base class
        virtual ~Collection(); 
        size_t size() const;
        std::ostream& display(std::ostream& os = std::cout) const;
        // overridden in Set
        virtual bool add(const T& item); 
        T operator[](const int index) const;
    };

    // declare class variable
    template <typename T, size_t CAPACITY>
    T Collection<T, CAPACITY>::m_dummy{};

    // specialize m_dummy using 2-arg constructor for Pair
    template <>
    Pair Collection<Pair, 100>::m_dummy("No Key", "No Value");

    // default empty constructor
    template <typename T, size_t CAPACITY>
    Collection<T, CAPACITY>::Collection() {}

    // empty destructor
    template <typename T, size_t CAPACITY>
    Collection<T, CAPACITY>::~Collection() {}

    // return number of records in collection
    template <typename T, size_t CAPACITY>
    size_t Collection<T, CAPACITY>::size() const { return m_count; }

    // display collection
    template <typename T, size_t CAPACITY>
    std::ostream& Collection<T, CAPACITY>::display(std::ostream& os) const {
        os << "----------------------" << std::endl;
        os << "| Collection Content |" << std::endl;
        os << "----------------------" << std::endl;
        for (auto i = 0ul; i < m_count; ++i) 
            os << m_data[i] << std::endl;
        os << "----------------------" << std::endl;
        return os;
    }

    // add an item to the collection
    template <typename T, size_t CAPACITY>
    bool Collection<T, CAPACITY>::add(const T& item) {
        bool res{};
        if (m_count < CAPACITY - 1) {
            m_data[m_count++] = item;
            res = true;
        }
        return res;
    }

    // [] overload returns a record in the collection at 'index'
    // or dummy object if its an invalid index
    template <typename T, size_t CAPACITY>
    T Collection<T, CAPACITY>::operator[](const int index) const {
        T res{};
        if (index < (int)m_count) res = m_data[index];
        else res = m_dummy;
        return res;
    }
}

#endif // !SDDS_COLLECTION_H_