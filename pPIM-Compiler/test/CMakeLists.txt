
find_program(CLANG_EXE clang++)

if(CLANG_EXE)
  # Matrix multiplication test
  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/matrix_multiply.bc
    COMMAND ${CLANG_EXE} -emit-llvm -c ${CMAKE_CURRENT_SOURCE_DIR}/MatrixMultiply/matrix_multiply.cpp -o ${CMAKE_CURRENT_BINARY_DIR}/matrix_multiply.bc
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/MatrixMultiply/matrix_multiply.cpp
  )
  
  add_custom_target(matrix_multiply_bc ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/matrix_multiply.bc
  )
  
  add_test(
    NAME MatrixMultiplyTest
    COMMAND $<TARGET_FILE:ppim-compiler> ${CMAKE_CURRENT_BINARY_DIR}/matrix_multiply.bc -o ${CMAKE_CURRENT_BINARY_DIR}/matrix_multiply.pim
  )
else()
  message(WARNING "Clang not found, skipping test compilation")
endif()
