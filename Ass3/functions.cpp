#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "functions.h"

bool sort_age(entry_t e1, entry_t e2) {
    return (e1.age < e2.age);
}

bool sort_pos(entry_t e1, entry_t e2) {
    return (e1.pos < e2.pos);
}

int abs(int a) {
    if (a < 0)
	return -a;
    return a;
}

int sum_age(const std::vector<entry_t> &d, int start, int len) {
    int sum = 0;

    for (int i = start; i < start+len; ++i) {
	sum += d[i].age;
    }

    return sum;
}

int mean_age(const std::vector<entry_t> &d, int start, int len) {
    return sum_age(d, start, len) / len;
}

int opt_age(const std::vector<entry_t> &d, int start, int len) {
    int val = d[start].age - 1;

    int prev = 0;
    int curr = 0x7FFFFFFF;

    do {
	++val;
	prev = curr;
	curr = 0;

	for (int i = start; i < start+len; ++i) {
	    curr += abs(d[i].age - val);
	}

	std::cout << val << "\t" << prev << "\t" << curr << std::endl;

    } while (prev > curr);

    return val-1;
}

void parse_csv(const char* filename, std::vector<entry_t> &d) {
    std::fstream df;

    df.open(filename, std::fstream::in);

    if (!df.is_open()) {
	std::cout << "Unable to open file " << filename << std::endl;
	return;
    }

    std::string s;
    std::size_t pos;
    entry_t entry;
    entry.pos = 0;
    
    while(getline(df,s)) {
	pos = s.find(',');
	entry.age = std::stoi(s.substr(0,pos));
	entry.phage = std::stoi(s.substr(pos+1));
	d.push_back(entry);
	++entry.pos;
    }

    return;
}

void write_csv(const char* filename, const std::vector<entry_t> &d) {
    std::fstream df;

    df.open(filename, std::fstream::out | std::fstream::trunc);

    if (!df.is_open()) {
	std::cout << "Unable to open file " << filename << std::endl;
	return;
    }

    for (uint i = 0; i < d.size(); ++i) {
	df << d[i].age << "," << d[i].phage << std::endl;
    }

    return;
}

int calc_change (const std::vector<entry_t> d1, const std::vector<entry_t> d2) {
    if (d1.size() != d2.size()) {
	std::cout << "Data sets have unequal lengths" << std::endl;
	return 0;
    }

    int change = 0;
    
    for (uint i = 0; i < d1.size(); ++i) {
	change += abs(d2[i].age - d1[i].age);
    }

    return change;
}

