#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
//#include <iomanip>
#include "pstream.h"

// Function prototypes
void decrypt_byte(const std::vector<std::string> &ctext, std::vector<std::string> &ptext);
void decrypt_block(const std::vector<std::string> &ctext, std::vector<std::string> &ptext);
void decrypt(const std::vector<std::string> &ctext, std::vector<std::string> &ptext);
bool oracle(uint8_t* block, int len);

void decrypt_byte(const std::vector<std::string> &ctext, std::vector<std::string> &ptext) {
    uint8_t r[16];

    // Generate random block r
    srand(time(0));
    for (int i = 0; i < 15; ++i) {
	r[i] = (uint8_t)rand();
    }
    r[15] = 0;

    uint8_t block[32];
    
    oracle(block, 32);
}

void decrypt_block(const std::vector<std::string> &ctext, std::vector<std::string> &ptext) {
    
}

void decrypt(const std::vector<std::string> &ctext, std::vector<std::string> &ptext) {
    
}

bool oracle(uint8_t* block, int len) {
    // std::fstream otext;

    // otext.open("oracle_test", std::fstream::out | std::fstream::trunc);
    // if (!otext.is_open()) {
    // 	return false;
    // }

    // for (int i = 0; i < len; ++i) {
    // 	otext.put(block[i]);
    // }

    std::string cmd = "python ./oracle.py ctext";

    redi::ipstream proc(cmd.c_str(), redi::pstreams::pstdout);
    std::string str;
    while (proc >> str) {
	std::cout << str << std::endl;
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

    std::vector<std::string> ctext, ptext;
    std::string s;

    while(std::getline(ciphertext, s)) {
	ctext.push_back(s);
    }

    ciphertext.close();

    decrypt_byte(ctext, ptext);
    
    return 0;
}
