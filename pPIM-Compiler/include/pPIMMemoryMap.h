#ifndef PPIM_MEMORY_MAP_H
#define PPIM_MEMORY_MAP_H

#include <vector>
#include <map>
#include <string>
#include <cstdint>

namespace pPIM {

// Represents the physical layout of DRAM for pPIM architecture
class MemoryMap {
public:
  // Constants for the pPIM architecture
  static const unsigned NumBanks = 8;
  static const unsigned NumSubarraysPerBank = 4;
  static const unsigned NumClustersPerSubarray = 4;
  static const unsigned ClusterRowBufferSize = 256; // bytes
  
  // Matrix memory layout information
  struct MatrixLayout {
    unsigned startBank;
    unsigned startSubarray;
    unsigned startRowAddr;
    unsigned numRows;
    unsigned numCols;
    unsigned elementSize; // in bytes
  };
  
  MemoryMap();
  
  // Allocate memory for a matrix
  MatrixLayout allocateMatrix(unsigned rows, unsigned cols, unsigned elementSize);
  
  // Get address mappings for matrix elements
  unsigned getPhysicalAddress(const MatrixLayout &layout, unsigned row, unsigned col);
  
  // Generate memory access instructions for matrix elements
  std::vector<uint32_t> generateLoadInstructions(const MatrixLayout &layout, unsigned row);
  std::vector<uint32_t> generateStoreInstructions(const MatrixLayout &layout, unsigned row);
  
  // Map matrix multiplication to pPIM operations
  std::vector<uint32_t> mapMatrixMultiplication(const MatrixLayout &A, const MatrixLayout &B, const MatrixLayout &C);
  
private:
  // Track memory allocations
  std::map<std::string, MatrixLayout> allocatedMatrices;
  unsigned nextAvailableBank;
  unsigned nextAvailableSubarray;
  unsigned nextAvailableRowAddr;
};

} // namespace pPIM

#endif // PPIM_MEMORY_MAP_H