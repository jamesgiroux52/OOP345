/*************************************************************
// File    Collection.h
// Version 1.0
// Date    February 22, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Collection template header
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// -----------------------------------------------------------
*************************************************************/

#ifndef SDDS_COLLECTION_H_
#define SDDS_COLLECTION_H_

#include <iostream>
#include <string>
#include <stdexcept>

namespace sdds {

    // templates collection class
    template <typename T>
    class Collection {
        std::string m_name{};
        T* m_data{};
        size_t m_size{};
        void (*m_observer)(const Collection<T>& C, const T& t) {};
    public:
        Collection(const std::string& name);
        Collection(const Collection<T>& C) = delete;
        Collection<T>& operator=(const Collection<T>& C) = delete;
        Collection(Collection<T>&& C) = delete;
        Collection<T>& operator=(Collection<T>&& C) = delete;

        const std::string& name() const;
        size_t size()const;
        void setObserver(void (*observer)(const Collection<T>&, const T&));
        Collection<T>& operator+=(const T& item);
        T& operator[](size_t index);
        T* operator[](const std::string& name) const;
        ~Collection();
        std::ostream& display(std::ostream& os) const;
    };

    // output
    template<typename T>
    std::ostream& Collection<T>::display(std::ostream& os) const {
        for (auto i = 0ul; i < m_size; ++i)
            os << m_data[i];
        return os;
    }
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& C) {
        return C.display(os);
    }

    // set name of collection
    template <typename T>
    Collection<T>::Collection(const std::string& name) {
        m_name = name;
    }

    // data queries
    template<typename T>
    const std::string& Collection<T>::name() const {
        return m_name;
    }
    template <typename T>
    size_t Collection<T>::size()const {
        return m_size;
    }

    // copy the address of the observer
    template<typename T>
    void Collection<T>::setObserver(void(*observer)(const Collection<T>&, const T&)) {
        m_observer = observer;
    }

    // troe an error if index is out of bounds or return element at 'index'
    template <typename T>
    T& Collection<T>::operator[](size_t index) {
        if (index >= m_size) {
            std::string err = "Bad index [" + std::to_string(index) + 
                "]. Collection has [" + std::to_string(m_size) + "] items.";
            throw std::out_of_range(err);
        } else return m_data[index];
    }

    // find and return address of an item
    template <typename T>
    T* Collection<T>::operator[](const std::string& name) const {
        for (size_t i = 0; i < m_size; ++i)
            if (m_data[i].title() == name)
                return &m_data[i];
        
        return nullptr;
    }

    // add items to collection if they arent already added
    template <typename T>
    Collection<T>& Collection<T>::operator+=(const T& item) {
        bool found{};
        for (size_t i = 0; i < m_size && !found; ++i)
            if (m_data[i].title() == item.title()) found = true;
        
        // if item is not already added the resize array and add item
        if (!found) {
            T* temp{};
            temp = new T[m_size + 1];
            for (size_t i = 0; i < m_size; ++i)
                temp[i] = m_data[i];
            delete[] m_data;
            m_data = temp;
            m_data[m_size++] = item;
            if (m_observer)
                m_observer(*this, item);
        }
        return *this;
    }
    // destructor cleanup
    template <typename T>
    Collection<T>::~Collection() {
        delete[] m_data;
    }
}

#endif // !SDDS_COLLECTION_H_