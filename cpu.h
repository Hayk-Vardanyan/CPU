#include "ram.h"
#include "alu.h"

#include <unordered_map>
#include <map>
#include <vector>
#include <iterator>


class Cpu : private Alu {   
public:
    Cpu() {
		commands.emplace("1111", &Cpu::move);
		commands.emplace("1110", &Cpu::print);
		commands.emplace("1010", &Cpu::add);
		commands.emplace("0101", &Cpu::sub);
		commands.emplace("0011", &Cpu::div);
		commands.emplace("01111", &Cpu::mul);
		commands.emplace("011111", &Cpu::cmp);
		
		jumpCommands.emplace("00111", &Cpu::jle);		
		jumpCommands.emplace("00110", &Cpu::je);		
		jumpCommands.emplace("00101", &Cpu::jg);		
		jumpCommands.emplace("00001", &Cpu::jge);		
		jumpCommands.emplace("00100", &Cpu::jle);		

		registers.emplace("0001", Register());
		registers.emplace("0010", Register());
		registers.emplace("0100", Register());
		registers.emplace("1000", Register());
		registers.emplace("1100", Register()); // register EFL for CMP;
	}
    void ReadFromRam(Ram&);
private:
    friend class Alu;
    void move(std::vector<std::string>);
    void print(std::vector<std::string>);
    void add(std::vector<std::string> currentCommand) {AluAdd(currentCommand);}	    
    void sub(std::vector<std::string> currentCommand) {AluSub(currentCommand);}
    void div(std::vector<std::string> currentCommand) {AluDiv(currentCommand);}
    void mul(std::vector<std::string> currentCommand) {AluMul(currentCommand);}
    void cmp(std::vector<std::string> currentCommand) {AluCmp(currentCommand);}
    void jle(std::vector<std::string> currentCommand, Ram&);
    void jl(std::vector<std::string> currentCommand, Ram&);
    void jg(std::vector<std::string> currentCommand, Ram&);
    void jge(std::vector<std::string> currentCommand, Ram&);
    void je(std::vector<std::string> currentCommand, Ram&);
    
    std::map<std::string, std::vector<std::string>>::iterator stackPointer;
    std::unordered_map<std::string,void(Cpu::*)(std::vector<std::string>)> commands;
    std::unordered_map<std::string,void(Cpu::*)(std::vector<std::string>, Ram&)> jumpCommands;
    std::unordered_map<std::string,std::string> labels;    

    class Register;
    static std::unordered_map<std::string, Register> registers;    

    class Register {
    public:
	std::string GetData(){return _data;}
	void SetData(std::string data) {_data = data;}
    private:
	std::string _data;	

    };
};
