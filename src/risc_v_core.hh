#ifndef RISC_V_CORE_HH
#define RISC_V_CORE_HH

#include <cstdint>
#include <string>

typedef uint32_t data_t;
typedef uint32_t instruction_t;
typedef uint32_t PC_t;

typedef uint8_t reg_t;
typedef uint8_t address_t;

bool RISC_V_Core(
    bool reset,
    data_t &ALUResult
);

void Load_Instruction(
    uint32_t index,
    instruction_t instruction
);

uint32_t AssembleInstruction(
    const std::string &line
);

#endif