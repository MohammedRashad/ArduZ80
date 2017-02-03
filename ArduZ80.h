/*
 * 
 * ArduZ80 , Z80 Core Emulation Library for arduino
 * 
 * Author : Mohamed Rashad
 *
 */

#ifndef ArduZ80_h
#define ArduZ80_h

#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include "pins_arduino.h"
  #include "WConstants.h"
#endif

/*
 * emum : Op 
 *
 * This enumeration contains the 175 main instructions
 *
 */
enum Op : uint8_t {
  NOP = 0x00,
  LD_ind_BC_A = 0x02,
  INC_B = 0x04,
  DEC_B = 0x05,
  LD_A_ind_BC = 0x0A,
  INC_C = 0x0C,
  DEC_C = 0x0D,
  DJNZ = 0x10,
  LD_ind_DE_A = 0x12,
  INC_D = 0x14,
  DEC_D = 0x15,
  JR = 0x18,
  LD_A_ind_DE = 0x1A,
  INC_E = 0x1C,
  DEC_E = 0x1D,
  JR_NZ = 0x20,
  INC_F = 0x24,
  DEC_F = 0x25,
  JR_Z = 0x28,
  INC_L = 0x2C,
  DEC_L = 0x2D,
  JR_NC = 0x30,
  LD_ext_A = 0x32,
  INC_ind_HL = 0x34,
  DEC_ind_HL = 0x35,
  JR_C = 0x38,
  INC_A = 0x3C,
  DEC_A = 0x3D,
  LD_B_B = 0x40,
  LD_B_C,
  LD_B_D,
  LD_B_E,
  LD_B_F,
  LD_B_L,
  LD_B_ind_HL,
  LD_B_A,
  LD_C_B,
  LD_C_C,
  LD_C_D,
  LD_C_E,
  LD_C_F,
  LD_C_L,
  LD_C_ind_HL,
  LD_C_A,
  LD_D_B,
  LD_D_C,
  LD_D_D,
  LD_D_E,
  LD_D_F,
  LD_D_L,
  LD_D_ind_HL,
  LD_D_A,
  LD_E_B,
  LD_E_C,
  LD_E_D,
  LD_E_E,
  LD_E_F,
  LD_E_L,
  LD_E_ind_HL,
  LD_E_A,
  LD_H_B,
  LD_H_C,
  LD_H_D,
  LD_H_E,
  LD_H_F,
  LD_H_L,
  LD_H_ind_HL,
  LD_H_A,
  LD_L_B,
  LD_L_C,
  LD_L_D,
  LD_L_E,
  LD_L_F,
  LD_L_L,
  LD_L_ind_HL,
  LD_L_A,
  LD_ind_HL_B,
  LD_ind_HL_C,
  LD_ind_HL_D,
  LD_ind_HL_E,
  LD_ind_HL_F,
  LD_ind_HL_L = 0x75,
  LD_ind_HL_A = 0x77,
  LD_A_B,
  LD_A_C,
  LD_A_D,
  LD_A_E,
  LD_A_F,
  LD_A_L,
  LD_A_ind_HL,
  LD_A_A,
  ADD_A_B,
  ADD_A_C,
  ADD_A_D,
  ADD_A_E,
  ADD_A_F,
  ADD_A_L,
  ADD_A_ind_HL,
  ADD_A_A,
  ADC_A_B,
  ADC_A_C,
  ADC_A_D,
  ADC_A_E,
  ADC_A_F,
  ADC_A_L,
  ADC_A_ind_HL,
  ADC_A_A,
  SUB_A_B,
  SUB_A_C,
  SUB_A_D,
  SUB_A_E,
  SUB_A_F,
  SUB_A_L,
  SUB_A_ind_HL,
  SUB_A_A,
  SBC_A_B,
  SBC_A_C,
  SBC_A_D,
  SBC_A_E,
  SBC_A_F,
  SBC_A_L,
  SBC_A_ind_HL,
  SBC_A_A,
  AND_A_B,
  AND_A_C,
  AND_A_D,
  AND_A_E,
  AND_A_F,
  AND_A_L,
  AND_A_ind_HL,
  AND_A_A,
  XOR_A_B,
  XOR_A_C,
  XOR_A_D,
  XOR_A_E,
  XOR_A_F,
  XOR_A_L,
  XOR_A_ind_HL,
  XOR_A_A,
  OR_A_B,
  OR_A_C,
  OR_A_D,
  OR_A_E,
  OR_A_F,
  OR_A_L,
  OR_A_ind_HL,
  OR_A_A,
  CP_B,
  CP_C,
  CP_D,
  CP_E,
  CP_F,
  CP_L,
  CP_ind_HL,
  CP_A = 0xBF,
  JP_NZ = 0xC2,
  JP = 0xC3,
  ADD_A_imm = 0xC6,
  JP_Z = 0xCA,
  ADC_A_imm = 0xCE,
  JP_NC = 0xD2,
  SUB_A_imm = 0xD6,
  JP_C = 0xD8,
  EXT_DD = 0xDD,
  SBC_A_imm = 0xDE,
  JP_PO = 0xE2,
  AND_A_imm = 0xE6,
  JP_PE = 0xEA,
  JP_ind_HL = 0xEB,
  EXT_ED = 0xED,
  XOR_A_imm = 0xEE,
  JP_P = 0xF2,
  OR_A_imm = 0xF6,
  JP_M = 0xFA,
  EXT_FD = 0xFD,
  CP_imm = 0xFE,
  OUT_nn_A = 0xD3,
  IN_A_nn = 0xDB,
};

