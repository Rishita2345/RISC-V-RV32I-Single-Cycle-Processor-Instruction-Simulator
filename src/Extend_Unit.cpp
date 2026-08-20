#include "risc_v_core.hh"

data_t Extend_Immediate(
    instruction_t instruction,
    uint8_t ImmSrc
)
{
    uint32_t instr = static_cast<uint32_t>(instruction);

    data_t immediate = 0;

    switch (ImmSrc)
    {
        // -------------------------
        // I-type
        // -------------------------
        case 0:

            immediate =
                static_cast<int32_t>(instr) >> 20;

            break;


        // -------------------------
        // S-type
        // -------------------------
        case 1:
        {
            uint32_t imm11_5 =
                (instr >> 25) & 0x7F;

            uint32_t imm4_0 =
                (instr >> 7) & 0x1F;

            uint32_t imm =
                (imm11_5 << 5) | imm4_0;

            // Sign extension
            if (imm & 0x800)
                imm |= 0xFFFFF000;

            immediate =
                static_cast<int32_t>(imm);

            break;
        }


        // -------------------------
        // B-type
        // -------------------------
        case 2:
        {
            uint32_t bit12 =
                (instr >> 31) & 0x1;

            uint32_t bit11 =
                (instr >> 7) & 0x1;

            uint32_t bits10_5 =
                (instr >> 25) & 0x3F;

            uint32_t bits4_1 =
                (instr >> 8) & 0xF;

            uint32_t imm =
                (bit12 << 12) |
                (bit11 << 11) |
                (bits10_5 << 5) |
                (bits4_1 << 1);

            if (imm & 0x1000)
                imm |= 0xFFFFE000;

            immediate =
                static_cast<int32_t>(imm);

            break;
        }


        default:
            immediate = 0;
            break;
    }

    return immediate;
}