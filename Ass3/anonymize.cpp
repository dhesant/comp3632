#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"

int main(int argc, char** argv) {
    if (argc < 3) {
	std::cout << "Usage: change <input file 1> <input file 2>" << std::endl;
	return 1;
    }

    std::vector<entry_t> d;

    parse_csv(argv[1], d);

    std::cout << "Datafile" << std::endl;
    for (uint i = 0; i < d.size(); ++i) {
	std::cout << d[i].pos << ":\tAge: " << d[i].age << ", Phage: " << d[i].phage << std::endl;
    }

    std::cout << std::endl << "Sorting Test" << std::endl;

    std::sort(d.begin(), d.end(), sort_age);

    std::cout << "Datafile" << std::endl;
    for (uint i = 0; i < d.size(); ++i) {
	std::cout << d[i].pos << ":\tAge: " << d[i].age << ", Phage: " << d[i].phage << std::endl;
    }

    write_csv(argv[2], d);

    return 0;
}
