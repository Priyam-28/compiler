#include "pPIMBackend.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/ToolOutputFile.h"
#include <memory>
#include <string>

using namespace llvm;

static cl::opt<std::string> InputFilename(cl::Positional, 
                                         cl::desc("<input bitcode file>"),
                                         cl::init("-"));

static cl::opt<std::string> OutputFilename("o", 
                                          cl::desc("Output filename"),
                                          cl::value_desc("filename"));

int main(int argc, char **argv) {
  // Parse command line options
  cl::ParseCommandLineOptions(argc, argv, "pPIM compiler\n");
  
  // Set up the context
  LLVMContext Context;
  SMDiagnostic Err;
  
  // Load the input module
  std::unique_ptr<Module> M = parseIRFile(InputFilename, Err, Context);
  if (!M) {
    Err.print(argv[0], errs());
    return 1;
  }
  
  // Create output file
  std::error_code EC;
  std::unique_ptr<ToolOutputFile> Out(
    new ToolOutputFile(OutputFilename, EC, sys::fs::OF_None));
  if (EC) {
    errs() << EC.message() << '\n';
    return 1;
  }
  
  // Initialize the pPIM backend
  pPIM::Backend Backend;
  if (!Backend.initialize(*M)) {
    errs() << "Failed to initialize pPIM backend\n";
    return 1;
  }
  
  // Process each function in the module
  std::vector<uint32_t> Instructions;
  for (Function &F : *M) {
    if (F.isDeclaration())
      continue;
    
    // Generate pPIM instructions
    std::vector<uint32_t> FuncInstructions = Backend.generateInstructions(F);
    Instructions.insert(Instructions.end(), FuncInstructions.begin(), FuncInstructions.end());
  }
  
  // Emit the final code
  if (!Backend.emitCode(Out->os(), Instructions)) {
    errs() << "Failed to emit pPIM code\n";
    return 1;
  }
  
  // Keep the output file
  Out->keep();
  
  return 0;
}