// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant

// ***********************************************************
// File   process_data.cpp
// Version 1.0
// Date    March 22, 2023
// Author  James Giroux - jgiroux1@myseneca.ca
// Stu #   129198164
// Description:
// Database Module
// -----------------------------------------------------------
// I have done all the TODO sections myself and only copied the
// code that my professor provided to complete this workshop
// ***********************************************************

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <numeric>
#include "process_data.h"

using namespace std;

namespace sdds_ws9 {

    // The following function receives array (pointer) as the first argument, number of array 
    //   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
    //   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
    //   hold average of the array elements. When they are different, avg will hold a value called 
    // 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
    //   different values for size and divisor will be useful for multi-threaded implementation in part-2. 
    void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
        avg = 0;
        for (int i = 0; i < size; i++) {
            avg += arr[i];
            //std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
        avg /= divisor;
    }
    // The following function receives array (pointer) as the first argument, number of array elements  
    //   (size) as second argument, divisor as the third argument, computed average value of the data items
    //   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
    //   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
    //   the array elements. When they are different, var will hold a value called as variance factor. 
    //   For part 1, you will be using same value for size and double. Use of different values for size 
    //   and divisor will be useful for multi-threaded implementation in part-2. 
    void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
        var = 0;
        for (int i = 0; i < size; i++) {
            var += (arr[i] - avg) * (arr[i] - avg);
            //std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        }
        var /= divisor;
    }
    // The following constructor of the functor receives name of the data file, opens it in 
    //   binary mode for reading, reads first int data as total_items, allocate memory space 
    //   to hold the data items, and reads the data items into the allocated memory space. 
    //   It prints first five data items and the last three data items as data samples. 
    //   
    ProcessData::ProcessData(std::string filename, int n_threads) {
        // TODO: Open the file whose name was received as parameter and read the content
        //         into variables "total_items" and "data". Don't forget to allocate
        //         memory for "data".
        //       The file is binary and has the format described in the specs.

        fstream bfs(filename, ios::in | ios::binary);
        // get number of items
        bfs.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));
        // allocate memory for data based on size
        data = new int[total_items];
        // read file contents
        bfs.read(reinterpret_cast<char*>(data), sizeof(data[0]) * total_items);
        // close file
        bfs.close();

        std::cout << "Item's count in file '" << filename << "': " << total_items << std::endl;
        std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
            << data[total_items - 3] << ", " << data[total_items - 2] << ", "
            << data[total_items - 1] << "]\n";

        // Following statements initialize the variables added for multi-threaded 
        //   computation
        num_threads = n_threads;
        averages = new double[num_threads] {};
        variances = new double[num_threads] {};
        p_indices = new int[num_threads + 1] {};
        for (int i = 0; i < num_threads + 1; ++i)
            p_indices[i] = i * (total_items / num_threads);
    }

    ProcessData::~ProcessData() {
        delete[] data;
        delete[] averages;
        delete[] variances;
        delete[] p_indices;
    }
    ProcessData::operator bool() const {
        return total_items > 0 && data && num_threads > 0 
            && averages && variances && p_indices;
    }
    // TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
    //   function logic for the computation of average and variance by running the 
    //   function computeAvgFactor and computeVarFactor in multile threads. 
    // The function divides the data into a number of parts, where the number of parts is 
    //   equal to the number of threads. Use multi-threading to compute average-factor for 
    //   each part of the data by calling the function computeAvgFactor. Add the obtained 
    //   average-factors to compute total average. Use the resulting total average as the 
    //   average value argument for the function computeVarFactor, to compute variance-factors 
    //   for each part of the data. Use multi-threading to compute variance-factor for each 
    //   part of the data. Add computed variance-factors to obtain total variance.
    // Save the data into a file with filename held by the argument fname_target. 
    // Also, read the workshop instruction.
    void ProcessData::operator()(std::string fileName, double& avg, double& var) {
        // placeholders for std::bind
        using namespace std::placeholders;

        // vectors of threads
        std::vector<std::thread> avgT(num_threads);
        std::vector<std::thread> varT(num_threads);

        // calculate average using thread(s)
        for (int i = 0; i < num_threads; ++i)
            avgT[i] = std::thread(std::bind(computeAvgFactor, _1, _2, total_items, _3), 
                &(data[p_indices[i]]), p_indices[1], std::ref(averages[i]));
        for (auto& t : avgT) 
            t.join();
        for (int i = 0; i < num_threads; ++i)
            avg += averages[i];

        // calculate variance using thread(s)
        for (int i = 0; i < num_threads; ++i)
            varT[i] = std::thread(std::bind(computeVarFactor, _1, _2, total_items, avg, _3), 
                &data[p_indices[i]], p_indices[1], std::ref(variances[i]));
        for (auto& t : varT)
            t.join();
        for (int i = 0; i < num_threads; ++i)
            var += variances[i];

        // save to file in binary
        fstream bfs(fileName, ios::out | ios::trunc | ios::binary);
        bfs.write(reinterpret_cast<char*>(&total_items), sizeof(total_items));
        bfs.write(reinterpret_cast<char*>(data), sizeof(data[0]) * total_items);
        bfs.close();
    }

}