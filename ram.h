#ifndef _RAM_H
#define _RAM_H

#include <map>
#include <vector>
#include <fstream>
#include <sstream>

class Ram
{
public: 
    Ram();
    void FillMemory(const std::string&);
    friend class Cpu;
    std::ifstream fin;

public:
    std::map<std::string, std::vector<std::string>> memory;
    std::vector<std::string> addresses;
};




#endif
