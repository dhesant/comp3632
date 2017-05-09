#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#include "functions_full.h"

int abs(int a) {
    if (a < 0)
	return -a;
    return a;
}

// int sum_age(const std::vector<entry_t> &d, int start, int len) {
//     int sum = 0;

//     for (int i = start; i < start+len; ++i) {
// 	sum += d[i].age;
//     }

//     return sum;
// }

// int mean_age(const std::vector<entry_t> &d, int start, int len) {
//     return sum_age(d, start, len) / len;
// }

// int delta_age(const std::vector<entry_t> &d, int start, int len, int val) {
//     int sum = 0;

//     for (int i = start; i < start+len; ++i) {
// 	sum += abs(d[i].age - val);
//     }

//     return sum;
// }

// int opt_age(const std::vector<entry_t> &d, int start, int len) {
//     // Safety checks
//     if (len <= 0) {
// 	return 0;
//     }
    
//     int val = mean_age(d, start, len);

//     int prev = delta_age(d, start, len, val);
//     int curr = delta_age(d, start, len, ++val);

//     bool grad = false;

//     if (prev > curr) {
// 	grad = true;
//     }

//     while (val >= d[start].age && val <= d[start+len-1].age) {
//         #ifdef DEBUG
// 	std::cout << val << "\t" << prev << "\t" << curr << std::endl;
// 	#endif

// 	prev = curr;

// 	if (grad) {
// 	    curr = delta_age(d, start, len, ++val);
// 	    if (prev >= curr)
// 		return --val;
// 	}

// 	else {
// 	    curr = delta_age(d, start, len, --val);
// 	    if (prev <= curr)
// 		return ++val;
// 	}
//     }

//     return mean_age(d, start, len);
// }

void parse_csv(const char* filename, std::vector<entry_t> &d) {
    std::fstream df;

    df.open(filename, std::fstream::in);

    if (!df.is_open()) {
	std::cout << "Unable to open file " << filename << std::endl;
	return;
    }

    std::string s;
    entry_t entry;
    char c[5];
    entry.index = 0;

    while(getline(df,s)) {
	std::istringstream ss(s);
	ss >> entry.data[0] >> c[0] >> entry.data[1] >> c[1] >> entry.data[2] >> c[2] >> entry.data[3] >> c[3] >> entry.data[4] >> c[4] >> entry.phage;
	d.push_back(entry);
	++entry.index;
    }

    df.close();

    return;
}

void write_csv(const char* filename, const std::vector<entry_t> &d) {
    std::fstream df;

    df.open(filename, std::fstream::out | std::fstream::trunc);

    if (!df.is_open()) {
	std::cout << "Unable to open file " << filename << std::endl;
	return;
    }

    for (auto e: d) {
	for (auto i: e.data) {
	    df << i << ",";
	}
	df << e.phage << std::endl;
    }

    df.close();

    return;
}

int calc_change (const std::vector<entry_t> d1, const std::vector<entry_t> d2) {
    if (d1.size() != d2.size()) {
	std::cout << "Data sets have unequal lengths" << std::endl;
	return 0;
    }

    int change = 0;
    
    for (uint i = 0; i < d1.size(); ++i) {
	for (uint j = 0; j < 5; ++j) {
	    change += abs(d2[i].data[j] - d1[i].data[j]);
	}
    }

    return change;
}

void print_entry(const entry_t &e) {
    std::cout << e.index << ":\t";
    for (auto i: e.data) {
	std::cout << i << ", ";
    }
    std::cout << e.phage << std::endl;
}

std::vector<std::vector<entry_t>> split_vector(const std::vector<std::vector<entry_t>> &v, int index) {
    std::vector<std::vector<entry_t>> v2;
    for (auto d: v) {
	std::sort(d.begin(), d.end(), [&index](entry_t e1, entry_t e2) {
		return (e1.data[index] < e2.data[index]);
	    });
	
	v2.push_back(d);
    }

    return v2;
}
