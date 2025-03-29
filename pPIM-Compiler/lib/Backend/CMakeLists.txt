
add_library(pPIMBackend
  pPIMBackend.cpp
  pPIMMemoryMap.cpp
)

target_link_libraries(pPIMBackend
  PRIVATE
  LLVMCore
  LLVMSupport
)
