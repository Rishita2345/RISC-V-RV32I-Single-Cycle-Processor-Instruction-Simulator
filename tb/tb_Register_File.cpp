#include <iostream>

#include "../src/risc_v_core.hh"

// Register File declaration
void Register_File(
    bool WE3,
    reg_t A1,
    reg_t A2,
    reg_t A3,
    data_t WD3,
    data_t &RD1_D,
    data_t &RD2_D
);

int main()
{
    data_t RD1;
    data_t RD2;

    // --------------------------------
    // Test 1: Write 100 into x5
    // --------------------------------

    Register_File(
        true,       // WE3
        0,          // A1
        0,          // A2
        5,          // A3 = x5
        100,        // WD3
        RD1,
        RD2
    );

    std::cout << "Wrote 100 into x5" << std::endl;


    // --------------------------------
    // Test 2: Read x5
    // --------------------------------

    Register_File(
        false,
        5,
        0,
        0,
        0,
        RD1,
        RD2
    );

    std::cout << "Read x5 = "
              << RD1 << std::endl;


    // --------------------------------
    // Test 3: Write 200 into x10
    // --------------------------------

    Register_File(
        true,
        0,
        0,
        10,
        200,
        RD1,
        RD2
    );

    std::cout << "Wrote 200 into x10" << std::endl;


    // --------------------------------
    // Test 4: Read x5 and x10
    // --------------------------------

    Register_File(
        false,
        5,
        10,
        0,
        0,
        RD1,
        RD2
    );

    std::cout << "RD1 (x5)  = "
              << RD1 << std::endl;

    std::cout << "RD2 (x10) = "
              << RD2 << std::endl;


    // --------------------------------
    // Test 5: x0 must always be zero
    // --------------------------------

    Register_File(
        true,
        0,
        0,
        0,
        999,
        RD1,
        RD2
    );

    Register_File(
        false,
        0,
        0,
        0,
        0,
        RD1,
        RD2
    );

    std::cout << "x0 = "
              << RD1 << std::endl;


    return 0;
}