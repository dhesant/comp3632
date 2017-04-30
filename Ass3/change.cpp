#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

struct entry_t {
    int age;
    bool phage;
} entry;

int main(int argc, char** argv) {
    if (argc < 3) {
	std::cout << "Usage: change <input file 1> <input file 2>" << std::endl;
	return 1;
    }

    std::fstream df1, df2;

    df1.open(argv[1], std::fstream::in);

    if (!df1.is_open()) {
	std::cout << "Unable to open file " << argv[1] << std::endl;
	return 1;
    }

    df2.open(argv[2], std::fstream::in);
    if (!df2.is_open()) {
	std::cout << "Unable to open file " << argv[2] << std::endl;
	return 1;
    }

    std::vector<entry_t> d1, d2;
    std::string s;
    std::size_t pos;

    while(getline(df1,s)) {
	pos = s.find(',');
	entry.age = std::stoi(s.substr(0,pos));
	entry.phage = std::stoi(s.substr(pos+1));
	d1.push_back(entry);
    }

    while(getline(df2,s)) {
	pos = s.find(',');
	entry.age = std::stoi(s.substr(0,pos));
	entry.phage = std::stoi(s.substr(pos+1));
	d2.push_back(entry);
    }

    std::cout << "Datafile 1" << std::endl;
    for (uint i = 0; i < d1.size(); ++i) {
	std::cout << "Age: " << d1[i].age << ", Phage: " << d1[i].phage << std::endl;
    }

    std::cout << std::endl << "Datafile 2" << std::endl;
    for (uint i = 0; i < d2.size(); ++i) {
	std::cout << "Age: " << d2[i].age << ", Phage: " << d1[i].phage << std::endl;
    }

    if (d1.size() != d2.size()) {
	std::cout << "File lengths are unequal. Exiting..." << std::endl;
	return 1;
    }

    int change = 0;
    
    for (uint i = 0; i < d1.size(); ++i) {
	change += abs(d2[i].age - d1[i].age);
    }

    std::cout << std::endl << "Change metric: " << change << std::endl;

    return 0;
}
