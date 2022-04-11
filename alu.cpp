#include "alu.h"
#include "cpu.h"


std::string Alu::ToBinary(int decimalNum) {

	std::string binaryNum;
	for (; decimalNum != 0; decimalNum /=2) {
		if(decimalNum%2 == 0) binaryNum = "0" + binaryNum;
		else binaryNum = "1" + binaryNum;
	}
	return binaryNum;
}

int Alu::ToDecimal(std::string binaryNum) {
	
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

void Alu::AluAdd(std::vector<std::string> currentCommand) {

	auto dataPosition = Cpu::registers.find(currentCommand[2]);
	if (dataPosition == Cpu::registers.end()) {	
		int decimalSum = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) + (ToDecimal(currentCommand[2]));
		std::string binarySum = ToBinary(decimalSum);	
		Cpu::registers[currentCommand[1]].SetData(binarySum);		

	} else {
int decimalSum = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) + ToDecimal(Cpu::registers[currentCommand[2]].GetData());
		std::string binarySum = ToBinary(decimalSum);
		Cpu::registers[currentCommand[1]].SetData(binarySum);
	}
}
void Alu::AluSub(std::vector<std::string> currentCommand) {

	auto dataPosition = Cpu::registers.find(currentCommand[2]);
	if (dataPosition == Cpu::registers.end()) {	
		int decimalDif = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) - (ToDecimal(currentCommand[2]));
		std::string binaryDif = ToBinary(decimalDif);	
		Cpu::registers[currentCommand[1]].SetData(binaryDif);		

	} else {
int decimalDif = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) - ToDecimal(Cpu::registers[currentCommand[2]].GetData());
		std::string binaryDif = ToBinary(decimalDif);
		Cpu::registers[currentCommand[1]].SetData(binaryDif);
	}
	
}

void Alu::AluDiv(std::vector<std::string> currentCommand) {

	auto dataPosition = Cpu::registers.find(currentCommand[2]);
	if (dataPosition == Cpu::registers.end()) {	
		int decimalDiv = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) / (ToDecimal(currentCommand[2]));
		std::string binaryDiv = ToBinary(decimalDiv);	
		Cpu::registers[currentCommand[1]].SetData(binaryDiv);		

	} else {
int decimalDiv = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) - ToDecimal(Cpu::registers[currentCommand[2]].GetData());
		std::string binaryDiv = ToBinary(decimalDiv);
		Cpu::registers[currentCommand[1]].SetData(binaryDiv);
	}
	
}

void Alu::AluMul(std::vector<std::string> currentCommand) {

	auto dataPosition = Cpu::registers.find(currentCommand[2]);
	if (dataPosition == Cpu::registers.end()) {	
		int decimalMul = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) * (ToDecimal(currentCommand[2]));
		std::string binaryMul = ToBinary(decimalMul);	
		Cpu::registers[currentCommand[1]].SetData(binaryMul);		

	} else {
int decimalMul = ToDecimal(Cpu::registers[currentCommand[1]].GetData()) * ToDecimal(Cpu::registers[currentCommand[2]].GetData());
		std::string binaryMul = ToBinary(decimalMul);
		Cpu::registers[currentCommand[1]].SetData(binaryMul);
	}
	
}


void Alu::AluCmp(std::vector<std::string> currentCommand) {

	std::string data = currentCommand[2];
	int comparedNumber1{};
	int comparedNumber2{};
	
	auto dataPosition = Cpu::registers.find(data);
	if (dataPosition == Cpu::registers.end()) {
		comparedNumber2 = ToDecimal(data);
	}
	else {
		comparedNumber2 = ToDecimal((Cpu::registers[currentCommand[2]]).GetData());
	}
	comparedNumber1 = ToDecimal((Cpu::registers[currentCommand[1]]).GetData());


	if (comparedNumber1 < comparedNumber2) {
		(Cpu::registers["1100"]).SetData("JE");
	} else if (comparedNumber1 <= comparedNumber2) {
		(Cpu::registers["1100"]).SetData("JL");
	} else if (comparedNumber1 == comparedNumber2) {
		(Cpu::registers["1100"]).SetData("JE");
	} else if (comparedNumber1 > comparedNumber2) {
		(Cpu::registers["1100"]).SetData("JG");
	} else if (comparedNumber1 >= comparedNumber2) {
		(Cpu::registers["1100"]).SetData("JGE");	
	}
}
