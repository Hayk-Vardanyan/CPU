#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include "ram.h"

bool Ram::generateBinaryCode() {
    setAssemblyAndBinaryCommands();	
    std::vector<std::string> labels;
    for (auto it = memory.begin(); it != memory.end(); ++it) {

	for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
		auto checkCommand = assemblyAndBinaryCommands.find(*it2);
		auto iter = std::find(labels.begin(), labels.end(), *it2);
		if (checkCommand != assemblyAndBinaryCommands.end()) {
		*it2 = assemblyAndBinaryCommands[*it2];
			}
		else if(checkCommand == assemblyAndBinaryCommands.end() && (*it2)[(*it2).size()-1] != ':' && iter == labels.end() 
			       	&& !checkNumber(*it2)) { 
				return false;
			}
		else if( (*it2)[(*it2).size()-1] == ':') {
			labels.push_back((*it2).substr(0, (*it2).size()-1 ));
			}			
		}
	}
	return true;
}

int Ram::stoi(std::string& str) { 
	std::vector<int> vec;
	for(int i = 0; i < str.size(); ++i) { 
		vec.push_back(str[i] - 48); 
		}
	int res = 0;
	for(int i = vec.size() - 1; i >= 0; --i ) { 
		res += vec[i] * pow(10, vec.size() - i - 1);
		} 
	return res;
} 

bool Ram::checkNumber(std::string& number) {
	bool negative = (number[0] == '-');
	if (negative) {
		number = number.substr(1);
	}
	for (int i = 0; i < number.size(); ++i) {
		if(!(number[i] >= '0' && number[i] <= '9')) {
			return false;
		}
	}
	int decimalNum = stoi(number);
	number.clear();
	for (; decimalNum != 0; decimalNum /= 2) {
		if(decimalNum % 2 == 0) {
			number = "0" + number;
		} else {
			number = "1" + number; 
		}
	}
	if(negative) {
		number = "1" + number;
	} else {
		number = "0" + number;
	}
	return true;
}

void Ram::setAssemblyAndBinaryCommands() {
    assemblyAndBinaryCommands.emplace("move", "1111");
    assemblyAndBinaryCommands.emplace("print", "1110");
    assemblyAndBinaryCommands.emplace("add", "1010");
    assemblyAndBinaryCommands.emplace("sub", "0101");
    assemblyAndBinaryCommands.emplace("div", "0011");
    assemblyAndBinaryCommands.emplace("mul", "01111");
    assemblyAndBinaryCommands.emplace("cmp", "011111");
    assemblyAndBinaryCommands.emplace("jg", "00101");
    assemblyAndBinaryCommands.emplace("jge", "00001");
    assemblyAndBinaryCommands.emplace("jl", "00100");
    assemblyAndBinaryCommands.emplace("jle", "00111");
    assemblyAndBinaryCommands.emplace("je", "00110");
    
    assemblyAndBinaryCommands.emplace("eax", "0001");
    assemblyAndBinaryCommands.emplace("ebx", "0010");
    assemblyAndBinaryCommands.emplace("ecx", "0100");
    assemblyAndBinaryCommands.emplace("edx", "1000");
}

Ram::Ram()
{
    for (int i = 0; i < 10; ++i) {
        addresses.push_back("000" + std::to_string(i));
    }
}

bool Ram::fillMemory(const std::string& fileName) {
    unsigned int index = 0;
    std::vector<std::string> currentCommands;
    read.open(fileName);
    if (!read.is_open()) {
		std::cout << "No such a file to open\n";
	}	
    
    while(!read.eof()) {
	std::string str;
        getline(read,str);
	std::stringstream readWord(str);

        while(!readWord.eof()) {    
            readWord >> str;
            currentCommands.push_back(str);   
        }
        	memory.emplace(addresses[index], currentCommands);
		index += 1;
		currentCommands.clear();
	}   
	memory.erase(--memory.end());
	read.close();    
	
	if (fileName.substr(fileName.size() - 3) == "asm") {
		if (generateBinaryCode()) {
			return true;
		} else {
			return false;
		}
	}
	return true;
}
