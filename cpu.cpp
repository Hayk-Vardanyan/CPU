#include "ram.h"
#include "cpu.h"
#include <iostream>
#include <iterator>

void Cpu::setCommands() {
	commands.emplace("0000001", &Cpu::move);
	commands.emplace("0000010", &Cpu::print);
	commands.emplace("0000100", &Cpu::addition);
	commands.emplace("0001000", &Cpu::subtraction);
	commands.emplace("0010000", &Cpu::division);
	commands.emplace("0001100", &Cpu::multiply);
	commands.emplace("0010100", &Cpu::compare);
		
	jumpCommands.emplace("000111", &Cpu::jumpLessEqual);		
	jumpCommands.emplace("000110", &Cpu::jumpEqual);		
	jumpCommands.emplace("000101", &Cpu::jumpGreat);		
	jumpCommands.emplace("000001", &Cpu::jumpGreatEqual);		
	jumpCommands.emplace("000100", &Cpu::jumpLess);		

	registers.emplace("00001", Register());
	registers.emplace("00010", Register());
	registers.emplace("00100", Register());
	registers.emplace("00110", Register());
	registers.emplace("1100", Register()); // register EFL for CMP;
}

void Cpu::compare(const std::vector<std::string>& currentCommand) {
	std::string data = currentCommand[2];
	std::string comparedNumber1{};
	std::string comparedNumber2{};
	
	auto dataPosition = registers.find(data);
	if (dataPosition == registers.end()) {
		comparedNumber2 = currentCommand[2];
	}
	else {
		comparedNumber2 = (registers[currentCommand[2]]).getData();
	}
	comparedNumber1 = (registers[currentCommand[1]]).getData();

	const std::string cmpStatus = alu.cmpTwoBinary(comparedNumber1, comparedNumber2);
	(registers["1100"]).setData(cmpStatus);
}

std::string Cpu::Alu::cmpTwoBinary(const std::string& number1, const std::string& number2) const {
	int decimalNumber1 = toDecimal(number1);
	int decimalNumber2 = toDecimal(number2);
	std::string cmpStatus{};
	if (decimalNumber1 > decimalNumber2) {
		cmpStatus = "JG";
	} else if (decimalNumber1 < decimalNumber2) {
		cmpStatus = "JL";
	} else {
		cmpStatus = "JE";
	}
	return cmpStatus;
}

void Cpu::addition(const std::vector<std::string>& currentCommand) { 
	auto dataPosition = registers.find(currentCommand[2]);
	std::string number2{};

	if (dataPosition == registers.end()) {	
		number2 = currentCommand[2];		
	} else {
		number2 = registers[currentCommand[2]].getData();
	}
		registers[currentCommand[1]].setData(alu.addTwoBinary(registers[currentCommand[1]].getData(), number2));
}

void Cpu::subtraction(const std::vector<std::string>& currentCommand) { 
	auto dataPosition = registers.find(currentCommand[2]);
	std::string number2{};

	if (dataPosition == registers.end()) {	
		number2 = currentCommand[2];		
	} else {
		number2 = registers[currentCommand[2]].getData();
	}
		registers[currentCommand[1]].setData(alu.subTwoBinary(registers[currentCommand[1]].getData(), number2));
}

void Cpu::division(const std::vector<std::string>& currentCommand) {  
	auto dataPosition = registers.find(currentCommand[2]);
	std::string number2{};

	if (dataPosition == registers.end()) {	
		number2 = currentCommand[2];		
	} else {
		number2 = registers[currentCommand[2]].getData();
	}
		registers[currentCommand[1]].setData(alu.divTwoBinary(registers[currentCommand[1]].getData(), number2));
}

void Cpu::multiply(const std::vector<std::string>& currentCommand) { 
	auto dataPosition = registers.find(currentCommand[2]);
	std::string number2{};

	if (dataPosition == registers.end()) {	
		number2 = currentCommand[2];		
	} else {
		number2 = registers[currentCommand[2]].getData();
	}
		registers[currentCommand[1]].setData(alu.mulTwoBinary(registers[currentCommand[1]].getData(), number2));
}

