#include "risc_v_core.hh"

static instruction_t program_memory[64] = {0};

void Load_Instruction(
    uint32_t index,
    instruction_t instruction
)
{
    if (index < 64)
    {
        program_memory[index] = instruction;
    }
}

instruction_t Instruction_Memory(PC_t address)
{
    uint32_t index = address / 4;

    if (index < 64)
    {
        return program_memory[index];
    }

    return 0;
}