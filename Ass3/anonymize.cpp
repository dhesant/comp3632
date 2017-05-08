#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

#include "functions.h"

#define BIN_SIZE 5

int main(int argc, char** argv) {
    // Ensure valid input arguments
    if (argc < 3) {
	std::cout << "Usage: change <input file 1> <input file 2>" << std::endl;
	return 1;
    }

    // Load datafile into vector
    std::vector<entry_t> d;
    parse_csv(argv[1], d);

    // DEBUG: Print datafile to cout
    #ifdef DEBUG
    std::cout << "Datafile" << std::endl;
    for (uint i = 0; i < d.size(); ++i) {
	std::cout << d[i].pos << ":\tAge: " << d[i].age << ", Phage: " << d[i].phage << std::endl;
    }
    #endif

    // Sort datafile by age and print to cout
    std::sort(d.begin(), d.end(), sort_age);

    // DEBUG: Print sorted datafile to cout
    #ifdef DEBUG
    std::cout << std::endl << "Sorted Datafile" << std::endl;
    for (uint i = 0; i < d.size(); ++i) {
	std::cout << d[i].pos << ":\tAge: " << d[i].age << ", Phage: " << d[i].phage << std::endl;
    }
    #endif

    if (d.size() < BIN_SIZE) {
	std::cout << "Not enough data points" << std::endl;
	return 1;
    }
    
    // Calculate number of bins for k
    uint max_bins = d.size() / BIN_SIZE;

    #ifdef DEBUG
    std::cout << "No of bins: " << max_bins << std::endl << std::endl;
    #endif 

    // Setup storage table
    std::vector<std::vector<metric_t>> metric;

    metric.resize(max_bins);
    for (uint i = 0; i < metric.size(); ++i) {
	metric[i].resize(d.size());
    }

    // Calculate first col of table
    for (uint i = 0; i < d.size(); ++i) {
	metric[0][i].metric = opt_metric(d, 0, i+1);
	metric[0][i].bins.push_back(i+1);
    }

    // Calculate second col of table
    for (uint n = 1; n < max_bins; ++n) {
	for (uint i = 0; i < d.size(); ++i) {
	    std::vector<metric_t> v;
	
	    for (uint j = 0; j <= i; ++j) {
		int k = i - j;
		metric_t m = metric[n-1][k];

		// Ensure valid fetch
		if (m.metric < 0) {
		    continue;
		}
	    
		int delta = opt_metric(d, k+1, j);
		std::cout << n << "," << i << ": " << k << "," << j << ": " << delta << std::endl;
		
		if (delta >= 0) {
		    m.metric += delta;
		    m.bins.push_back(j);
		    v.push_back(m);
		}
	    }

	    std::sort(v.begin(), v.end(), metric_sort);
	
	    if(v.empty()) {
		v.push_back(metric[n-1][i]);
	    }

	    for (uint k = 0; k < v.size(); ++k) {
		std::cout << i+1 << ": " << k << ": ";
		print_metric(v[k]);
	    }
	    std::cout << std::endl;

	    metric[n][i] = v[0];
	}
    }

    // Print calc table
    std::cout << "Len";
    for (uint i = 0; i < metric.size(); ++i) {
	std::cout << "\t" << i+1;
    }
    std::cout << std::endl;

    for (uint j = 0; j < d.size(); ++j) {
	std::cout << j+1;
	for (uint i = 0; i < metric.size(); ++i) {
	    std::cout << "\t" << metric[i][j].metric;
	}
	std::cout << std::endl;
    }
    
    return 0;
}