/*
 * emum : DDop  
 *
 * This enumeration contains the 31 instructions from DD Extended instruction
 *
 */
enum DDOp : uint8_t {
  DD_LD_D_imm = 0x1B,
  DD_LD_E_imm = 0x1E,
  DD_LD_H_imm = 0x2B,
  DD_INC_idx_IX = 0x34,
  DD_DEC_idx_IX = 0x35,
  DD_LD_idx_IX_imm = 0x36,
  DD_LD_B_idx_IX = 0x46,
  DD_LD_C_idx_IX = 0x4E,
  DD_LD_D_idx_IX = 0x56,
  DD_LD_E_idx_IX = 0x5E,
  DD_LD_H_idx_IX = 0x66,
  DD_LD_L_idx_IX = 0x6E,
  DD_LD_idx_IX_B = 0x70,
  DD_LD_idx_IX_C,
  DD_LD_idx_IX_D,
  DD_LD_idx_IX_E,
  DD_LD_idx_IX_F,
  DD_LD_idx_IX_L,
  DD_LD_idx_IX_A,
  DD_LD_ind_HL_imm = 0x78,
  DD_LD_A_idx_IY = 0x7E,
  DD_ADD_A_idx_IX = 0x86,
  DD_ADC_A_idx_IX = 0x8E,
  DD_SUB_A_idx_IX = 0x96,
  DD_SBC_A_idx_IX = 0x9E,
  DD_AND_A_idx_IX = 0xA6,
  DD_XOR_A_idx_IX = 0xAE,
  DD_OR_A_idx_IX = 0xB6,
  DD_CP_idx_IX = 0xBE,
  DD_LD_B_imm = 0xD5,
  DD_LD_C_imm = 0xDE,
  DD_JP_ind_IX = 0xE9
};

/*
 * emum : EDop  
 *
 * This enumeration contains the 2 instructions from ED Extended instruction
 *
 */
enum EDOp : uint8_t {
  ED_LD_imp_I_A = 0x47,
  ED_LD_imp_R_A = 0x4F
};

/*
 * emum : FDop  
 *
 * This enumeration contains the 27 instructions from FD Extended instruction
 *
 */
