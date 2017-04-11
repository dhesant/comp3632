#include <fstream>
#include <iostream>
#include <cctype>
#include <string>

#define MSG_LEN 400

void disp_ptext(const char* ptext, int len) {
    for (int i = 0; i < MSG_LEN; i += 40) {
	std::cout << i << "\t";
	for (int j = 0; j < 40; ++j) {
	    if (isprint(ptext[i+j]))
		std::cout << ptext[i+j];
	    else
		std::cout << ' ';
	}
	std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    std::fstream ctext0, ctext1, ptext0, ptext1;
    char p0p1[MSG_LEN] = "";
    char p0[MSG_LEN] = "";
    char p1[MSG_LEN] = "";
    char c0[MSG_LEN];
    char c1[MSG_LEN];

    ctext0.open("ctext0.txt", std::fstream::in);
    if (!ctext0.is_open()) {
	std::cout << "Could not open \"ctext0.txt\"" << std::endl;
	return 1;
    }
    
    ctext1.open("ctext1.txt", std::fstream::in);
    if (!ctext1.is_open()) {
	std::cout << "Could not open \"ctext1.txt\"" << std::endl;
	return 1;
    }

    ctext0.get(c0, MSG_LEN);
    ctext1.get(c1, MSG_LEN);
    
    for (int i = 0; i < MSG_LEN; ++i) {
	p0p1[i] = c0[i] ^ c1[i];
    }

    ctext0.close();
    ctext1.close();

    std::string input, str;
    
    while(true) {
	// Display current plaintext
	std::cout << "Plaintext 1" << std::endl;
	disp_ptext(p0, MSG_LEN);
	std::cout << "Plaintext 2" << std::endl;
	disp_ptext(p1, MSG_LEN);

	// Get target message
	std::cout << "Enter a string for crib-dragging: ";
	std::cin.clear();
	std::getline(std::cin, str);

	// Apply input across all inputs
	for (int i = 0; i < MSG_LEN - str.length(); ++i) {
	    std::cout << i << "\t";
	    for (int j = 0; j < str.length(); ++j) {
		std::cout << (char)(p0p1[i+j] ^ str[j]);
	    }
	    std::cout << std::endl;
	}

	// Get suitable input
	std::cout << "Pick suitable line (n for none, e for exit): ";
	std::cin.clear();
	std::getline(std::cin, input);

	if (input == "e") {
	    // Open ptext0.txt
	    ptext0.open("ptext0.txt", std::fstream::out | std::fstream::trunc);
	    if (!ptext0.is_open()) {
		std::cout << "Could not open \"ptext0.txt\"" << std::endl;
		return 1;
	    }
    
	    // Open ptext1.txt
	    ptext1.open("ptext1.txt", std::fstream::out | std::fstream::trunc);
	    if (!ptext1.is_open()) {
		std::cout << "Could not open \"ptext1.txt\"" << std::endl;
		return 1;
	    }

	    // Write decoded plaintexts to text files
	    ptext0.write(p0, MSG_LEN);
	    ptext1.write(p1, MSG_LEN);

	    // Close text files
	    ptext0.close();
	    ptext1.close();

	    // Exit program
	    return 0;
	}

	else if (input == "n")
	    // Break current loop
	    continue;

	else {
	    // Get index from input
	    int index = std::stoi(input);

	    // Select plaintext to write to
	    input = "";
	    while (!(input == "0" || input == "1")) {
		input = "";
		std::cout << "Save string to plaintext 0 or 1 (enter '0' or '1'): ";
		std::cin.clear();
		std::getline(std::cin, input);
	    }

	    if (input == "0") {
		for (int i = 0; i < str.length(); ++i) {
		    p0[index + i] = str[i];
		    p1[index + i] = p0p1[index + i] ^ p0[index + i];
		}
	    }
	    else if (input == "1") {
		for (int i = 0; i < str.length(); ++i) {
		    p1[index + i] = str[i];
		    p0[index + i] = p0p1[index + i] ^ p1[index + i];
		}
	    }
	}
    }
    
    return 0;
}
