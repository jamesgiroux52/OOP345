// ***********************************************************
// File    Database.h
// Version 1.0
// Date    March 22, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Database Module
// -----------------------------------------------------------
// I have done all the coding myself and only copied the
// code that my professor provided to complete this workshop
// ***********************************************************

#ifndef SDDS_DATABASE_H_
#define SDDS_DATABASE_H_

#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

namespace sdds {
    // error status enumerator
    enum class Err_Status {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
    };

    // database template class
    template <typename T>
    class Database {
        static std::shared_ptr<Database> m_instance;
        size_t m_numItems{};
        std::string m_key[20];
        T m_value[20];
        std::string m_fileName{};
        // handy replace function 
        static void replaceCh(std::string& str, const char ch) {
            for (auto i = 0u; i < str.length(); ++i)
                if (str[i] == ch)
                    str[i] = ' ';
        }
        // private constructor to ensure client can not create instances
        Database(const std::string& file);
        void encryptDecrypt(T& value) {}
    public:
        static std::shared_ptr<Database<T>> getInstance(const std::string& filename);
        Err_Status GetValue(const std::string& key, T& value) const;
        Err_Status SetValue(const std::string& key, const T& value);
        ~Database();
    };

    // instance class variable instantiation
    template <typename T>
    std::shared_ptr<Database<T>> Database<T>::m_instance = nullptr;

    // std::string specialization to encrypt and decrypt values
    template <>
    void Database<std::string>::encryptDecrypt(std::string& str) {
        char key[]{ "secret encryption key" };
        for (auto& i : str)
            for (auto j : key)
                i ^= j;
    }

    // long long specialization to encrypt and decrypt values
    template <>
    void Database<long long>::encryptDecrypt(long long& num) {
        char key[]{ "super secret encryption key" };
        char* bytes = reinterpret_cast<char*>(&num);
        for (auto i = 0u; i < sizeof(num); ++i)
            for (auto j : key)
                bytes[i] ^= j;
    }

    // private constructor to build a database
    template <typename T>
    Database<T>::Database(const std::string& filename) {
        std::cout << "[" << this << "] " << "Database(const string&)" << std::endl;
        m_fileName = filename;
        std::ifstream fs(m_fileName);
        int cnt{};
        std::string line{};
        getline(fs, line, '\n');
        while (fs) {
            std::string str{};
            std::stringstream s(line);
            s >> str;
            replaceCh(str, '_');
            m_key[cnt] = str;
            s >> m_value[cnt];
            encryptDecrypt(m_value[cnt]);
            ++cnt;
            getline(fs, line, '\n');
        }
        m_numItems = cnt;
        fs.close(); 
    }

    // create or return only one instance for a specific type
    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::getInstance(const std::string& filename) {
        if (!m_instance)
            m_instance = std::shared_ptr<Database<T>>(new Database(filename));
        return m_instance;
    }

    // get a value from the DB
    template <typename T>
    Err_Status Database<T>::GetValue(const std::string& key, T& value) const {
        for (int i = 0; i < 20; ++i) {
            if (m_key[i] == key) {
                value = m_value[i];
                return Err_Status::Err_Success;
            }
        }
        return Err_Status::Err_NotFound;
    }

    // set a value in DB if there is space
    template <typename T>
    Err_Status Database<T>::SetValue(const std::string& key, const T& value) {
        if (m_numItems < 20) {
            m_key[m_numItems] = key;
            m_value[m_numItems] = value;
            ++m_numItems;
            return  Err_Status::Err_Success;
        } else
            return Err_Status::Err_OutOfMemory;
    }

    // cleanup and save backup files
    template <typename T>
    Database<T>::~Database() {
        std::cout << "[" << this << "] " << "~Database()" << std::endl;
        std::string file = m_fileName + ".bkp.txt";
        std::ofstream fs(file);
        for (auto i = 0u; i < m_numItems; ++i) {
            fs << std::left;
            fs.width(25);
            fs << m_key[i] << " -> ";
            encryptDecrypt(m_value[i]);
            fs << m_value[i] << std::endl;
        }
        fs.close();
    }
}
#endif // !SDDS_DATABASE_H_