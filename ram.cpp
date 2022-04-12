#include "ram.h"

void Ram::generateBinaryCode() {
    setAssemblyAndBinaryCommands();	
	
	for (auto it = memory.begin(); it != memory.end(); ++it) {
		for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
			
			auto checkCommand = assembly_and_binary_commands.find(*it2);
			if (checkCommand != assembly_and_binary_commands.end()) {
			*it2 = assembly_and_binary_commands[*it2];
			}
		}
	}

	
}

void Ram::setAssemblyAndBinaryCommands() {
    assembly_and_binary_commands.emplace("move", "1111");
    assembly_and_binary_commands.emplace("print", "1110");
    assembly_and_binary_commands.emplace("add", "1010");
    assembly_and_binary_commands.emplace("sub", "0101");
    assembly_and_binary_commands.emplace("div", "0011");
    assembly_and_binary_commands.emplace("mul", "01111");
    assembly_and_binary_commands.emplace("cmp", "011111");
    assembly_and_binary_commands.emplace("jg", "00101");
    assembly_and_binary_commands.emplace("jge", "00001");
    assembly_and_binary_commands.emplace("jl", "00100");
    assembly_and_binary_commands.emplace("jle", "00111");
    assembly_and_binary_commands.emplace("je", "00110");
    
    assembly_and_binary_commands.emplace("eax", "0001");
    assembly_and_binary_commands.emplace("ebx", "0010");
    assembly_and_binary_commands.emplace("ecx", "0100");
    assembly_and_binary_commands.emplace("edx", "1000");
}

void Ram::checkAssembly() {
	
	std::vector<std::string> firstAddress = memory["0000"];
	if (firstAddress[0][0] == '0' || firstAddress[0][0] == '1') { return; }

	generateBinaryCode();
}

Ram::Ram()
{
    for (int i = 0; i < 10; ++i) {
        addresses.push_back("000" + std::to_string(i));
    }
}

void Ram::FillMemory(const std::string& file_name) {
    unsigned int index = 0;
    std::vector<std::string> currentCommands;
    fin.open(file_name);
    while(!fin.eof()){
	std::string str;
        getline(fin,str);
	std::stringstream s(str);
	
        while(!s.eof()){    
            s >> str;
            currentCommands.push_back(str);   
        }
        memory.emplace(addresses[index], currentCommands);
	index += 1;
	currentCommands.clear();
	}   
	memory.erase(--memory.end());

	fin.close();    

	checkAssembly();
}
