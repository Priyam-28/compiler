#include "pPIMMemoryMap.h"
#include <stdexcept>

namespace pPIM {

MemoryMap::MemoryMap() : 
    nextAvailableBank(0),
    nextAvailableSubarray(0),
    nextAvailableRow(0) {}

MatrixLayout MemoryMap::allocateMatrix(unsigned rows, unsigned cols, unsigned elementSize) {
    MatrixLayout layout;
    layout.bank = nextAvailableBank;
    layout.subarray = nextAvailableSubarray;
    layout.startRow = nextAvailableRow;
    layout.numRows = rows;
    layout.numCols = cols;
    layout.elementSize = elementSize;

    // Calculate needed rows (256B row buffer)
    unsigned totalBytes = rows * cols * elementSize;
    unsigned neededRows = (totalBytes + ClusterRowBufferSize - 1) / ClusterRowBufferSize;

    // Update allocation pointers
    nextAvailableRow += neededRows;
    if (nextAvailableRow >= 512) {  // 512 rows per subarray
        nextAvailableRow = 0;
        nextAvailableSubarray++;
        if (nextAvailableSubarray >= NumSubarraysPerBank) {
            nextAvailableSubarray = 0;
            nextAvailableBank++;
            if (nextAvailableBank >= NumBanks) {
                throw std::runtime_error("DRAM out of memory");
            }
        }
    }

    return layout;
}

unsigned MemoryMap::getPhysicalAddress(const MatrixLayout &layout, unsigned row, unsigned col) {
    unsigned offset = (row * layout.numCols + col) * layout.elementSize;
    return layout.startRow + (offset / ClusterRowBufferSize);
}

std::vector<uint32_t> MemoryMap::generateLoadInstructions(const MatrixLayout &layout, unsigned row) {
    std::vector<uint32_t> instructions;
    unsigned rowAddr = getPhysicalAddress(layout, row, 0);
    instructions.push_back(Instruction::createMemAccess(true, false, rowAddr).getBinary());
    return instructions;
}

std::vector<uint32_t> MemoryMap::generateStoreInstructions(const MatrixLayout &layout, unsigned row) {
    std::vector<uint32_t> instructions;
    unsigned rowAddr = getPhysicalAddress(layout, row, 0);
    instructions.push_back(Instruction::createMemAccess(false, true, rowAddr).getBinary());
    return instructions;
}

std::vector<uint32_t> MemoryMap::mapMatrixMultiplication(const MatrixLayout &A, const MatrixLayout &B, const MatrixLayout &C) {
    std::vector<uint32_t> instructions;
    // Implementation of matrix multiplication mapping
    // ... [Your implementation here]
    return instructions;
}

} // namespace pPIM