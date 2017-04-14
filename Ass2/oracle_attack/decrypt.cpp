#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "pstream.h"

//#define DEBUG

// Function prototypes
bool oracle(char* block, int len);

char decrypt_byte(const char* y) {
    char block[32];

    srand(std::time(0));
    for (int i = 0; i < 15; ++i) {
	block[i] = (char)rand();
    }
    block[15] = 0;

    // Load r & y into the padding oracle block
    for (int i = 0; i < 16; ++i) {
	block[i+16] = y[i];
    }

    // Increment i until the padding oracle return true
    while (!oracle(block, 32)) {
	++block[15];
	#ifdef DEBUG
	std::cout << "\rk: 15; i: " << (int)block[15];
	#endif
    }
#ifdef DEBUG
    std::cout << std::endl;
	#endif
    
    // Calculate the decrypted block value
    for (int k = 0; k < 15; ++k) {
	block[k] = (char)rand();
	if (!oracle(block, 32)) {
	    return block[15] ^ (17 - (k+1));
	}
    }

    return block[15] ^ 1;
}

char* decrypt_block(const char* y) {
    char* d = new char[16];
    char block[32];

    d[15] = decrypt_byte(y);
    
    srand(std::time(0));
    for (int i = 0; i < 16; ++i) {
	block[i] = (char)rand();
    }

    for (int i = 0; i < 16; ++i) {
	block[i+16] = y[i];
    }

    for (int i = 14; i >= 0; --i) {
	// Load d values into r
	for (int j = 15; j > i; --j) {
	    block[j] = d[j] ^ (17 - (i+1));
	}

	// Set i to 0
	block[i] = 0;

	// Increment i until padding block returns true
	while(!oracle(block, 32)) {
	    ++block[i];
	#ifdef DEBUG
	    std::cout << "\rk: " << i << "; i: " << (int)block[i];
	#endif
	}
	d[i] = block[i] ^ (17 - (i+1));
	#ifdef DEBUG
	std::cout << std::endl;
	#endif
    }

    return d;
}

char** decrypt(const char* iv, const std::vector<char*> y) {
    // Get length of output message
    uint len = y.size();

    // Initialize output char array
    char** ptext = new char* [len];
    for (uint i = 0; i < len; ++i) {
	ptext[i] = new char [16];
    }

    char* d;
    // Decrypt ciphertext
    for (uint i = len-1; i > 0; --i) {
#ifdef DEBUG
	std::cout << "Block " << i << std::endl;
#endif
	d = decrypt_block(y[i]);
	for (int j = 0; j < 16; ++j) {
	    ptext[i][j] = d[j] ^ y[i-1][j];
	}
    }

#ifdef DEBUG
    std::cout << "Block 0" << std::endl;
#endif
    d = decrypt_block(y[0]);
    for (int i = 0; i < 16; ++i) {
	ptext[0][i] = d[i] ^ iv[i];
    }

    // Return plaintext
    return ptext;
}

bool oracle(char* block, int len) {
    std::fstream otext;

    otext.open("oracle_text", std::fstream::out | std::fstream::trunc);
    if (!otext.is_open()) {
    	return false;
    }

    for (int i = 0; i < len; ++i) {
    	otext.put(block[i]);
    }

    otext.close();

    std::string cmd = "python ./oracle.py oracle_text";

    redi::ipstream proc(cmd.c_str(), redi::pstreams::pstdout);

    std::string str;
    while (proc >> str) {
	if (str == "1") {
	    return true;
	}
    }

    return false;
}

int main (int argc, char** argv) {
    if (argc < 2) {
	std::cout << "Invalid argument. Expected filename" << std::endl;
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
