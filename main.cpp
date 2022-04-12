#include "cpu.h"

int main()
{
    Ram ram;
    ram.FillMemory("cpu.txt");
    Cpu cpu;
    cpu.ReadFromRam(ram);
}
