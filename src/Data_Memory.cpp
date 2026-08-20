#include "risc_v_core.hh"

data_t Data_Memory(
    PC_t address,
    data_t WriteData,
    bool MemWrite
)
{
    static data_t memory[64] = {0};

    // Convert byte address to memory index
    uint32_t index = address / 4;

    // Write
    if (MemWrite)
    {
        memory[index] = WriteData;
    }

    // Read
    return memory[index];
}