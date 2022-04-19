#ifndef _RAM_H
#define _RAM_H

#include <map>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

class Ram
{
public: 
    Ram();
    bool fillMemory(const std::string&);
    friend class Cpu;
    std::ifstream read;
private:
    int stoi(std::string&);
    bool generateBinaryCode();
    bool checkNumber(std::string&);
    void setAssemblyAndBinaryCommands();
    std::map<std::string, std::vector<std::string>> memory;
    std::vector<std::string> addresses;
    std::unordered_map<std::string, std::string> assemblyAndBinaryCommands;
};

#endif // _RAM_H
