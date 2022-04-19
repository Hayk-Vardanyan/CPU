#include "cpu.h"

int main()
{
    Ram ram;
    std::string path;
    std::cout << "Enter the name of file to read from\n";
    std::cin >> path;
    if(ram.fillMemory(path)) {
    	Cpu cpu;
    	if(!cpu.ReadFromRam(ram)) std::cout << "unkown command\n";
    }
    else {
		std::cout << "failed to fill memory\n";
	}	
}
