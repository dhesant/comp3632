#include <fstream>
#include <iostream>

int main(int argc, char** argv) {

    std::fstream ctext0;
    std::fstream ctext1;
    std::fstream ptext12;

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
    
    ptext12.open("ptext12.txt", std::fstream::out | std::fstream::trunc);
    if (!ptext12.is_open()) {
	std::cout << "Could not open \"ptext12.txt\"" << std::endl;
	return 1;
    }
    

    while (!(ctext0.eof() || ctext1.eof())) {
	ptext12.put(ctext0.get() ^ ctext1.get());
    }

    return 0;
}
