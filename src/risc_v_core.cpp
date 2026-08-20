#include <iostream>
#include "risc_v_core.hh"

void ALU_Unit(
    data_t SrcAE,
    data_t SrcBE,
    uint8_t ALUControl,
    bool &ZERO,
    data_t &ALUResult
);

// ==========================================
// Program Counter
// ==========================================

PC_t Program_Counter(
    PC_t pc_current,
    bool reset,
    bool PCSrc,
    PC_t pc_target
);


// ==========================================
// Instruction Memory
// ==========================================

instruction_t Instruction_Memory(
    PC_t address
);


// ==========================================
// Instruction Decoder
// ==========================================

void Decode_Instruction(
    instruction_t instruction,
    reg_t &rs1,
    reg_t &rs2,
    reg_t &rd,
    uint8_t &funct3,
    uint8_t &funct7,
    uint8_t &opcode
);
// ==========================================
// Register File
// ==========================================

void Register_File(
    bool WE3,
    reg_t A1,
    reg_t A2,
    reg_t A3,
    data_t WD3,
    data_t &RD1_D,
    data_t &RD2_D
);
// ==========================================
// Control Unit
// ==========================================

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

// ==========================================
// Extend Unit
// ==========================================

data_t Extend_Immediate(
    instruction_t instruction,
    uint8_t ImmSrc
);

// ==========================================
// Data Memory
// ==========================================

data_t Data_Memory(
    PC_t address,
    data_t WriteData,
    bool MemWrite
);

// ==========================================
// RISC-V Core
// ==========================================

bool RISC_V_Core(
    bool reset,
    data_t &ALUResult
)
{
    // --------------------------------------
    // 1. Program Counter
    // --------------------------------------

    static PC_t pc = 0;
    bool PCSrc = false;
    PC_t pc_target = 0;

    // --------------------------------------
    // Reset
    // --------------------------------------

    if (reset)
    {
        pc = 0;
    }


    // --------------------------------------
    // 2. Instruction Memory
    // --------------------------------------

    instruction_t instruction;

    instruction = Instruction_Memory(pc);
    if (instruction == 0x00100073)
    {
        std::cout << "HALT instruction reached at PC = "
                << pc
                << std::endl;

        return true;
    }


    // --------------------------------------
    // 3. Decode instruction
    // --------------------------------------

    reg_t rs1;
    reg_t rs2;
    reg_t rd;

    uint8_t funct3;
    uint8_t funct7;
    uint8_t opcode;

    Decode_Instruction(
        instruction,
        rs1,
        rs2,
        rd,
        funct3,
        funct7,
        opcode
    );
    // ======================================
    // 4. Control Unit
    // ======================================

    bool RegWrite;
    bool MemWrite;
    bool MemToReg;
    bool ALUSrc;
    bool Branch;

    uint8_t ALUControl;
    uint8_t ImmSrc;

    Control_Unit(
        opcode,
        funct3,
        funct7,

        RegWrite,
        MemWrite,
        MemToReg,
        ALUSrc,
        Branch,

        ALUControl,
        ImmSrc
    );

    // ======================================
    // 5. Extend Immediate
    // ======================================

    data_t ImmExt;

    ImmExt = Extend_Immediate(
        instruction,
        ImmSrc
    );

    std::cout << "Immediate = "
            << ImmExt
            << std::endl;
    // ======================================
    // 6. Register File - READ
    // ======================================

    data_t RD1;
    data_t RD2;

    Register_File(
        false,          // Don't write during READ
        rs1,
        rs2,
        rd,
        0,              // No write data
        RD1,
        RD2
    );


    // ======================================
    // 7. ALU Input Selection
    // ======================================

    data_t ALUInputB;

    if (ALUSrc)
    {
        ALUInputB = ImmExt;
    }
    else
    {
        ALUInputB = RD2;
    }


    // ======================================
    // 8. ALU
    // ======================================
    std::cout << "ALU Inputs:" << std::endl;

    std::cout << "RD1 = "
            << RD1
            << std::endl;

    std::cout << "ALUInputB = "
            << ALUInputB
            << std::endl;

    std::cout << "ALUControl = "
            << (int)ALUControl
            << std::endl;
        data_t ALUResultValue;
        bool ZERO;

    ALU_Unit(
        RD1,
        ALUInputB,
        ALUControl,
        ZERO,
        ALUResultValue
    );
    std::cout << "ALU Result immediately after ALU = "
          << ALUResultValue
          << std::endl;

    ALUResult = ALUResultValue;

    // ======================================
    // 9. Branch Logic
    // ======================================

    int32_t branch_offset =
    static_cast<int32_t>(ImmExt);

    pc_target = pc + branch_offset;

    PCSrc = Branch && ZERO;

    std::cout << "Branch Signals:" << std::endl;

    std::cout << "Branch = "
            << Branch
            << std::endl;

    std::cout << "ZERO = "
            << ZERO
            << std::endl;

    std::cout << "PCSrc = "
            << PCSrc
            << std::endl;

    std::cout << "PC Target = "
            << pc_target
            << std::endl;
        // ======================================
        // 10. Data Memory
        // ======================================

        data_t MemoryReadData = 0;

        if (MemWrite || MemToReg)
        {
            MemoryReadData = Data_Memory(
                ALUResultValue,
                RD2,
                MemWrite
            );
        }


    // ======================================
    // 11. Writeback MUX
    // ======================================

    data_t WriteBackData;

    if (MemToReg)
    {
        WriteBackData = MemoryReadData;
    }
    else
    {
        WriteBackData = ALUResultValue;
    }


    // ======================================
    // 12. Register File WRITEBACK
    // ======================================

    Register_File(
        RegWrite,
        rs1,
        rs2,
        rd,
        WriteBackData,
        RD1,
        RD2
    );


    // ======================================
    // Memory Debug
    // ======================================

    std::cout << "Memory Signals:" << std::endl;

    std::cout << "MemWrite = "
            << MemWrite << std::endl;

    std::cout << "MemToReg = "
            << MemToReg << std::endl;

    std::cout << "MemoryReadData = "
            << MemoryReadData << std::endl;

    std::cout << "WriteBackData = "
            << WriteBackData << std::endl;

    // ======================================
    // Next PC
    // ======================================

    pc = Program_Counter(
        pc,
        reset,
        PCSrc,
        pc_target
    );
    return false;
}