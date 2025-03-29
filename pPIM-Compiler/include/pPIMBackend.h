#ifndef PPIM_BACKEND_H
#define PPIM_BACKEND_H

#include <vector>
#include <string>
#include "pPIMMemoryMap.h"
#include "pPIMInstrInfo.h"

namespace llvm {
  class Module;
  class Function;
  class MachineFunction;
  class raw_ostream;
}

namespace pPIM {

class Backend {
public:
  Backend();
  
  // Initialize the backend
  bool initialize(llvm::Module &M);
  
  // Identify matrix multiplication patterns in the IR
  bool identifyMatrixMultiplication(llvm::Function &F);
  
  // Lower matrix multiplication to pPIM instructions
  bool lowerMatrixMultiplication(llvm::Function &F);
  
  // Generate pPIM instructions for a function
  std::vector<uint32_t> generateInstructions(llvm::Function &F);
  
  // Emit the final binary code
  bool emitCode(llvm::raw_ostream &OS, const std::vector<uint32_t> &Instructions);
  
private:
  // Generate LUT programming instructions
  std::vector<uint32_t> generateLUTProgramming();
  
  // Generate memory load/store instructions
  std::vector<uint32_t> generateMemoryInstructions(const MemoryMap::MatrixLayout &layout);
  
  // Generate compute instructions
  std::vector<uint32_t> generateComputeInstructions();
  
  // Map LLVM IR operations to pPIM operations
  uint32_t mapOperation(const std::string &opName);
  
  // Memory map for handling DRAM address translations
  MemoryMap memoryMap;
};

} // namespace pPIM

#endif // PPIM_BACKEND_H