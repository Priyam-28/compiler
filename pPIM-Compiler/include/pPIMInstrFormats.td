//===-- pPIMInstrFormats.td - pPIM Instruction Formats ------*- tablegen -*-===//

// Basic instruction format (19-bit)
class pPIMInst<bits<2> op, dag outs, dag ins, string asmStr, list<dag> pattern> 
  : Instruction {
  field bits<19> Inst;
  
  // Instruction fields
  bits<2> Opcode = op;      // Bits 18-17
  bits<6> ReadCorePtrField; // Bits 16-11
  bits<1> RdBit;            // Bit 10
  bits<1> WrBit;            // Bit 9
  bits<9> RowAddrField;     // Bits 8-0
  
  // Instruction encoding
  let Inst{18-17} = Opcode;
  let Inst{16-11} = ReadCorePtrField;
  let Inst{10} = RdBit;
  let Inst{9} = WrBit;
  let Inst{8-0} = RowAddrField;
  
  let Namespace = "pPIM";
  let OutOperandList = outs;
  let InOperandList = ins;
  let AsmString = asmStr;
  let Pattern = pattern;
}

// Memory Access Instruction
class MemoryInst<bit read, bit write, dag outs, dag ins, string asmStr, list<dag> pattern>
  : pPIMInst<0b00, outs, ins, asmStr, pattern> {
  let RdBit = read;
  let WrBit = write;
}

// LUT Programming Instruction
class LUTProgramInst<dag outs, dag ins, string asmStr, list<dag> pattern>
  : pPIMInst<0b01, outs, ins, asmStr, pattern> {
}

// Compute Instruction
class ComputeInst<dag outs, dag ins, string asmStr, list<dag> pattern>
  : pPIMInst<0b10, outs, ins, asmStr, pattern> {
}

// Define specific instructions
def LOADROW : MemoryInst<1, 0,
                        (outs),
                        (ins i9imm:$row_addr, i6imm:$buffer_ptr),
                        "loadrow $row_addr, $buffer_ptr",
                        []>;

def STOREROW : MemoryInst<0, 1,
                         (outs),
                         (ins i9imm:$row_addr, i6imm:$buffer_ptr),
                         "storerow $row_addr, $buffer_ptr",
                         []>;

def PROGMAC8 : LUTProgramInst<(outs),
                             (ins i6imm:$core_id),
                             "progmac8 $core_id",
                             []>;

def MAC8 : ComputeInst<(outs),
                      (ins i6imm:$src_ptr, i6imm:$dst_ptr),
                      "mac8 $src_ptr, $dst_ptr",
                      []>;