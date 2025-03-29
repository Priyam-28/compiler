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
    
    // Initialization
    bool initialize(llvm::Module &M);
    
    // Matrix operation handling
    bool identifyMatrixMultiplication(llvm::Function &F);
    bool lowerMatrixMultiplication(llvm::Function &F);
    std::vector<uint32_t> generateInstructions(llvm::Function &F);
    std::vector<uint32_t> generateMAC8Bit(const MatrixLayout &A, 
                                        const MatrixLayout &B, 
                                        const MatrixLayout &C);
    
    // Code emission
    bool emitCode(llvm::raw_ostream &OS, const std::vector<uint32_t> &Instructions);
    
private:
    // Instruction generation helpers
    std::vector<uint32_t> generateLUTProgramming();
    std::vector<uint32_t> generateMemoryInstructions(const MatrixLayout &layout);
    std::vector<uint32_t> generateComputeInstructions();
    uint32_t mapOperation(const std::string &opName);
    
    MemoryMap memoryMap;
};

} // namespace pPIM

#endif // PPIM_BACKEND_H