# RISC-V RV32I Single-Cycle Processor & Instruction Simulator

A from-scratch implementation of a **32-bit RISC-V processor** based on the **RV32I instruction set architecture**.

This project implements a **single-cycle / non-pipelined RISC-V CPU** in C++, including the processor datapath, control logic, instruction memory, register file, ALU, data memory, branching, instruction assembly, and an interactive simulator.

The processor has been tested by executing a GCD (Greatest Common Divisor) program using RISC-V instructions.


## Features

* 32-bit RISC-V architecture
* Single-cycle / non-pipelined CPU
* Program Counter
* Instruction Memory
* Instruction Decoder
* Control Unit
* Register File
* ALU
* Immediate Extension Unit
* Data Memory
* Branch Logic
* Writeback logic
* RISC-V instruction assembler
* Interactive instruction input
* Label support
* Branch label resolution
* HALT instruction
* CPU cycle-by-cycle debugging
* GCD program execution

---

## CPU Architecture

The processor follows a basic single-cycle datapath:

```text
              ┌──────────────────┐
              │ Program Counter  │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Instruction      │
              │ Memory           │
              └────────┬─────────┘
                       │
                       ▼
              ┌──────────────────┐
              │ Instruction      │
              │ Decoder          │
              └────────┬─────────┘
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
    ┌──────────┐ ┌──────────┐ ┌──────────────┐
    │ Register │ │ Control  │ │ Immediate    │
    │ File     │ │ Unit     │ │ Extension    │
    └────┬─────┘ └──────────┘ └──────┬───────┘
         │                            │
         └──────────┬─────────────────┘
                    ▼
              ┌──────────┐
              │   ALU    │
              └────┬─────┘
                   │
          ┌────────┴────────┐
          ▼                 ▼
   ┌──────────────┐   ┌──────────────┐
   │ Data Memory  │   │ Branch Logic │
   └──────┬───────┘   └──────┬───────┘
          │                  │
          └────────┬─────────┘
                   ▼
             ┌───────────┐
             │ Writeback │
             └─────┬─────┘
                   │
                   ▼
             Register File
```

---

## Project Structure

```text
RISC-V-Project/
│
├── src/
│   ├── risc_v_core.cpp
│   ├── risc_v_core.hh
│   ├── ALU.cpp
│   ├── Control_Unit.cpp
│   ├── Decode_Instruction.cpp
│   ├── Extend_Immediate.cpp
│   ├── Instruction_Memory.cpp
│   ├── Register_File.cpp
│   ├── Data_Memory.cpp
│   └── PC.cpp
│
├── tb/
│   └── tb_risc_v_core.cpp
│
├── README.md
└── ...
```

---

## Processor Components

### Program Counter

The Program Counter keeps track of the current instruction address.

For normal instructions:

```text
PC = PC + 4
```

For a taken branch:

```text
PC = PC + branch_offset
```

---

### Instruction Memory

Instruction memory stores the machine-code instructions executed by the processor.

Example:

```text
PC 0x00000000 : 0x03000293
PC 0x00000004 : 0x01200313
PC 0x00000008 : 0x00628e63
```

---

### Instruction Decoder

The decoder extracts fields from a 32-bit RISC-V instruction:

```text
opcode
rd
rs1
rs2
funct3
funct7
```

These fields are passed to the control unit and register file.

### Register File

The processor uses the standard RISC-V register set:

```text
x0 - x31
```

The register file provides two read ports and one write port.

Example:

```text
x5 = 48
x6 = 18
```

---

### ALU

The ALU currently supports operations including:

```text
ADD
SUB
AND
OR
SLT
```

The ALU also generates a zero flag used by branch instructions.

For example:

```text
6 - 6 = 0
```

produces:

```text
ZERO = 1
```

which allows a `BEQ` instruction to take the branch.


### Immediate Extension

The immediate extension unit extracts and extends immediate values from RISC-V instructions.

These values are then supplied to the ALU or branch logic.


### Data Memory

The processor provides an interface for reading and writing data memory.

The memory interface uses:

```text
Address
Write Data
MemWrite
Read Data
```


### Control Unit

The control unit generates the signals required by the datapath:

```text
RegWrite
MemWrite
MemToReg
ALUSrc
Branch
ALUControl
ImmSrc
```


## Current Instruction Support

The project is being developed toward the RV32I base integer instruction set.

### Currently implemented/tested

| Instruction | Status |
| ----------- | ------ |
| `ADD`       | ✅      |
| `SUB`       | ✅      |
| `AND`       | ✅      |
| `OR`        | ✅      |
| `SLT`       | ✅      |
| `ADDI`      | ✅      |
| `BEQ`       | ✅      |
| `SW`        | 🔶     |
| `LW`        | 🔶     |
| `HALT`      | ✅      |

> 🔶 Indicates functionality that is implemented or under active testing.

### Planned RV32I instructions

