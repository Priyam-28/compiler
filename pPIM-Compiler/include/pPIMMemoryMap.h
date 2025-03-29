#ifndef PPIM_MEMORY_MAP_H
#define PPIM_MEMORY_MAP_H

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include "pPIMInstrInfo.h"

namespace pPIM {

// Single unified MatrixLayout definition
struct MatrixLayout {
    unsigned bank;            // DRAM bank number (0-7)
    unsigned subarray;        // Subarray within bank (0-3)
    unsigned startRow;        // Starting row address (0-511)
    unsigned numRows;         // Number of rows in matrix
    unsigned numCols;         // Number of columns in matrix
    unsigned elementSize;     // Size of each element in bytes
};

class MemoryMap {
public:
    // Architecture constants
    static const unsigned NumBanks = 8;
    static const unsigned NumSubarraysPerBank = 4;
    static const unsigned NumClustersPerSubarray = 4;
    static const unsigned ClusterRowBufferSize = 256; // bytes
    
    MemoryMap();
    
    // Memory management
    MatrixLayout allocateMatrix(unsigned rows, unsigned cols, unsigned elementSize);
    unsigned getPhysicalAddress(const MatrixLayout &layout, unsigned row, unsigned col);
    
    // Instruction generation
    std::vector<uint32_t> generateLoadInstructions(const MatrixLayout &layout, unsigned row);
    std::vector<uint32_t> generateStoreInstructions(const MatrixLayout &layout, unsigned row);
    std::vector<uint32_t> mapMatrixMultiplication(const MatrixLayout &A, 
                                                const MatrixLayout &B, 
                                                const MatrixLayout &C);
    
private:
    std::map<std::string, MatrixLayout> allocatedMatrices;
    unsigned nextAvailableBank;
    unsigned nextAvailableSubarray;
    unsigned nextAvailableRow;
};

} // namespace pPIM

#endif // PPIM_MEMORY_MAP_H