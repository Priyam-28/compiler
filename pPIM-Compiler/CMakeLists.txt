cmake_minimum_required(VERSION 3.10)
project(pPIM-Compiler)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(include)
add_definitions(${LLVM_DEFINITIONS})


# Add subdirectories
add_subdirectory(lib)
add_subdirectory(tools)

# Enable testing
enable_testing()
add_subdirectory(test)



