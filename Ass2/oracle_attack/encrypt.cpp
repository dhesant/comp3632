#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "decrypt_library.h"

int main (int argc, char** argv) {
    if (argc < 2) {
	std::cout << "Usage: encrypt <filename>" << std::endl;
	return 1;
    }

    std::fstream plaintext;
    plaintext.open(argv[1], std::fstream::in);
    if(!plaintext.is_open()) {
	std::cout << "Cannot open file \"" << argv[1] << "\"" << std::endl;
	return 1;
    }

    std::vector<char*> x, y;
    char* str;
    
    // Read remaining text into 16 byte chunks in y
    while(!plaintext.eof()) {
	str = new char[16];
	plaintext.get(str, 17);
	x.push_back(str);
    }

    #ifdef DEBUG
    // Debug output created variables
    std::cout << "Plaintext" << std::endl;
    for (uint i = 0; i < x.size(); ++i) {
    	std::cout << "Block " << i << ":\t" << x[i] << std::endl;
    }
    #endif

    // Generate random ciphertext block
    str = new char[16];
    srand(std::time(0));
    for (int i = 0; i < 16; ++i) {
    	str[i] = (char)rand();
    }
    y.push_back(str);

    char* d;
    
    // Calculate preceeding ciphertext block
    for (int i = x.size()-1; i >= 0; --i) {
	d = decrypt_block(str);

	str = new char[16];
	for (int j = 0; j < 16; ++j) {
	    str[j] = d[j] ^ x[i][j];
	}
	y.insert(y.begin(), str);
    }
    
    #ifdef DEBUG
    // Debug output created variables
    std::cout << std::endl << "Ciphertext" << std::endl;
    for (uint i = 0; i < y.size(); ++i) {
    	std::cout << "Block " << i << ":\t" << y[i] << std::endl;
    }
    #endif

    // Ouput ciphertext
    for (uint i = 0; i < y.size(); ++i) {
    	std::cout << y[i];
    }
    
    
    // cleanup
    for (uint i = 0; i < x.size() ; ++i) {
	delete[] x[i];
    }

    for (uint i = 0; i < y.size() ; ++i) {
	delete[] y[i];
    }
    
    return 0;
}
