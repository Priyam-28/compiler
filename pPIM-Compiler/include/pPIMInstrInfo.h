#ifndef PPIM_INSTR_INFO_H
#define PPIM_INSTR_INFO_H

#include <cstdint>
#include <string>
#include <vector>

namespace pPIM {

// Instruction field positions
static const unsigned OPCODE_POS = 17;
static const unsigned READ_CORE_PTR_POS = 11;
static const unsigned RD_BIT_POS = 10;
static const unsigned WR_BIT_POS = 9;
static const unsigned ROW_ADDR_POS = 0;

// Instruction field widths
static const unsigned OPCODE_WIDTH = 2;
static const unsigned READ_CORE_PTR_WIDTH = 6;
static const unsigned RD_BIT_WIDTH = 1;
static const unsigned WR_BIT_WIDTH = 1;
static const unsigned ROW_ADDR_WIDTH = 9;

// Opcodes
enum class Opcode {
  MEMORY_ACCESS = 0b00,
  LUT_PROGRAM = 0b01,
  COMPUTE = 0b10,
  CONTROL = 0b11
};

// Instruction class
class Instruction {
public:
  Instruction() : value(0) {}
  
  // Set fields
  void setOpcode(Opcode op) {
    value &= ~(((1 << OPCODE_WIDTH) - 1) << OPCODE_POS);
    value |= (static_cast<uint32_t>(op) << OPCODE_POS);
  }
  
  void setReadCorePtr(uint32_t ptr) {
    value &= ~(((1 << READ_CORE_PTR_WIDTH) - 1) << READ_CORE_PTR_POS);
    value |= ((ptr & ((1 << READ_CORE_PTR_WIDTH) - 1)) << READ_CORE_PTR_POS);
  }
  
  void setRdBit(bool rd) {
    value &= ~(1 << RD_BIT_POS);
    if (rd) value |= (1 << RD_BIT_POS);
  }
  
  void setWrBit(bool wr) {
    value &= ~(1 << WR_BIT_POS);
    if (wr) value |= (1 << WR_BIT_POS);
  }
  
  void setRowAddr(uint32_t addr) {
    value &= ~(((1 << ROW_ADDR_WIDTH) - 1) << ROW_ADDR_POS);
    value |= ((addr & ((1 << ROW_ADDR_WIDTH) - 1)) << ROW_ADDR_POS);
  }
  
  // Get the binary representation
  uint32_t getBinary() const { return value; }
  
  // Instruction builders
  static Instruction createLoad(uint32_t rowAddr, uint32_t bufferPtr) {
    Instruction inst;
    inst.setOpcode(Opcode::MEMORY_ACCESS);
    inst.setReadCorePtr(bufferPtr);
    inst.setRdBit(true);
    inst.setWrBit(false);
    inst.setRowAddr(rowAddr);
    return inst;
  }
  
  static Instruction createStore(uint32_t rowAddr, uint32_t bufferPtr) {
    Instruction inst;
    inst.setOpcode(Opcode::MEMORY_ACCESS);
    inst.setReadCorePtr(bufferPtr);
    inst.setRdBit(false);
    inst.setWrBit(true);
    inst.setRowAddr(rowAddr);
    return inst;
  }
  
  static Instruction createLUTProgram(uint32_t coreId) {
    Instruction inst;
    inst.setOpcode(Opcode::LUT_PROGRAM);
    inst.setReadCorePtr(coreId);
    return inst;
  }
  
  static Instruction createCompute(uint32_t srcPtr, uint32_t dstPtr) {
    Instruction inst;
    inst.setOpcode(Opcode::COMPUTE);
    inst.setReadCorePtr(srcPtr);
    inst.setRowAddr(dstPtr);
    return inst;
  }
  
private:
  uint32_t value;
};

} // namespace pPIM

#endif // PPIM_INSTR_INFO_H