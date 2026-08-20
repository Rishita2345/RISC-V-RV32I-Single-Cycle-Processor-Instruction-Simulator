#include <iostream>
#include "../src/risc_v_core.hh"

// Declaration of the Program Counter function
PC_t Program_Counter(
    PC_t pc_current,
    bool reset,
    bool PCSrc,
    PC_t pc_target
);

int main()
{
    PC_t pc;

    // -------------------------
    // Test 1: Reset
    // -------------------------
    pc = Program_Counter(100, true, false, 200);

    std::cout << "Test 1 - Reset: ";
    std::cout << pc << std::endl;


    // -------------------------
    // Test 2: Normal PC + 4
    // -------------------------
    pc = Program_Counter(0, false, false, 100);

    std::cout << "Test 2 - PC + 4: ";
    std::cout << pc << std::endl;


    // -------------------------
    // Test 3: Another PC + 4
    // -------------------------
    pc = Program_Counter(4, false, false, 100);

    std::cout << "Test 3 - PC + 4: ";
    std::cout << pc << std::endl;


    // -------------------------
    // Test 4: Branch / Jump
    // -------------------------
    pc = Program_Counter(8, false, true, 100);

    std::cout << "Test 4 - Branch Target: ";
    std::cout << pc << std::endl;


    return 0;
}