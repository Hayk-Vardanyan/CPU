#ifndef _CPU_H
#define _CPU_H

#include "ram.h"

#include <iterator>
#include <iostream>

class Cpu {   
public:
    Cpu() { setCommands(); }
    bool ReadFromRam(Ram&);
private:
    void setCommands();
private:
    void move(const std::vector<std::string>&);
    void print(const std::vector<std::string>&);
    void addition(const std::vector<std::string>&);	    
    void subtraction(const std::vector<std::string>&);
    void division(const std::vector<std::string>&);
    void multiply(const std::vector<std::string>&);
    void compare(const std::vector<std::string>& currentCommand);
    void jumpLessEqual(const std::vector<std::string>& currentCommand, Ram&);
    void jumpLess(const std::vector<std::string>& currentCommand, Ram&);
    void jumpGreat(const std::vector<std::string>& currentCommand, Ram&);
    void jumpGreatEqual(const std::vector<std::string>& currentCommand, Ram&);
    void jumpEqual(const std::vector<std::string>& currentCommand, Ram&);

private:
    
	class Alu {
	public:
		Alu() = default;
		std::string addTwoBinary(const std::string&, const std::string&) const;
		std::string subTwoBinary(const std::string&, const std::string&) const;
		std::string divTwoBinary(const std::string&, const std::string&) const;
		std::string mulTwoBinary(const std::string&, const std::string&) const;
		std::string cmpTwoBinary(const std::string&, const std::string&) const;
	private:	
		int toDecimal(const std::string&) const;
		std::string toBinary(int) const;	
	}; // Alu

    std::map<std::string, std::vector<std::string>>::iterator stackPointer;
    std::unordered_map<std::string,void(Cpu::*)(const std::vector<std::string>&)> commands;
    std::unordered_map<std::string,void(Cpu::*)(const std::vector<std::string>&, Ram&)> jumpCommands;
    std::unordered_map<std::string,std::string> labels;    
    
    class Register {
    public:
	std::string getData() const { return data; }
	void setData(const std::string& data) {
		this->data = data;
	}
    private:
	std::string data;	
    }; // Register

	Alu alu;
    	std::unordered_map<std::string, Register> registers;    
}; // Cpu

#endif // _CPU_H
