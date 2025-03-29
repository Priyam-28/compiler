#ifndef PPIM_INSTR_INFO_H
#define PPIM_INSTR_INFO_H

#include <cstdint>

namespace pPIM {

// ============== 24-bit Instruction Format ==============
// | 2-bit TYPE | 6-bit CORE_PTR | 6-bit UNUSED | 10-bit MEM_ACCESS |
// | OPCODE     | LUT/Cluster ID | (Reserved)   | R | W | ROW_ADDR  |
// ====================================================

// Field Positions
static const unsigned TYPE_POS     = 22;
static const unsigned CORE_PTR_POS = 16;
static const unsigned MEM_RD_POS   = 9;
static const unsigned MEM_WR_POS   = 8;
static const unsigned ROW_ADDR_POS = 0;

// Field Widths
static const unsigned TYPE_WIDTH     = 2;
static const unsigned CORE_PTR_WIDTH = 6;
static const unsigned MEM_RD_WIDTH   = 1;
static const unsigned MEM_WR_WIDTH   = 1;
static const unsigned ROW_ADDR_WIDTH = 9;

// Instruction Types
enum class InstrType {
  MEM_ACCESS = 0b00,  // DRAM row access (R/W)
  LUT_PROG   = 0b01,  // Program LUTs in a cluster
  COMPUTE    = 0b10,  // Execute arithmetic/logic op
  END        = 0b11   // Terminate operation
};

class Instruction {
public:
  Instruction() : value(0) {}

  // ---- Operation Segment (Upper 8 bits) ----
  void setType(InstrType type) {
    value &= ~(((1 << TYPE_WIDTH) - 1) << TYPE_POS);
    value |= (static_cast<uint32_t>(type) << TYPE_POS);
  }

  void setCorePtr(uint8_t core) {
    value &= ~(((1 << CORE_PTR_WIDTH) - 1) << CORE_PTR_POS);
    value |= ((core & ((1 << CORE_PTR_WIDTH) - 1)) << CORE_PTR_POS);
  }

  // ---- Memory Segment (Lower 10 bits) ----
  void setMemAccess(bool read, bool write, uint16_t rowAddr) {
    value &= ~((1 << MEM_RD_POS) | (1 << MEM_WR_POS) | ((1 << ROW_ADDR_WIDTH) - 1));
    if (read)  value |= (1 << MEM_RD_POS);
    if (write) value |= (1 << MEM_WR_POS);
    value |= (rowAddr & ((1 << ROW_ADDR_WIDTH) - 1));
  }

  // Instruction Builders
  static Instruction createMemAccess(bool rd, bool wr, uint16_t rowAddr) {
    Instruction inst;
    inst.setType(InstrType::MEM_ACCESS);
    inst.setMemAccess(rd, wr, rowAddr);
    return inst;
  }

  static Instruction createLUTProg(uint8_t coreId) {
    Instruction inst;
    inst.setType(InstrType::LUT_PROG);
    inst.setCorePtr(coreId);
    return inst;
  }

  static Instruction createCompute(uint8_t opCode) {
    Instruction inst;
    inst.setType(InstrType::COMPUTE);
    inst.setCorePtr(opCode);
    return inst;
  }

  static Instruction createEnd() {
    Instruction inst;
    inst.setType(InstrType::END);
    return inst;
  }

  uint32_t getBinary() const { return value & 0xFFFFFF; } // 24-bit mask

private:
  uint32_t value;  // Stored as 32-bit, but only 24 bits are used
};

} // namespace pPIM
#endif