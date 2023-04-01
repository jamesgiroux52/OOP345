// Workshop 9 - Multi-Threading, Thread Class
// process_data.h
// 2021/1/5 - Jeevan Pant

#ifndef SDDS_W9_PROCESSDATA_H
#define SDDS_W9_PROCESSDATA_H

#include<iostream>
#include<string>
#include<fstream>
#include<functional>

namespace sdds_ws9 {
	void computeAvgFactor(const int*, int size, int div, double& avg);
	void computeVarFactor(const int*, int size, int div, double avg, double& var);
	class ProcessData {
		int total_items{};
		int* data{};
        // Following parameters are included to be used for managing multi-threaded 
        //  computation in the operator() function. 
        int num_threads{ 0 }; // to hold number of threads 
        double* averages{ nullptr }; // to hold average factors 
        double* variances{ nullptr }; // to hold variance factors
        int* p_indices{ nullptr }; // to hold partitioning indices
	public:
		ProcessData(std::string, int n_threads);
		ProcessData(const ProcessData&) = delete;
		ProcessData& operator=(const ProcessData&) = delete;
		~ProcessData();
		operator bool() const;
		void operator()(std::string fileName, double& avg, double& variance);
	};
}
#endif 