std::string Cpu::Alu::toBinary(int decimalNum) const {
	std::string binaryNum;
	bool negative{};
	if (decimalNum < 0) {
		negative = true;
	}

	for (; decimalNum != 0; decimalNum /= 2) {
		if (decimalNum%2 == 0) {
			binaryNum = "0" + binaryNum;
		} else {
			binaryNum = "1" + binaryNum; 
		}
	}
	if (negative) {
		binaryNum = "1" + binaryNum;
	} else {
		binaryNum = "0" + binaryNum; 
	}
	return binaryNum;
}

int Cpu::Alu::toDecimal(const std::string& binaryNum) const {
	if (binaryNum == "0") { return 0; }
	int decimalNum{1};
	for (int i = 2; i < binaryNum.size(); ++i) {
		if (binaryNum[i] == '1') { 
			++(decimalNum *= 2);	
		} else {
			decimalNum *= 2;
		}
  	 }
	if (binaryNum[0] == '1') {
		decimalNum = decimalNum - 2 * decimalNum;
	}
	return decimalNum;
}

std::string Cpu::Alu::addTwoBinary(const std::string& number1,const std::string& number2) const {
	return toBinary(toDecimal(number1) + toDecimal(number2));
}

std::string Cpu::Alu::subTwoBinary(const std::string& number1,const std::string& number2) const {
	return toBinary(toDecimal(number1) - toDecimal(number2));
}

std::string Cpu::Alu::divTwoBinary(const std::string& number1,const std::string& number2) const {
	return toBinary(toDecimal(number1) / toDecimal(number2));
}

std::string Cpu::Alu::mulTwoBinary(const std::string& number1,const std::string& number2) const {
	return toBinary(toDecimal(number1) * toDecimal(number2));
}

void Cpu::jumpLessEqual(const std::vector<std::string>& currentCommand, Ram& ram) {	
	std::string data = (registers["1100"]).getData();
	if(data != "JL" && data != "JE") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::jumpLess(const std::vector<std::string>& currentCommand, Ram& ram) {
	std::string data = (registers["1100"]).getData();
	if(data != "JL") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::jumpGreat(const std::vector<std::string>& currentCommand, Ram& ram) {
	std::string data = (registers["1100"]).getData();
	if(data != "JG") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::jumpGreatEqual(const std::vector<std::string>& currentCommand, Ram& ram) {
	std::string data = (registers["1100"]).getData();
	if(data != "JG" && data != "JE") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::jumpEqual(const std::vector<std::string>& currentCommand, Ram& ram) {
	std::string data = (registers["1100"]).getData();
	if(data != "JE") return;
	
	auto labelAddress = labels[currentCommand[1]];
	stackPointer = ram.memory.find(labelAddress);
}

void Cpu::move(const std::vector<std::string>& currentCommand) {
	auto dataPosition = registers.find(currentCommand[2]);
	if (dataPosition == registers.end()) {	
		registers[currentCommand[1]].setData(currentCommand[2]);
	} else {
		registers[currentCommand[1]].setData(registers[currentCommand[2]].getData());
	}
}

void Cpu::print(const std::vector<std::string>& currentCommand) {
	auto dataPosition = registers.find(currentCommand[1]);
	if (dataPosition == registers.end()) {	
		std::cout << currentCommand[1];
	} else {
		std::cout << " " << registers[currentCommand[1]].getData() << '\n';
	}		
} 

bool Cpu::ReadFromRam(Ram& ram) {
    using fptr = void(Cpu::*)(const std::vector<std::string>&);	
    using fptr2 = void(Cpu::*)(const std::vector<std::string>&, Ram&);
    
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
	else if(checkCommand == commands.end() && (*stackPointer).second[0][(*stackPointer).second[0].size()-1] == ':') {
		std::string label = (*(stackPointer)).second[0];
		label.pop_back();
		labels.emplace(label, stackPointer->first);
		continue;
	}
	else if(commandName == "0") continue;
	else {
		std::cout << commandName << " ";
		return false;
	}
	
    }
	return true;
}
