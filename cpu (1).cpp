#include "ram.h"
#include "cpu.h"

#include <iostream>
#include <iterator>
#include <unordered_map>


std::unordered_map<std::string, Cpu::Register> Cpu::registers;    

void Cpu::jle(std::vector<std::string> currentCommand, Ram& ram) {
	
	std::string data = (registers["1100"]).GetData();
	if(data != "JLE" || data != "JE") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::jl(std::vector<std::string> currentCommand, Ram& ram) {
	
	std::string data = (registers["1100"]).GetData();
	if(data != "JL") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::jg(std::vector<std::string> currentCommand, Ram& ram) {
	
	std::string data = (registers["1100"]).GetData();
	if(data != "JG") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}


void Cpu::jge(std::vector<std::string> currentCommand, Ram& ram) {
	
	std::string data = (registers["1100"]).GetData();
	if(data != "JGE" || data != "JE") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::je(std::vector<std::string> currentCommand, Ram& ram) {
	
	std::string data = (registers["1100"]).GetData();
	if(data != "JE") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}


void Cpu::move(std::vector<std::string> currentCommand) {
	
	std::string data = currentCommand[2];
	auto dataPosition = registers.find(data);
	if (dataPosition == registers.end()) {	
		registers[currentCommand[1]].SetData(data);
	} else
		registers[currentCommand[1]].SetData(registers[currentCommand[2]].GetData());
}

void Cpu::print(std::vector<std::string> currentCommand) {

	std::string data = currentCommand[1];
	auto dataPosition = registers.find(data);
	if (dataPosition == registers.end()) {	
		std::cout << currentCommand[1];
	} else
		std::cout << " " << registers[currentCommand[1]].GetData();

} 


void Cpu::ReadFromRam(Ram& ram) {

    using fptr = void(Cpu::*)(std::vector<std::string>);	
    using fptr2 = void(Cpu::*)(std::vector<std::string>, Ram&);
    
    stackPointer = ram.memory.begin();
 
    for (; stackPointer != ram.memory.end(); ++stackPointer) {
     	std::string commandName = (*stackPointer).second[0];

	
	auto checkJumpCommand = jumpCommands.find(commandName);
	if (checkJumpCommand != jumpCommands.end()) {
		fptr2 function = jumpCommands[commandName];
		(this->*function)((*stackPointer).second, ram);	
		continue;	
	}

	auto checkCommand = commands.find(commandName);
	if (checkCommand != commands.end()) {	
	fptr function = commands[commandName];
	(this->*function)((*stackPointer).second);
	continue;
	}
	labels.emplace((*stackPointer).second[0], stackPointer->first);
    }

}