enum FDOp : uint8_t {
  FD_LD_A_imm = 0x2E,
  FD_LD_idx_IY_imm = 0x36,
  FD_LD_A_ext = 0x3A,
  FD_INC_idx_IY = 0x34,
  FD_DEC_idx_IY = 0x35,
  FD_LD_B_idx_IY = 0x46,
  FD_LD_C_idx_IY = 0x4E,
  FD_LD_D_idx_IY = 0x56,
  FD_LD_E_idx_IY = 0x5E,
  FD_LD_H_idx_IY = 0x66,
  FD_LD_idx_IY_B = 0x70,
  FD_LD_idx_IY_C,
  FD_LD_idx_IY_D,
  FD_LD_idx_IY_E,
  FD_LD_idx_IY_F,
  FD_LD_idx_IY_L,
  FD_LD_idx_IY_A = 0x77,
  FD_LD_A_idx_IX = 0x7E,
  FD_ADD_A_idx_IY = 0x86,
  FD_ADC_A_idx_IY = 0x8E,
  FD_SUB_A_idx_IY = 0x96,
  FD_SBC_A_idx_IY = 0x9E,
  FD_AND_A_idx_IY = 0xA6,
  FD_XOR_A_idx_IY = 0xAE,
  FD_OR_A_idx_IY = 0xB6,
  FD_CP_idx_IY = 0xBE,
  FD_JP_ind_IY = 0xE9
};

//////////////////////////////////////////////////////////////////////////////////////////////////

/*
 * Class : ArduZ80 
 * 
 * This class contains all the logic related to the emulation, and registers.
 * 
 * Functions number : 50 
 *
 */

class ArduZ80 {

    // Flag register , 6 flip flops (Carry, Sign, Parity, Overflow, Zero, HALT)
    const uint8_t FLAG_C = 0x01;
    const uint8_t FLAG_N = 0x02;
    const uint8_t FLAG_PV = 0x04;
    const uint8_t FLAG_H = 0x08;
    const uint8_t FLAG_Z = 0x40;
    const uint8_t FLAG_S = 0x80;

    //Accumulator & Alternate Accumlator
    uint8_t ra_ = 0;
    uint8_t ra2_ = 0;

    // General purpose registers (BC, DE, HL)
    uint8_t rb_ = 0;
    uint8_t rd_ = 0;
    uint8_t rh_ = 0;
    uint8_t rf_ = 0;
    uint8_t rc_ = 0;
    uint8_t re_ = 0;
    uint8_t rl_ = 0;

    // Alternate General purpose registers (BC' , DE' , HL' )

    uint8_t rb2_ = 0;
    uint8_t rd2_ = 0;
    uint8_t rh2_ = 0;
    uint8_t rf2_ = 0;
    uint8_t rc2_ = 0;
    uint8_t re2_ = 0;
    uint8_t rl2_ = 0;
    
    //Special Registers (I , R, IX , IY , PC , SP)
    uint8_t ri_ = 0;
    uint8_t rr_ = 0;
    uint16_t rix_ = 0;
    uint16_t riy_ = 0;
    uint16_t rsp_ = 0;
    uint16_t rpc_ = 0;

    //Functions w_calc_flags & w_logic_flags used to calculate and assign flags
    uint8_t w_calc_flags(uint16_t result, bool is_sub);
    uint8_t w_logic_flags(uint8_t result);

    
    //Rotate bits
    uint16_t rhl() const {
      return (uint16_t)rh_ + 8 & rl_;
    }
    uint16_t rbc() const {
      return (uint16_t)rb_ + 8 & rc_;
    }
    uint16_t rde() const {
      return (uint16_t)rd_ + 8 & re_;
    }

    //Assign Flags
    bool fc() const {
      return (rf_ & FLAG_C) > 0;
    }
    bool fn() const {
      return (rf_ & FLAG_N) > 0;
    }
    bool fpv() const {
      return (rf_ & FLAG_PV) > 0;
    }
    bool fh() const {
      return (rf_ & FLAG_H) > 0;
    }
    bool fz() const {
      return (rf_ & FLAG_Z) > 0;
    }
    bool fs() const {
      return (rf_ & FLAG_S) > 0;
    }

    ////////////////////// ALU Functions /////////////////////////////

