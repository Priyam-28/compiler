# pPIM Compiler: A LLVM-based Compiler for Processing-in-Memory Architectures

![pPIM Architecture Overview](https://via.placeholder.com/800x400?text=pPIM+Compiler+Architecture+Diagram)

## Table of Contents
1. [Introduction](#introduction)
2. [Codebase Structure](#codebase-structure)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Instruction Set Architecture](#instruction-set-architecture)
6. [Memory Management](#memory-management)
7. [Backend Compiler](#backend-compiler)
8. [Testing](#testing)
9. [Future Work](#future-work)
10. [License](#license)
11. [FAQ](#faq)

## Introduction
The pPIM Compiler translates C/C++/LLVM IR code into custom 24-bit instructions optimized for Processing-in-Memory (PIM) architectures. It specializes in compiling matrix operations (like matrix multiplication, ReLU activation) for AI/ML workloads running on DRAM-based PIM hardware.

Key Features:
- Generates efficient 24-bit pPIM instructions
- Optimizes for near-memory computing
- Supports common linear algebra operations
- Integrates with LLVM toolchain

## Codebase Structure
pPIM-Compiler/
├── include/
│ ├── pPIMBackend.h # Core compiler logic
│ ├── pPIMMemoryMap.h # DRAM memory management
│ └── pPIMInstrInfo.h # 24-bit ISA definition
├── lib/Backend/
│ ├── pPIMBackend.cpp # Instruction generation
│ └── pPIMMemoryMap.cpp # DRAM mapping logic
├── tools/
│ └── pPIMCompiler.cpp # Main compiler executable
└── test/
└── MatrixMultiply/ # Test cases
├── matrix_multiply.cpp
└── CMakeLists.txt


## Installation
### Prerequisites
- LLVM 10+ (with development headers)
- CMake 3.10+
- Clang
- Make or Ninja

### Building from Source
```bash
# Clone repository
git clone https://github.com/your-username/pPIM-Compiler.git
cd pPIM-Compiler

# Configure build
mkdir build && cd build
cmake .. -DLLVM_DIR=$(llvm-config --cmakedir)

# Compile
make -j$(nproc)

# Verify installation
./tools/ppim-compiler --version

clang++ -emit-llvm -c test/MatrixMultiply/matrix_multiply.cpp -o matrix_multiply.bc
./tools/ppim-compiler matrix_multiply.bc -o program.pim

cat program.pim
010000000000000000000000  # Program LUTs
000000000000001000000000  # Load matrix row
100000000000000000000000  # Compute operation
110000000000000000000000  # End program

[2-bit OPCODE][6-bit CORE][6-bit UNUSED][1-bit R][1-bit W][8-bit ROW_ADDR]