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

    // Calculate number of bins for k
    uint len = d.size();
    uint bins = len / BIN_SIZE;

    #ifdef DEBUG
    std::cout << "No of bins: " << bins << std::endl << std::endl;
    #endif 

    int metric = 0x7FFFFFFF;

    // Init random number generator
    std::random_device rd;
    std::mt19937 e(rd());
    std::uniform_int_distribution<> rnd(0,bins);

    for (int t = 0; t < 50; ++t) {
	// Setup temp vars
	std::vector<entry_t> d2 = d;
	std::vector<uint> lens, index, data;

	// Load number of vars per bin
	for (uint i = 0; i < bins; ++i) {
	    lens.push_back(BIN_SIZE);
	}
    
	// Update vars per bin to accomidate length of data file
	while((uint)std::accumulate(lens.begin(), lens.end(), 0) < len) {
	    ++lens[rnd(e)];
	}

	// DEBUG: print length distribution
	std::cout << "Current split: ";
	for (uint i = 0; i < bins; ++i) {
	    std::cout << lens[i] << ", ";
	}
	std::cout << std::endl;

	// Calculate offset index
	index.push_back(0);
	for (uint i = 0; i < bins; ++i) {
	    index.push_back(index[i] + lens[i]);
	}

	// Get data values for anonyminity dataset
	for (uint i = 0; i < bins; ++i) {
	    data.push_back(mean_age(d, index[i], lens[i]));
	}

	// Update dataset
	for (uint j = 0; j < bins; ++j) {
	    for (uint i = index[j]; i < index[j+1]; ++i) {
		d2[i].age = data[j];
	    }
	}

	// Check if current metric is better
	int current = calc_change(d, d2);
	std::cout << "Current metric: " << current << std::endl;

	if (current < metric) {
	    std::cout << "Current index better than previous. Writing to output..." << std::endl;
	    metric = current;
	    std::sort(d2.begin(), d2.end(), sort_pos);
	    write_csv(argv[2], d2);
	}
    }

    return 0;
}
