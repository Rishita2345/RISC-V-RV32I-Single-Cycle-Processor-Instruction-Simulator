#include <iostream>
#include <iomanip>

#include "../src/risc_v_core.hh"

void Decode_Instruction(
    instruction_t instruction,
    reg_t &rs1,
    reg_t &rs2,
    reg_t &rd,
    uint8_t &funct3,
    uint8_t &funct7,
    uint8_t &opcode
);

int main()
{
    /*
        ADD x5, x6, x7

        Encoding:
        funct7 = 0000000
        rs2    = 00111 = 7
        rs1    = 00110 = 6
        funct3 = 000
        rd     = 00101 = 5
        opcode = 0110011
    */

    uint32_t instruction = 0x007302B3;

    reg_t rs1;
    reg_t rs2;
    reg_t rd;

    uint8_t funct3;
    uint8_t funct7;
    uint8_t opcode;

    Decode_Instruction(
        instruction,
        rs1,
        rs2,
        rd,
        funct3,
        funct7,
        opcode
    );

    std::cout << "Instruction = 0x"
              << std::hex
              << instruction
              << std::endl;

    std::cout << std::dec;

    std::cout << "rs1    = x" << (int)rs1 << std::endl;
    std::cout << "rs2    = x" << (int)rs2 << std::endl;
    std::cout << "rd     = x" << (int)rd << std::endl;

    std::cout << "funct3 = 0x"
              << std::hex
              << (int)funct3
              << std::endl;

    std::cout << "funct7 = 0x"
              << (int)funct7
              << std::endl;

    std::cout << "opcode = 0x"
              << (int)opcode
              << std::endl;

    return 0;
}