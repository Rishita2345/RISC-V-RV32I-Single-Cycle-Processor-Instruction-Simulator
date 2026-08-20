#include <iostream>

#include "../src/risc_v_core.hh"

void ALU_Unit(
    data_t SrcAE,
    data_t SrcBE,
    uint8_t ALUControlE,
    bool &ZEROE,
    data_t &ALUResultE
);

int main()
{
    data_t result;
    bool zero;


    // =========================
    // TEST 1: ADD
    // =========================

    ALU_Unit(
        10,
        20,
        0b000,
        zero,
        result
    );

    std::cout << "ADD: "
              << result
              << "  ZERO = "
              << zero
              << std::endl;


    // =========================
    // TEST 2: SUB
    // =========================

    ALU_Unit(
        20,
        10,
        0b001,
        zero,
        result
    );

    std::cout << "SUB: "
              << result
              << "  ZERO = "
              << zero
              << std::endl;


    // =========================
    // TEST 3: SUB equal
    // =========================

    ALU_Unit(
        20,
        20,
        0b001,
        zero,
        result
    );

    std::cout << "SUB equal: "
              << result
              << "  ZERO = "
              << zero
              << std::endl;


    // =========================
    // TEST 4: AND
    // =========================

    ALU_Unit(
        0b1010,
        0b1100,
        0b010,
        zero,
        result
    );

    std::cout << "AND: "
              << result
              << std::endl;


    // =========================
    // TEST 5: OR
    // =========================

    ALU_Unit(
        0b1010,
        0b1100,
        0b011,
        zero,
        result
    );

    std::cout << "OR: "
              << result
              << std::endl;


    // =========================
    // TEST 6: SLT
    // =========================

    ALU_Unit(
        5,
        10,
        0b101,
        zero,
        result
    );

    std::cout << "SLT (5 < 10): "
              << result
              << std::endl;


    // =========================
    // TEST 7: SLT false
    // =========================

    ALU_Unit(
        20,
        10,
        0b101,
        zero,
        result
    );

    std::cout << "SLT (20 < 10): "
              << result
              << std::endl;


    return 0;
}