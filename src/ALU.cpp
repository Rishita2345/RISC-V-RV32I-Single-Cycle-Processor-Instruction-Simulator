#include "risc_v_core.hh"

void ALU_Unit(
    data_t SrcAE,
    data_t SrcBE,
    uint8_t ALUControlE,
    bool &ZEROE,
    data_t &ALUResultE
)
{
    data_t result = 0;

    switch (ALUControlE)
    {
        case 0b000:       // ADD
            result = SrcAE + SrcBE;
            break;

        case 0b001:       // SUB
            result = SrcAE - SrcBE;
            break;

        case 0b010:       // AND
            result = SrcAE & SrcBE;
            break;

        case 0b011:       // OR
            result = SrcAE | SrcBE;
            break;

        case 0b101:       // SLT
            if (SrcAE < SrcBE)
                result = 1;
            else
                result = 0;
            break;

        default:
            result = 0;
            break;
    }

    ALUResultE = result;

    // Zero flag
    if (ALUControlE == 0b001)
    {
        // SUB operation
        ZEROE = (SrcAE == SrcBE);
    }
    else
    {
        ZEROE = (ALUResultE == 0);
    }
}