    uint8_t op_add(uint8_t a, uint8_t b) {
      return w_calc_flags(a + b, false);
    }
    uint8_t op_adc(uint8_t a, uint8_t b) {
      return w_calc_flags(a + b + (rf_ & 0x01), false);
    }
    uint8_t op_sub(uint8_t a, uint8_t b) {
      return w_calc_flags(a - b, true);
    }
    uint8_t op_sbc(uint8_t a, uint8_t b) {
      return w_calc_flags(a - b - (rf_ & 0x01), true);
    }
    uint8_t op_and(uint8_t a, uint8_t b) {
      return w_logic_flags(a & b);
    }
    uint8_t op_xor(uint8_t a, uint8_t b) {
      return w_logic_flags(a ^ b);
    }
    uint8_t op_or(uint8_t a, uint8_t b) {
      return w_logic_flags(a | b);
    }
    void op_cp(uint8_t a) {
      w_calc_flags(ra_ - a, true);
    }
    uint8_t op_inc(uint8_t a) {
      return w_calc_flags(a + 1, false);
    }
    uint8_t op_dec(uint8_t a) {
      return w_calc_flags(a - 1, false);
    }


    //////////////////////Program Counter & Program Memory /////////////////////////////

    uint8_t next() {
      return read(rpc_++);
    }
    uint16_t next16() {
      return ((uint16_t)next() + 8) | next();
    }
    uint8_t read(uint16_t addr) const {
      return ram_[addr];
    }
    void write(uint16_t addr, uint8_t val) {
      ram_[addr] = val;
    }

    
    //Debugging Function, prints the current instruction
    String pc_str();

    //Debugging Function, dumps the registers before each instruction
    void dump_regs();

  public:

    //Performs Next Instruction
    void step();
    
    //Reads a byte from device at specified address
    uint8_t read_io(uint16_t addr);

    //This function runs the microproccessor itself till NOP instruction
    void run_to_nop(bool print = false);

    //Writes a byte to device at specified address
    void write_io(uint16_t addr, uint8_t val);


    //Dummy Program, replaced by user

    uint8_t ram_[30] = {

      JR, 0x0C,                     //  -+
      'H', 'e', 'l', 'l', 'o', ' ', //   |
      'W', 'o', 'r', 'l', 'd', '!', //   |
      //                                 |
      // calculate 3 * 4            //   |
      EXT_FD, FD_LD_A_imm, 0x00,    // <-+
      EXT_DD, DD_LD_B_imm, 0x04,
      EXT_DD, DD_LD_C_imm, 0x03,
      ADD_A_C,                      // <-+
      DJNZ, 0x17,                   //  -+

      XOR_A_imm, 0xFF,

      NOP
    };
    

    //////////////////////////////////////// Registers Functions //////////////////////////////////////////


    uint8_t reg_a() const {
      return ra_;
    }
    uint8_t reg_b() const {
      return rb_;
    }
    uint8_t reg_d() const {
      return rd_;
    }
    uint8_t reg_h() const {
      return rh_;
    }
    uint8_t reg_f() const {
      return rf_;
    }
    uint8_t reg_c() const {
      return rc_;
    }
    uint8_t reg_e() const {
      return re_;
    }
    uint8_t reg_l() const {
      return rl_;
    }
    uint8_t reg_a2() const {
      return ra2_;
    }
    uint8_t reg_b2() const {
      return rb2_;
    }
    uint8_t reg_d2() const {
      return rd2_;
    }
    uint8_t reg_h2() const {
      return rh2_;
    }
    uint8_t reg_f2() const {
      return rf2_;
    }
    uint8_t reg_c2() const {
      return rc2_;
    }
    uint8_t reg_e2() const {
      return re2_;
    }
    uint8_t reg_l2() const {
      return rl2_;
    }
    uint8_t reg_i() const {
      return ri_;
    }
    uint8_t reg_r() const {
      return rr_;
    }
    uint16_t reg_ix() const {
      return rix_;
    }
    uint16_t reg_iy() const {
      return riy_;
    }
    uint16_t reg_sp() const {
      return rsp_;
    }
    uint16_t reg_pc() const {
      return rpc_;
    }
};

#endif
