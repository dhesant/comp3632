#include <iostream>
#include <vector>

#include "functions.h"

int main(int argc, char** argv) {
    if (argc < 3) {
	std::cout << "Usage: change <input file 1> <input file 2>" << std::endl;
	return 1;
    }

    std::vector<entry_t> d1, d2;

    parse_csv(argv[1], d1);
    parse_csv(argv[2], d2);

    std::cout << "Datafile 1" << std::endl;
    for (uint i = 0; i < d1.size(); ++i) {
	std::cout << d1[i].pos << ":\tAge: " << d1[i].age << ", Phage: " << d1[i].phage << std::endl;
    }

    std::cout << std::endl << "Datafile 2" << std::endl;
    for (uint i = 0; i < d2.size(); ++i) {
	std::cout << d2[i].pos << ":\tAge: " << d2[i].age << ", Phage: " << d1[i].phage << std::endl;
    }

    int change = calc_change(d1, d2);
    
    std::cout << std::endl << "Change metric: " << change << std::endl;

    return 0;
}
