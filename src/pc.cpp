#include "risc_v_core.hh"

PC_t Program_Counter(
    PC_t pc_current,
    bool reset,
    bool PCSrc,
    PC_t pc_target
)
{
    if (reset) {
        return 0;
    }

    if (PCSrc) {
        return pc_target;
    }

    return pc_current + 4;
}