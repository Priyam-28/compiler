
add_executable(ppim-compiler
  pPIMCompiler.cpp
)

target_link_libraries(ppim-compiler
  PRIVATE
  pPIMBackend
  LLVMCore
  LLVMIRReader
  LLVMSupport
)
