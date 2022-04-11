#ifndef _ALU_H
#define _ALU_H

#include <vector>
#include <iostream>


class Alu
{
protected:
	Alu() = default;
	void AluAdd(std::vector<std::string>);
	void AluSub(std::vector<std::string>);
	void AluDiv(std::vector<std::string>);
	void AluMul(std::vector<std::string>);
	void AluCmp(std::vector<std::string>);
	
	int ToDecimal(std::string);
	std::string ToBinary(int);	
};

#endif
