#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "../src/risc_v_core.hh"

// ==========================================
// Remove leading/trailing spaces
// ==========================================

std::string Trim(const std::string &str)
{
    size_t start = str.find_first_not_of(" \t");

    if (start == std::string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t");

    return str.substr(start, end - start + 1);
}


// ==========================================
// Replace branch label with offset
// ==========================================

std::string ResolveLabels(
    std::string line,
    const std::map<std::string, int> &labels,
    int currentPC
)
{
    std::stringstream ss(line);

    std::string op;
    ss >> op;

    if (op != "beq")
        return line;

    std::string rs1;
    std::string rs2;
    std::string target;

    ss >> rs1;
    ss >> rs2;
    ss >> target;

    if (!rs1.empty() && rs1.back() == ',')
        rs1.pop_back();

    if (!rs2.empty() && rs2.back() == ',')
        rs2.pop_back();

    auto it = labels.find(target);

    if (it == labels.end())
    {
        std::cout << "Unknown label: "
                  << target
                  << std::endl;

        return "";
    }

    int targetPC = it->second;

    int offset = targetPC - currentPC;

    return "beq " +
           rs1 + ", " +
           rs2 + ", " +
           std::to_string(offset);
}


// ==========================================
// MAIN
// ==========================================

int main()
{
    std::vector<std::string> program;

    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "       RISC-V CPU Simulator\n";
    std::cout << "====================================\n";

    std::cout << "\nEnter RISC-V instructions.\n";
    std::cout << "Labels are supported.\n\n";

    std::cout << "Commands:\n";
    std::cout << "  run   - execute program\n";
    std::cout << "  clear - clear program\n";
    std::cout << "  quit  - exit\n\n";


    // ======================================
    // Read program
    // ======================================

    while (true)
    {
        std::cout << "> ";

        std::string line;

        std::getline(std::cin, line);

        line = Trim(line);

        if (line == "run")
            break;

        if (line == "quit")
            return 0;

        if (line == "clear")
        {
            program.clear();

            std::cout << "Program cleared.\n";

            continue;
        }

        if (line.empty())
            continue;

        program.push_back(line);

        std::cout << "Added: "
                  << line
                  << std::endl;
    }


    // ======================================
    // PASS 1
    // Find labels
    // ======================================

    std::map<std::string, int> labels;

    int pc = 0;

    for (const std::string &originalLine : program)
    {
        std::string line = Trim(originalLine);

        if (!line.empty() && line.back() == ':')
        {
            std::string label =
                line.substr(0, line.size() - 1);

            labels[label] = pc;

            std::cout << "Label: "
                      << label
                      << " = PC "
                      << pc
                      << std::endl;

            continue;
        }

        pc += 4;
    }


    // ======================================
    // PASS 2
    // Assemble instructions
    // ======================================

    std::vector<uint32_t> machineCode;

    pc = 0;

    for (const std::string &originalLine : program)
    {
        std::string line = Trim(originalLine);

        // Skip labels
        if (!line.empty() && line.back() == ':')
        {
            continue;
        }

        // Resolve branch labels
        line = ResolveLabels(
            line,
            labels,
            pc
        );

        if (line.empty())
        {
            return 1;
        }

        uint32_t instruction = 0;

        // ======================================
        // HALT
        // ======================================

        if (line == "halt")
        {
            instruction = 0x00100073;
        }
        else
        {
            instruction = AssembleInstruction(line);

            if (instruction == 0)
            {
                std::cout << "Invalid instruction: "
                          << line
                          << std::endl;

                return 1;
            }
        }

        machineCode.push_back(instruction);

        std::cout << "PC 0x"
                  << std::hex
                  << std::setw(8)
                  << std::setfill('0')
                  << pc
                  << " : 0x"
                  << std::setw(8)
                  << instruction
                  << std::dec
                  << std::setfill(' ')
                  << std::endl;

        pc += 4;
    }


    // ======================================
    // Load into instruction memory
    // ======================================

    for (size_t i = 0;
         i < machineCode.size();
         i++)
    {
        Load_Instruction(
            i,
            machineCode[i]
        );
    }


    // ======================================
    // Run CPU
    // ======================================

    std::cout << "\n";
    std::cout << "====================================\n";
    std::cout << "Running CPU\n";
    std::cout << "====================================\n";

    data_t result = 0;

    for (int cycle = 0; cycle < 1000; cycle++)
    {
        std::cout << "\n===== CPU Cycle "
                  << cycle + 1
                  << " =====\n";

        bool reset = (cycle == 0);

        bool halted = RISC_V_Core(
            reset,
            result
        );

        std::cout << "ALU Result = "
                  << result
                  << std::endl;

        if (halted)
        {
            std::cout << "\nProgram finished.\n";
            break;
        }
    }


    std::cout << "\nProgram finished.\n";

    return 0;
}