#include <iostream>
#include "../src/risc_v_core.hh"

int main()
{
    std::cout << std::hex;

    std::cout << "ADDI: "
              << AssembleInstruction("addi x5, x0, 10")
              << std::endl;

    std::cout << "ADDI: "
              << AssembleInstruction("addi x6, x0, 20")
              << std::endl;

    std::cout << "ADD: "
              << AssembleInstruction("add x7, x5, x6")
              << std::endl;

    std::cout << "SUB: "
              << AssembleInstruction("sub x8, x6, x5")
              << std::endl;

    return 0;
}