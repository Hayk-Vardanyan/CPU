#ifndef _CPU_H
#define _CPU_H

#include "ram.h"

#include <unordered_map>
#include <map>
#include <vector>
#include <iterator>


class Cpu {   
public:
    Cpu() { setCommands(); }
    		void ReadFromRam(Ram&);
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
    
class Alu
{
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
};

    std::map<std::string, std::vector<std::string>>::iterator stackPointer;
    std::unordered_map<std::string,void(Cpu::*)(const std::vector<std::string>&)> commands;
    std::unordered_map<std::string,void(Cpu::*)(const std::vector<std::string>&, Ram&)> jumpCommands;
    std::unordered_map<std::string,std::string> labels;    
    
    class Register {
    public:
	std::string getData() const {return _data;}
	void setData(std::string data) {_data = data;}
    private:
	std::string _data;	
    };

	Alu alu;
    	std::unordered_map<std::string, Register> registers;    
};

#endif // _CPU_H