```text
XOR
SLTU
SLL
SRL
SRA

ANDI
ORI
XORI
SLTI
SLTIU

SLLI
SRLI
SRAI

LB
LH
LBU
LHU

SB
SH

BNE
BLT
BGE
BLTU
BGEU

JAL
JALR

LUI
AUIPC
```

The goal is to progressively expand the implementation toward complete RV32I support.


#  Interactive Instruction Simulator

The testbench provides an interactive environment where RISC-V instructions can be entered without modifying the CPU source code.

Example:

```text
> addi x5, x0, 10
> addi x6, x0, 20
> add x7, x5, x6
> halt
> run
```

The simulator assembles the instructions into machine code and loads them into instruction memory.


## Label Support

Labels can be used for branches.

Example:

```text
addi x5, x0, 10
addi x6, x0, 10

loop:
beq x5, x6, done

addi x7, x0, 1

done:
halt
```

The simulator performs a first pass to find labels and a second pass to resolve branch offsets.

Example output:

```text
Label: loop = PC 8
Label: done = PC 20
```


#  GCD Demonstration

One of the main demonstrations is a GCD program.

For example:

```text
GCD(48, 18) = 6
```

The program uses the Euclidean subtraction algorithm:

```text
48 - 18 = 30
30 - 18 = 12
18 - 12 = 6
12 - 6  = 6
```

When the two values become equal:

```text
6 = 6
```

the program branches to the `done` label.

The final result is stored in register `x10`:

```text
WRITE: x10 = 6
```

The processor then executes the HALT instruction.


#  Example Execution

Example machine code generated by the assembler:

```text
PC 0x00000000 : 0x03000293
PC 0x00000004 : 0x01200313
PC 0x00000008 : 0x00628e63
PC 0x0000000c : 0x005323b3
...
PC 0x00000024 : 0x00028533
PC 0x00000028 : 0x00100073
```

The CPU then executes the program cycle by cycle.

Example:

```text
===== CPU Cycle 25 =====

ALU Result immediately after ALU = 6
WRITE: x10 = 6

===== CPU Cycle 26 =====

HALT instruction reached at PC = 40
```

Final result:

```text
GCD = 6
```


#  Building the Project

Compile the project using your C++ compiler.

For example:

```bash
clang++ src/*.cpp tb/tb_risc_v_core.cpp -o riscv_sim
```

Then run:

```bash
./riscv_sim
```

On macOS, the same project can be compiled using:

```bash
clang++ src/*.cpp tb/tb_risc_v_core.cpp -o riscv_sim
./riscv_sim
```

> Adjust the source-file list if your project contains additional files or a different directory structure.


#  Running a Program

Start the simulator:

```bash
./riscv_sim
```

Enter instructions:

```text
> addi x5, x0, 48
> addi x6, x0, 18
> ...
> halt
> run
```

The simulator will:

1. Read the instructions.
2. Resolve labels.
3. Assemble instructions into machine code.
4. Load them into instruction memory.
5. Start the CPU.
6. Execute instructions cycle by cycle.
7. Display ALU, branch, memory, and register activity.
8. Stop at `HALT`.


#  Debugging Output

The simulator provides detailed internal signals such as:

```text
Immediate = 28

ALU Inputs:
RD1 = 48
ALUInputB = 18
ALUControl = 1

ALU Result immediately after ALU = 30

Branch Signals:
Branch = 1
ZERO = 0
PCSrc = 0

Memory Signals:
MemWrite = 0
MemToReg = 0
MemoryReadData = 0
WriteBackData = 30
```

This makes it possible to inspect how each instruction travels through the CPU datapath.


#  Project Goals

The main goals of this project are:

* Understand the RISC-V ISA.
* Implement a CPU datapath from scratch.
* Understand instruction decoding.
* Understand ALU and control-unit design.
* Implement register and memory operations.
* Implement conditional branching.
* Build an instruction assembler/simulator.
* Execute real RISC-V programs.
* Progress toward complete RV32I support.
* Provide a foundation for a future pipelined implementation.


#  Future Work

Planned improvements include:

* Complete RV32I instruction support.
* Correct signed and unsigned operations.
* Additional load/store instructions.
* Complete branch instruction support.
* `JAL` and `JALR`.
* `LUI` and `AUIPC`.
* More comprehensive automated tests.
* Better instruction/error handling.
* Register dump after program execution.
* Memory dump/debugging.
* Improved instruction trace.
* Performance statistics.
* Five-stage pipelined implementation.


#  Learning Objectives

This project is intended as an educational implementation of a RISC-V processor.

It demonstrates how high-level instructions such as:

```text
addi
sub
beq
add
```

are translated into machine code and executed through the processor datapath.

The GCD example demonstrates that the processor can execute:

* Arithmetic operations
* Comparisons
* Conditional branches
* Loops
* Register updates
* Program termination


#  Author

Rishita Mishra

RISC-V RV32I Processor Implementation


