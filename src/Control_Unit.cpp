#include "risc_v_core.hh"

void Control_Unit(
    uint8_t opcode,
    uint8_t funct3,
    uint8_t funct7,

    bool &RegWrite,
    bool &MemWrite,
    bool &MemToReg,
    bool &ALUSrc,
    bool &Branch,

    uint8_t &ALUControl,
    uint8_t &ImmSrc
)
{
    // Default values
    RegWrite = false;
    MemWrite = false;
    MemToReg = false;
    ALUSrc = false;
    Branch = false;

    ALUControl = 0b000; // ADD
    ImmSrc = 0;

    // ==========================================
    // R-TYPE INSTRUCTIONS
    // ADD, SUB, AND, OR, SLT
    // opcode = 0110011 = 0x33
    // ==========================================

    if (opcode == 0x33)
    {
        RegWrite = true;
        ALUSrc = false;
        MemToReg = false;

        if (funct3 == 0b000)
        {
            if (funct7 == 0b0000000)
            {
                // ADD
                ALUControl = 0b000;
            }
            else if (funct7 == 0b0100000)
            {
                // SUB
                ALUControl = 0b001;
            }
        }
        else if (funct3 == 0b111)
        {
            // AND
            ALUControl = 0b010;
        }
        else if (funct3 == 0b110)
        {
            // OR
            ALUControl = 0b011;
        }
        else if (funct3 == 0b010)
        {
            // SLT
            ALUControl = 0b101;
        }
    }


    // ==========================================
    // I-TYPE ALU INSTRUCTIONS
    // ADDI
    // opcode = 0010011 = 0x13
    // ==========================================

    else if (opcode == 0x13)
    {
        RegWrite = true;
        ALUSrc = true;
        MemToReg = false;
        ImmSrc = 0;

        if (funct3 == 0b000)
        {
            // ADDI
            ALUControl = 0b000;
        }
    }


    // ==========================================
    // LOAD
    // LW
    // opcode = 0000011 = 0x03
    // ==========================================

    else if (opcode == 0x03)
    {
        RegWrite = true;

        MemWrite = false;

        MemToReg = true;

        ALUSrc = true;

        ImmSrc = 0;

        // Address calculation
        ALUControl = 0b000;
    }


    // ==========================================
    // STORE
    // SW
    // opcode = 0100011 = 0x23
    // ==========================================

    else if (opcode == 0x23)
    {
        RegWrite = false;

        MemWrite = true;

        ALUSrc = true;

        ImmSrc = 1;

        // Address calculation
        ALUControl = 0b000;
    }


    // ==========================================
    // BRANCH
    // BEQ
    // opcode = 1100011 = 0x63
    // ==========================================

    else if (opcode == 0x63)
    {
        RegWrite = false;

        MemWrite = false;

        ALUSrc = false;

        Branch = true;

        ImmSrc = 2;

        // Compare registers
        ALUControl = 0b001;
    }
}