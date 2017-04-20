#include <iostream>
#include <fstream>
#include <vector>

#include "decrypt_library.h"

int main (int argc, char** argv) {
    if (argc < 2) {
	std::cout << "Usage: decrypt <filename>" << std::endl;
	return 1;
    }

    std::fstream ciphertext;
    ciphertext.open(argv[1], std::fstream::in);
    if(!ciphertext.is_open()) {
	std::cout << "Cannot open file \"" << argv[1] << "\"" << std::endl;
	return 1;
    }

    char iv[16];
    std::vector<char*> y;
    char* str;
    
    // Get iv into string
    ciphertext.get(iv, 17);

    // Read remaining text into 16 byte chunks in y
    while(!ciphertext.eof()) {
	str = new char[16];
	ciphertext.get(str, 17);
	y.push_back(str);
    }

    #ifdef DEBUG
    // Debug output created variables
    std::cout << "Ciphertext" << std::endl;
    std::cout << "IV:\t" << iv << std::endl;
    for (uint i = 0; i < y.size(); ++i) {
    	std::cout << "Block " << i << ":\t" << y[i] << std::endl;
    }
    #endif

    // // Decrypt byte
    // std::cout << "Decrypt Byte" << std::endl;

    // int index = y.size();
    // --index;

    // char d = decrypt_byte(y[index]);
    // d = d ^ y[index-1][15];
    
    // std::cout << "byte: " << (int)d << std::endl;

    // // Decrypt block
    // std::cout << std::endl << "Decrypt Block" << std::endl;
    // char* d2 = decrypt_block(y[index]);
    // for (int i = 0; i < 16; ++i) {
    // 	d2[i] = d2[i] ^ y[index-1][i];
    // }

    // for (int i = 0; i < 16; ++i) {
    // 	std::cout << d2[i];
    // }
    // std::cout << std::endl;

    // Decrypt ciphertext
#ifdef DEBUG
    std::cout << std::endl << "Decrypt" << std::endl;
#endif
    
    char** ptext = decrypt(iv, y);

    //std::cout << "Plaintext:" << std::endl;
    
    for (uint i = 0; i < y.size(); ++i) {
	for (int j = 0; j < 16; ++j) {
	    std::cout << ptext[i][j];
	}
    }
    
    // cleanup
    for (uint i = 0; i < y.size() ; ++i) {
	delete[] y[i];
    }
    
    return 0;
}
