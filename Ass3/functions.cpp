#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "functions.h"

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

    while(getline(df,s)) {
	pos = s.find(',');
	entry.age = std::stoi(s.substr(0,pos));
	entry.phage = std::stoi(s.substr(pos+1));
	d.push_back(entry);
    }
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
