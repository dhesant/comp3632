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

    std::vector<std::vector<entry_t>> v1, v2;
    v1.push_back(d);

    v2 = split_vector(v1, 0);

    std::vector<entry_t> d2 = v2[0];
    std::cout << std::endl << "Datafile 2" << std::endl;

    #ifdef DEBUG
    for (auto e: d2) {
	print_entry(e);
    }
    #endif
    
    // // Sort datafile by age
    // std::sort(d.begin(), d.end(), sort_age);

    // // DEBUG: Print sorted datafile to cout
    // #ifdef DEBUG
    // std::cout << std::endl << "Sorted Datafile" << std::endl;
    // for (uint i = 0; i < d.size(); ++i) {
    // 	std::cout << d[i].pos << ":\tAge: " << d[i].age << ", Phage: " << d[i].phage << std::endl;
    // }
    // #endif

    // // Calculate number of bins
    // uint max_bins = d.size() / BIN_SIZE;

    // #ifdef DEBUG
    // std::cout << "No of bins: " << max_bins << std::endl << std::endl;
    // #endif 

    // // Setup storage table
    // std::vector<std::vector<metric_t>> metric;
    // metric.resize(max_bins);
    // for (uint i = 0; i < metric.size(); ++i) {
    // 	metric[i].resize(d.size());
    // }

    // // Calculate first col of the table
    // for (uint i = 0; i < d.size(); ++i) {
    // 	metric[0][i].metric = opt_metric(d, 0, i+1);
    // 	metric[0][i].bins.push_back(i+1);
    // }

    // // Calculate rest of the cols of the table
    // for (uint n = 1; n < max_bins; ++n) {
    // 	for (uint i = 0; i < d.size(); ++i) {
    // 	    std::vector<metric_t> v;
	
    // 	    for (uint j = 0; j <= i; ++j) {
    // 		int k = i - j;
    // 		metric_t m = metric[n-1][k];

    // 		// Ensure valid fetch
    // 		if (m.metric < 0) {
    // 		    continue;
    // 		}
	    
    // 		int delta = opt_metric(d, k+1, j);

    // 		// If valid metric, push to vector
    // 		if (delta >= 0) {
    // 		    m.metric += delta;
    // 		    m.bins.push_back(j);
    // 		    v.push_back(m);
    // 		}
    // 	    }

    // 	    // Sort vector by metric
    // 	    std::sort(v.begin(), v.end(), metric_sort);

    // 	    // Ensure vector is not empty
    // 	    if(v.empty()) {
    // 		v.push_back(metric[n-1][i]);
    // 	    }

    // 	    // DEBUG: Print metric info to cout
    // 	    #ifdef DEBUG
    // 	    for (uint k = 0; k < v.size(); ++k) {
    // 		std::cout << i+1 << ": " << k << ": ";
    // 		print_metric(v[k]);
    // 	    }
    // 	    std::cout << std::endl;
    // 	    #endif

    // 	    // Push best metric to calc table
    // 	    metric[n][i] = v[0];
    // 	}
    // }

    // // Print calc table
    // std::cout << "Len";
    // for (uint i = 0; i < metric.size(); ++i) {
    // 	std::cout << "\t" << i+1;
    // }
    // std::cout << std::endl;

    // for (uint j = 0; j < d.size(); ++j) {
    // 	std::cout << j+1;
    // 	for (uint i = 0; i < metric.size(); ++i) {
    // 	    std::cout << "\t" << metric[i][j].metric;
    // 	}
    // 	std::cout << std::endl;
    // }

    // // Create vectors for data write
    // std::vector<entry_t> d2 = d;
    // std::vector<uint> bins = metric[metric.size()-1][d.size()-1].bins;
    // std::vector<uint> index, data;
	
    // // Calculate offset index
    // index.push_back(0);
    // for (uint i = 0; i < bins.size(); ++i) {
    // 	index.push_back(index[i] + bins[i]);
    // }

    // // Get data values for anonyminity dataset
    // for (uint i = 0; i < bins.size(); ++i) {
    // 	data.push_back(opt_age(d, index[i], bins[i]));
    // }

    // // Update dataset
    // for (uint j = 0; j < bins.size(); ++j) {
    // 	for (uint i = index[j]; i < index[j+1]; ++i) {
    // 	    d2[i].age = data[j];
    // 	}
    // }

    // // Write metric to cout
    // int current = calc_change(d, d2);
    // std::cout << "Current metric: " << current << std::endl;

    // // Write metric to output file
    // std::sort(d2.begin(), d2.end(), sort_pos);
    // write_csv(argv[1], d2);
    
    return 0;
}
