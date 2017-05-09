#include <iostream>
#include <vector>
#include <algorithm>

#include "functions_full.h"

#define BIN_SIZE 5

int main(int argc, char** argv) {
    // Ensure valid input arguments
    if (argc < 2) {
	std::cout << "Usage: anonymize <target file>" << std::endl;
	return 1;
    }

    // Load datafile into vector
    std::vector<entry_t> d;
    parse_csv(argv[1], d);

    // DEBUG: Print datafile to cout
    #ifdef DEBUG
    std::cout << "Datafile" << std::endl;
    for (auto e: d) {
	print_entry(e);
    }
    #endif

    // Ensure enough inputs for 5-anonymity
    if (d.size() < BIN_SIZE) {
	std::cout << "Not enough data points" << std::endl;
	return 1;
    }

    // Create input vector of vectors
    std::vector<std::vector<entry_t>> v;
    v.push_back(d);

    // Split vector into vectors for anonymization
    int i = 0;
    while(min_length(v) > BIN_SIZE * 2) {
	v = split_vector(v, i);
	++i;
	if (i >= BIN_SIZE) {
	    i = 0;
	}
    }

    #ifdef DEBUG
    std::cout << "Min Length: " << min_length(v) << std::endl;
    #endif

    // Anonymize vectors
    for (auto &vec: v) {
	for (int i = 0; i < 5; ++i) {
	    int val = opt_data(vec, i);
	    for (auto &e: vec) {
		e.data[i] = val;
	    }
	}
    }
	     
    // Recombine vectors
    std::vector<entry_t> d2;
    d2.reserve(d.size());

    for (const auto &vec: v) {
	d2.insert(d2.end(), vec.begin(), vec.end());
    }

    std::sort(d2.begin(), d2.end(), sort_index);

    // DEBUG: print vector to cout
    #ifdef DEBUG
    std::cout << std::endl << "Output Data" << std::endl;
    for (auto e: d2) {
	print_entry(e);
    }
    #endif

    // Write vector to output file
    write_csv(argv[1], d2);
        
    return 0;
}
