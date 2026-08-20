#include <iostream>

#include "../src/risc_v_core.hh"

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
);

void printSignals(
    bool RegWrite,
    bool MemWrite,
    bool MemToReg,
    bool ALUSrc,
    bool Branch,
    uint8_t ALUControl,
    uint8_t ImmSrc
)
{
    std::cout << "RegWrite  = " << RegWrite << std::endl;
    std::cout << "MemWrite  = " << MemWrite << std::endl;
    std::cout << "MemToReg  = " << MemToReg << std::endl;
    std::cout << "ALUSrc    = " << ALUSrc << std::endl;
    std::cout << "Branch    = " << Branch << std::endl;
    std::cout << "ALUControl = " << (int)ALUControl << std::endl;
    std::cout << "ImmSrc     = " << (int)ImmSrc << std::endl;
}

int main()
{
    bool RegWrite;
    bool MemWrite;
    bool MemToReg;
    bool ALUSrc;
    bool Branch;

    uint8_t ALUControl;
    uint8_t ImmSrc;


    // ==========================================
    // TEST 1: ADD
    // ==========================================

    std::cout << "\n===== ADD =====" << std::endl;

    Control_Unit(
        0x33,       // opcode
        0b000,      // funct3
        0b0000000,  // funct7
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );

    printSignals(
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );


    // ==========================================
    // TEST 2: SUB
    // ==========================================

    std::cout << "\n===== SUB =====" << std::endl;

    Control_Unit(
        0x33,
        0b000,
        0b0100000,
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );

    printSignals(
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );


    // ==========================================
    // TEST 3: ADDI
    // ==========================================

    std::cout << "\n===== ADDI =====" << std::endl;

    Control_Unit(
        0x13,
        0b000,
        0,
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );

    printSignals(
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );


    // ==========================================
    // TEST 4: LW
    // ==========================================

    std::cout << "\n===== LW =====" << std::endl;

    Control_Unit(
        0x03,
        0,
        0,
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );

    printSignals(
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );


    // ==========================================
    // TEST 5: SW
    // ==========================================

    std::cout << "\n===== SW =====" << std::endl;

    Control_Unit(
        0x23,
        0,
        0,
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );

    printSignals(
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );


    // ==========================================
    // TEST 6: BEQ
    // ==========================================

    std::cout << "\n===== BEQ =====" << std::endl;

    Control_Unit(
        0x63,
        0b000,
        0,
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );

    printSignals(
        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,
        ALUControl,
        ImmSrc
    );


    return 0;
}