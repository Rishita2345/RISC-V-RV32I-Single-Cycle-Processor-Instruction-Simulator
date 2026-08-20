#include <iostream>

#include "../src/risc_v_core.hh"

data_t Extend_Immediate(
    instruction_t instruction,
    uint8_t ImmSrc
);

int main()
{
    // -------------------------
    // I-type test
    // -------------------------

    // ADDI x5, x6, 10
    uint32_t addi =
        0x00A30293;

    data_t imm =
        Extend_Immediate(addi, 0);

    std::cout << "I-type immediate = "
              << imm
              << std::endl;


    // -------------------------
    // I-type negative test
    // -------------------------

    // Immediate = -1
    uint32_t negative =
        0xFFF30293;

    imm =
        Extend_Immediate(negative, 0);

    std::cout << "Negative immediate = "
              << imm
              << std::endl;


    return 0;
}