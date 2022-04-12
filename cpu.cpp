#include "ram.h"
#include "cpu.h"

#include <iostream>
#include <iterator>

void Cpu::setCommands() {
		commands.emplace("1111", &Cpu::move);
		commands.emplace("1110", &Cpu::print);
		commands.emplace("1010", &Cpu::addition);
		commands.emplace("0101", &Cpu::subtraction);
		commands.emplace("0011", &Cpu::division);
		commands.emplace("01111", &Cpu::multiply);
		commands.emplace("011111", &Cpu::compare);
		
		jumpCommands.emplace("00111", &Cpu::jumpLessEqual);		
		jumpCommands.emplace("00110", &Cpu::jumpEqual);		
		jumpCommands.emplace("00101", &Cpu::jumpGreat);		
		jumpCommands.emplace("00001", &Cpu::jumpGreatEqual);		
		jumpCommands.emplace("00100", &Cpu::jumpLess);		

		registers.emplace("0001", Register());
		registers.emplace("0010", Register());
		registers.emplace("0100", Register());
		registers.emplace("1000", Register());
		registers.emplace("1100", Register()); // register EFL for CMP;
}

void Cpu::compare(const std::vector<std::string>& currentCommand) {
	std::string data = currentCommand[2];
	std::string comparedNumber1{};
	std::string comparedNumber2{};
	
	auto dataPosition = registers.find(data);
	if (dataPosition == registers.end()) {
		comparedNumber2 = data;
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
	if (dataPosition == registers.end()) {	
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = currentCommand[2];		
		
		std::string binarySum = alu.addTwoBinary(number1, number2);	
		registers[currentCommand[1]].setData(binarySum);		

	} else {
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = registers[currentCommand[2]].getData();

		std::string binarySum = alu.addTwoBinary(number1, number2);
		registers[currentCommand[1]].setData(binarySum);
	}
}

void Cpu::subtraction(const std::vector<std::string>& currentCommand) { 
	auto dataPosition = registers.find(currentCommand[2]);
	if (dataPosition == registers.end()) {	
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = currentCommand[2];		
		
		std::string binarySub = alu.subTwoBinary(number1, number2);	
		registers[currentCommand[1]].setData(binarySub);		

	} else {
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = registers[currentCommand[2]].getData();

		std::string binarySub = alu.subTwoBinary(number1, number2);
		registers[currentCommand[1]].setData(binarySub);
	}
}

void Cpu::division(const std::vector<std::string>& currentCommand) { 
	auto dataPosition = registers.find(currentCommand[2]);
	if (dataPosition == registers.end()) {	
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = currentCommand[2];		
		
		std::string binaryDiv = alu.divTwoBinary(number1, number2);	
		registers[currentCommand[1]].setData(binaryDiv);		

	} else {
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = registers[currentCommand[2]].getData();

		std::string binaryDiv = alu.divTwoBinary(number1, number2);
		registers[currentCommand[1]].setData(binaryDiv);
	}
}

void Cpu::multiply(const std::vector<std::string>& currentCommand) { 
	auto dataPosition = registers.find(currentCommand[2]);
	if (dataPosition == registers.end()) {	
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = currentCommand[2];		
		
		std::string binaryMul = alu.mulTwoBinary(number1, number2);	
		registers[currentCommand[1]].setData(binaryMul);		

	} else {
		std::string number1 = (registers[currentCommand[1]].getData());
		std::string number2 = registers[currentCommand[2]].getData();

		std::string binaryMul = alu.mulTwoBinary(number1, number2);
		registers[currentCommand[1]].setData(binaryMul);
	}

}

std::string Cpu::Alu::toBinary(int decimalNum) const {
	std::string binaryNum;
	for (; decimalNum != 0; decimalNum /=2) {
		if(decimalNum%2 == 0) binaryNum = "0" + binaryNum;
		else binaryNum = "1" + binaryNum;
	}
	return binaryNum;
}

int Cpu::Alu::toDecimal(const std::string& binaryNum) const {
	int decimalNum{1};
	for (int i = 1; i < binaryNum.size(); ++i) {
		if (binaryNum[i] == '1') { 
			++(decimalNum *= 2);	
		} else {
			decimalNum *= 2;
		}
  	 }
	return decimalNum;
}

std::string Cpu::Alu::addTwoBinary(const std::string& number1,const std::string& number2) const {
	int decimalNumber1 = toDecimal(number1);
	int decimalNumber2 = toDecimal(number2);

	int decimalSummary = decimalNumber1 + decimalNumber2;
	std::string binarySummary = toBinary(decimalSummary);
	return binarySummary;
}

std::string Cpu::Alu::subTwoBinary(const std::string& number1,const std::string& number2) const {
	int decimalNumber1 = toDecimal(number1);
	int decimalNumber2 = toDecimal(number2);

	int decimalSubtraction = decimalNumber1 - decimalNumber2;
	std::string binarySubtraction = toBinary(decimalSubtraction);
	return binarySubtraction;
}

std::string Cpu::Alu::divTwoBinary(const std::string& number1,const std::string& number2) const {
	int decimalNumber1 = toDecimal(number1);
	int decimalNumber2 = toDecimal(number2);

	int decimalSubtraction = decimalNumber1 / decimalNumber2;
	std::string binarySubtraction = toBinary(decimalSubtraction);
	return binarySubtraction;
}

std::string Cpu::Alu::mulTwoBinary(const std::string& number1,const std::string& number2) const {
	int decimalNumber1 = toDecimal(number1);
	int decimalNumber2 = toDecimal(number2);

	int decimalSubtraction = decimalNumber1 * decimalNumber2;
	std::string binarySubtraction = toBinary(decimalSubtraction);
	return binarySubtraction;
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
	std::string data = currentCommand[2];
	auto dataPosition = registers.find(data);
	if (dataPosition == registers.end()) {	
		registers[currentCommand[1]].setData(data);
	} else
		registers[currentCommand[1]].setData(registers[currentCommand[2]].getData());
}

void Cpu::print(const std::vector<std::string>& currentCommand) {
	std::string data = currentCommand[1];
	auto dataPosition = registers.find(data);
	if (dataPosition == registers.end()) {	
		std::cout << currentCommand[1];
	} else
		std::cout << " " << registers[currentCommand[1]].getData();
} 

void Cpu::ReadFromRam(Ram& ram) {
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
	std::string label = (*(stackPointer)).second[0];
	label.pop_back();
	labels.emplace(label, stackPointer->first);
    }
}

