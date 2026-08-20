#include "risc_v_core.hh"
#include <iostream>

void Register_File(
    bool WE3,
    reg_t A1,
    reg_t A2,
    reg_t A3,
    data_t WD3,
    data_t &RD1_D,
    data_t &RD2_D
)
{
    static data_t registers[32] = {0};

    // Read register 1
    if (A1 == 0)
        RD1_D = 0;
    else
        RD1_D = registers[A1];

    // Read register 2
    if (A2 == 0)
        RD2_D = 0;
    else
        RD2_D = registers[A2];

    // Write register
    if (WE3 == 1 && A3 != 0){
        registers[A3] = WD3;}
    if (WE3)
    {
        std::cout << "WRITE: x"
                << (int)A3
                << " = "
                << WD3
                << std::endl;
    }
}