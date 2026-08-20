#include <iostream>

#include "../src/risc_v_core.hh"

void Data_Memory(
    bool MemWrite,
    PC_t address,
    data_t WriteData,
    data_t &ReadData
);

int main()
{
    data_t ReadData;

    // ==================================
    // TEST 1: Write 100 to address 20
    // ==================================

    Data_Memory(
        true,      // MemWrite
        20,        // address
        100,       // WriteData
        ReadData
    );

    std::cout << "Wrote 100 to address 20"
              << std::endl;


    // ==================================
    // TEST 2: Read address 20
    // ==================================

    Data_Memory(
        false,
        20,
        0,
        ReadData
    );

    std::cout << "Read address 20 = "
              << ReadData
              << std::endl;


    // ==================================
    // TEST 3: Write 200 to address 40
    // ==================================

    Data_Memory(
        true,
        40,
        200,
        ReadData
    );

    std::cout << "Wrote 200 to address 40"
              << std::endl;


    // ==================================
    // TEST 4: Read address 40
    // ==================================

    Data_Memory(
        false,
        40,
        0,
        ReadData
    );

    std::cout << "Read address 40 = "
              << ReadData
              << std::endl;


    // ==================================
    // TEST 5: Make sure address 20
    // still contains 100
    // ==================================

    Data_Memory(
        false,
        20,
        0,
        ReadData
    );

    std::cout << "Read address 20 again = "
              << ReadData
              << std::endl;


    return 0;
}