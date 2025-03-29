#include "pPIMMemoryMap.h"
#include "pPIMInstrInfo.h"
#include <algorithm>
#include <cassert>

namespace pPIM {

MemoryMap::MemoryMap() 
  : nextAvailableBank(0), 
    nextAvailableSubarray(0),
    nextAvailableRowAddr(0) {}

MemoryMap::MatrixLayout MemoryMap::allocateMatrix(unsigned rows, unsigned cols, unsigned elementSize) {
  MatrixLayout layout;
  layout.startBank = nextAvailableBank;
  layout.startSubarray = nextAvailableSubarray;
  layout.startRowAddr = nextAvailableRowAddr;
  layout.numRows = rows;
  layout.numCols = cols;
  layout.elementSize = elementSize;
  
  // Simple allocation strategy - allocate sequential rows
  unsigned totalSize = rows * cols * elementSize;
  unsigned rowsNeeded = (totalSize + ClusterRowBufferSize - 1) / ClusterRowBufferSize;
  
  // Update next available location
  nextAvailableRowAddr += rowsNeeded;
  if (nextAvailableRowAddr >= 512) { // Assuming 512 rows per subarray
    nextAvailableRowAddr = 0;
    nextAvailableSubarray++;
    if (nextAvailableSubarray >= NumSubarraysPerBank) {
      nextAvailableSubarray = 0;
      nextAvailableBank++;
      if (nextAvailableBank >= NumBanks) {
        // Out of memory
        assert(false && "Out of memory in pPIM architecture");
      }
    }
  }
  
  return layout;
}

unsigned MemoryMap::getPhysicalAddress(const MatrixLayout &layout, unsigned row, unsigned col) {
  // Calculate offset within the matrix
  unsigned offset = (row * layout.numCols + col) * layout.elementSize;
  
  // Calculate row address
  unsigned rowAddr = layout.startRowAddr + (offset / ClusterRowBufferSize);
  
  // For simplicity, we're just returning the row address
  // In a real implementation, we would return bank, subarray, and row information
  return rowAddr;
}

std::vector<uint32_t> MemoryMap::generateLoadInstructions(const MatrixLayout &layout, unsigned row) {
  std::vector<uint32_t> instructions;
  
  // Calculate start row address for this matrix row
  unsigned startRowAddr = getPhysicalAddress(layout, row, 0);
  unsigned rowsForThisRow = (layout.numCols * layout.elementSize + ClusterRowBufferSize - 1) / ClusterRowBufferSize;
  
  // Generate load instructions for each needed row
  for (unsigned i = 0; i < rowsForThisRow; ++i) {
    Instruction loadInstr = Instruction::createLoad(startRowAddr + i, i);
    instructions.push_back(loadInstr.getBinary());
  }
  
  return instructions;
}

std::vector<uint32_t> MemoryMap::generateStoreInstructions(const MatrixLayout &layout, unsigned row) {
  std::vector<uint32_t> instructions;
  
  // Calculate start row address for this matrix row
  unsigned startRowAddr = getPhysicalAddress(layout, row, 0);
  unsigned rowsForThisRow = (layout.numCols * layout.elementSize + ClusterRowBufferSize - 1) / ClusterRowBufferSize;
  
  // Generate store instructions for each needed row
  for (unsigned i = 0; i < rowsForThisRow; ++i) {
    Instruction storeInstr = Instruction::createStore(startRowAddr + i, i);
    instructions.push_back(storeInstr.getBinary());
  }
  
  return instructions;
}

std::vector<uint32_t> MemoryMap::mapMatrixMultiplication(const MatrixLayout &A, const MatrixLayout &B, const MatrixLayout &C) {
  std::vector<uint32_t> instructions;
  
  // First, program the LUTs for MAC operation
  for (unsigned i = 0; i < 9; ++i) { // 9 LUTs per cluster
    Instruction progInstr = Instruction::createLUTProgram(i);
    instructions.push_back(progInstr.getBinary());
  }
  
  // For each element of the result matrix
  for (unsigned i = 0; i < C.numRows; ++i) {
    // Load the ith row of matrix A
    auto loadAInstr = generateLoadInstructions(A, i);
    instructions.insert(instructions.end(), loadAInstr.begin(), loadAInstr.end());
    
    for (unsigned j = 0; j < C.numCols; ++j) {
      // For each column of B, we need to compute dot product
      // In a real implementation, we would need to transpose B or load columns
      // For simplicity, we'll just assume we can load columns directly
      
      // Load the jth column of matrix B
      // This is simplified - in reality, loading columns is more complex
      MatrixLayout transposedB = B;
      std::swap(transposedB.numRows, transposedB.numCols);
      auto loadBInstr = generateLoadInstructions(transposedB, j);
      instructions.insert(instructions.end(), loadBInstr.begin(), loadBInstr.end());
      
      // Perform the MAC operation for the dot product
      Instruction macInstr = Instruction::createCompute(0, 1); // Simplified: src from buffer 0, dst to buffer 1
      instructions.push_back(macInstr.getBinary());
      
      // Store the result to matrix C
      // For simplicity, we're assuming each element is stored separately
      MatrixLayout singleElement;
      singleElement.startBank = C.startBank;
      singleElement.startSubarray = C.startSubarray;
      singleElement.startRowAddr = getPhysicalAddress(C, i, j);
      singleElement.numRows = 1;
      singleElement.numCols = 1;
      singleElement.elementSize = C.elementSize;
      
      auto storeCInstr = generateStoreInstructions(singleElement, 0);
      instructions.insert(instructions.end(), storeCInstr.begin(), storeCInstr.end());
    }
  }
  
  return instructions;
}

} // namespace pPIM