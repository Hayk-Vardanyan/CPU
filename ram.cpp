#include "ram.h"


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
}
