#include "risc_v_core.hh"
#include <sstream>
#include <string>
#include <cstdint>

// ==========================================
// Register parser
// ==========================================

int ParseRegister(const std::string &reg)
{
    if (reg.size() >= 2 && reg[0] == 'x')
    {
        return std::stoi(reg.substr(1));
    }

    return -1;
}


// ==========================================
// R-Type
// ==========================================

uint32_t EncodeRType(
    uint32_t funct7,
    uint32_t rs2,
    uint32_t rs1,
    uint32_t funct3,
    uint32_t rd,
    uint32_t opcode
)
{
    return
        (funct7 << 25) |
        (rs2    << 20) |
        (rs1    << 15) |
        (funct3 << 12) |
        (rd     << 7)  |
        opcode;
}


// ==========================================
// I-Type
// ==========================================

uint32_t EncodeIType(
    int32_t imm,
    uint32_t rs1,
    uint32_t funct3,
    uint32_t rd,
    uint32_t opcode
)
{
    uint32_t immediate = imm & 0xFFF;

    return
        (immediate << 20) |
        (rs1       << 15) |
        (funct3    << 12) |
        (rd         << 7) |
        opcode;
}


// ==========================================
// S-Type
// ==========================================

uint32_t EncodeSType(
    int32_t imm,
    uint32_t rs2,
    uint32_t rs1,
    uint32_t funct3,
    uint32_t opcode
)
{
    uint32_t immediate = imm & 0xFFF;

    uint32_t imm11_5 =
        (immediate >> 5) & 0x7F;

    uint32_t imm4_0 =
        immediate & 0x1F;

    return
        (imm11_5 << 25) |
        (rs2      << 20) |
        (rs1      << 15) |
        (funct3   << 12) |
        (imm4_0   << 7)  |
        opcode;
}


// ==========================================
// B-Type
// ==========================================

uint32_t EncodeBType(
    int32_t imm,
    uint32_t rs2,
    uint32_t rs1,
    uint32_t funct3,
    uint32_t opcode
)
{
    uint32_t immediate = imm & 0x1FFF;

    uint32_t bit12 =
        (immediate >> 12) & 0x1;

    uint32_t bit11 =
        (immediate >> 11) & 0x1;

    uint32_t bits10_5 =
        (immediate >> 5) & 0x3F;

    uint32_t bits4_1 =
        (immediate >> 1) & 0xF;

    return
        (bit12    << 31) |
        (bits10_5 << 25) |
        (rs2      << 20) |
        (rs1      << 15) |
        (funct3   << 12) |
        (bits4_1  << 8)  |
        (bit11    << 7)  |
        opcode;
}


// ==========================================
// Assembler
// ==========================================

uint32_t AssembleInstruction(
    const std::string &line
)
{
    std::stringstream ss(line);

    std::string instruction;

    ss >> instruction;


    // ======================================
    // R-TYPE
    // ======================================

    if (instruction == "add" ||
        instruction == "sub" ||
        instruction == "and" ||
        instruction == "or"  ||
        instruction == "slt")
    {
        std::string rdString;
        std::string rs1String;
        std::string rs2String;

        ss >> rdString;
        ss >> rs1String;
        ss >> rs2String;

        if (!rdString.empty() &&
            rdString.back() == ',')
            rdString.pop_back();

        if (!rs1String.empty() &&
            rs1String.back() == ',')
            rs1String.pop_back();

        int rd  = ParseRegister(rdString);
        int rs1 = ParseRegister(rs1String);
        int rs2 = ParseRegister(rs2String);

        uint32_t funct3 = 0;
        uint32_t funct7 = 0;

        if (instruction == "add")
        {
            funct3 = 0b000;
            funct7 = 0b0000000;
        }
        else if (instruction == "sub")
        {
            funct3 = 0b000;
            funct7 = 0b0100000;
        }
        else if (instruction == "and")
        {
            funct3 = 0b111;
        }
        else if (instruction == "or")
        {
            funct3 = 0b110;
        }
        else if (instruction == "slt")
        {
            funct3 = 0b010;
        }

        return EncodeRType(
            funct7,
            rs2,
            rs1,
            funct3,
            rd,
            0x33
        );
    }


    // ======================================
    // ADDI
    // ======================================

    if (instruction == "addi")
    {
        std::string rdString;
        std::string rs1String;
        int imm;

        ss >> rdString;
        ss >> rs1String;
        ss >> imm;

        if (!rdString.empty() &&
            rdString.back() == ',')
            rdString.pop_back();

        if (!rs1String.empty() &&
            rs1String.back() == ',')
            rs1String.pop_back();

        int rd  = ParseRegister(rdString);
        int rs1 = ParseRegister(rs1String);

        return EncodeIType(
            imm,
            rs1,
            0b000,
            rd,
            0x13
        );
    }


    // ======================================
    // LW
    //
    // lw rd, offset(rs1)
    // ======================================

    if (instruction == "lw")
    {
        std::string rdString;
        std::string address;

        ss >> rdString;
        ss >> address;

        if (!rdString.empty() &&
            rdString.back() == ',')
            rdString.pop_back();

        size_t open = address.find('(');
        size_t close = address.find(')');

        int imm =
            std::stoi(address.substr(0, open));

        std::string rs1String =
            address.substr(
                open + 1,
                close - open - 1
            );

        int rd  = ParseRegister(rdString);
        int rs1 = ParseRegister(rs1String);

        return EncodeIType(
            imm,
            rs1,
            0b010,
            rd,
            0x03
        );
    }


    // ======================================
    // SW
    //
    // sw rs2, offset(rs1)
    // ======================================

    if (instruction == "sw")
    {
        std::string rs2String;
        std::string address;

        ss >> rs2String;
        ss >> address;

        if (!rs2String.empty() &&
            rs2String.back() == ',')
            rs2String.pop_back();

        size_t open = address.find('(');
        size_t close = address.find(')');

        int imm =
            std::stoi(address.substr(0, open));

        std::string rs1String =
            address.substr(
                open + 1,
                close - open - 1
            );

        int rs2 = ParseRegister(rs2String);
        int rs1 = ParseRegister(rs1String);

        return EncodeSType(
            imm,
            rs2,
            rs1,
            0b010,
            0x23
        );
    }


    // ======================================
    // BEQ
    //
    // beq rs1, rs2, offset
    // ======================================

    if (instruction == "beq")
    {
        std::string rs1String;
        std::string rs2String;
        int imm;

        ss >> rs1String;
        ss >> rs2String;
        ss >> imm;

        if (!rs1String.empty() &&
            rs1String.back() == ',')
            rs1String.pop_back();

        if (!rs2String.empty() &&
            rs2String.back() == ',')
            rs2String.pop_back();

        int rs1 = ParseRegister(rs1String);
        int rs2 = ParseRegister(rs2String);

        return EncodeBType(
            imm,
            rs2,
            rs1,
            0b000,
            0x63
        );
    }


    return 0;
}