#include <iostream>

#include "../src/risc_v_core.hh"

instruction_t Instruction_Memory(PC_t address);

int main()
{
    instruction_t instruction;

    instruction = Instruction_Memory(0);

    std::cout << "PC = 0x00000000"
              << "  Instruction = 0x"
              << std::hex << instruction
              << std::endl;

    instruction = Instruction_Memory(4);

    std::cout << "PC = 0x00000004"
              << "  Instruction = 0x"
              << std::hex << instruction
              << std::endl;

    instruction = Instruction_Memory(8);

    std::cout << "PC = 0x00000008"
              << "  Instruction = 0x"
              << std::hex << instruction
              << std::endl;

    instruction = Instruction_Memory(12);

    std::cout << "PC = 0x0000000C"
              << "  Instruction = 0x"
              << std::hex << instruction
              << std::endl;

    return 0;
}