#include "risc_v_core.hh"

void Decode_Instruction(
    instruction_t instruction,
    reg_t &rs1,
    reg_t &rs2,
    reg_t &rd,
    uint8_t &funct3,
    uint8_t &funct7,
    uint8_t &opcode
)
{
    uint32_t instr =
        static_cast<uint32_t>(instruction);

    // Extract fields

    opcode = instr & 0x7F;

    rd = (instr >> 7) & 0x1F;

    funct3 = (instr >> 12) & 0x07;

    rs1 = (instr >> 15) & 0x1F;

    rs2 = (instr >> 20) & 0x1F;

    funct7 = (instr >> 25) & 0x7F;
}