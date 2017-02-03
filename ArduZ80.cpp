/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

#include "ArduZ80.h"

/*
 *
 *
 *
 *
 *
 *
 *
 *
 */
uint8_t ArduZ80::w_calc_flags(uint16_t result, bool is_sub) {
  rf_ = 0;

  if (result & 0x0100) rf_ |= FLAG_C;
  if (is_sub) rf_ |= FLAG_N;
  if (result > 0xFF) rf_ |= FLAG_PV;
  if (result & 0x08) rf_ |= FLAG_H;
  if (!result) rf_ |= FLAG_Z;
  if (result & 0x80) rf_ |= FLAG_S;

  return (uint8_t)result;

}

/*
 *
 *
 *
 *
 *
 *
 *
 *
 */
uint8_t ArduZ80::w_logic_flags(uint8_t result) {

  rf_ = 0;

  uint8_t x = result;

  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;

  bool parity = (~x) & 0x01;

  if (parity) rf_ |= FLAG_PV;
  if (!result) rf_ |= FLAG_Z;
  if (result & 0x80) rf_ |= FLAG_S;

  return result;

}


/*
 * 
 *
 *
 *
 *
 *
 *
 *
 */
String ArduZ80::pc_str() {

  uint8_t old_pc = rpc_;
  uint8_t code;
  String str;

  switch (code = next()) {
    case NOP: str = "nop"; break;
    case LD_A_A: str = "ld a, a"; break;
    case LD_A_B: str = "ld a, b"; break;
    case LD_A_C: str = "ld a, c"; break;
    case LD_A_D: str = "ld a, d"; break;
    case LD_A_E: str = "ld a, e"; break;
    case LD_A_F: str = "ld a, f"; break;
    case LD_A_L: str = "ld a, l"; break;
    case LD_B_A: str = "ld b, a"; break;
    case LD_B_B: str = "ld b, b"; break;
    case LD_B_C: str = "ld b, c"; break;
    case LD_B_D: str = "ld b, d"; break;
    case LD_B_E: str = "ld b, e"; break;
    case LD_B_F: str = "ld b, f"; break;
    case LD_B_L: str = "ld b, l"; break;
    case LD_C_A: str = "ld c, a"; break;
    case LD_C_B: str = "ld c, b"; break;
    case LD_C_C: str = "ld c, c"; break;
    case LD_C_D: str = "ld c, d"; break;
    case LD_C_E: str = "ld c, e"; break;
    case LD_C_F: str = "ld c, f"; break;
    case LD_C_L: str = "ld c, l"; break;
    case LD_D_A: str = "ld d, a"; break;
    case LD_D_B: str = "ld d, b"; break;
    case LD_D_C: str = "ld d, c"; break;
    case LD_D_D: str = "ld d, d"; break;
    case LD_D_E: str = "ld d, e"; break;
    case LD_D_F: str = "ld d, f"; break;
    case LD_D_L: str = "ld d, l"; break;
    case LD_E_A: str = "ld e, a"; break;
    case LD_E_B: str = "ld e, b"; break;
    case LD_E_C: str = "ld e, c"; break;
    case LD_E_D: str = "ld e, d"; break;
    case LD_E_E: str = "ld e, e"; break;
    case LD_E_F: str = "ld e, f"; break;
    case LD_E_L: str = "ld e, l"; break;
    case LD_H_A: str = "ld h, a"; break;
    case LD_H_B: str = "ld h, b"; break;
    case LD_H_C: str = "ld h, c"; break;
    case LD_H_D: str = "ld h, d"; break;
    case LD_H_E: str = "ld h, e"; break;
    case LD_H_F: str = "ld h, f"; break;
    case LD_H_L: str = "ld h, l"; break;
    case LD_L_A: str = "ld l, a"; break;
    case LD_L_B: str = "ld l, b"; break;
    case LD_L_C: str = "ld l, c"; break;
    case LD_L_D: str = "ld l, d"; break;
    case LD_L_E: str = "ld l, e"; break;
    case LD_L_F: str = "ld l, f"; break;
    case LD_L_L: str = "ld l, l"; break;
    case LD_A_ind_HL: str = "ld a, (hl)"; break;
    case LD_A_ind_BC: str = "ld a, (bc)"; break;
    case LD_A_ind_DE: str = "ld a, (de)"; break;
    case LD_B_ind_HL: str = "ld b, (hl)"; break;
    case LD_C_ind_HL: str = "ld c, (hl)"; break;
    case LD_D_ind_HL: str = "ld d, (hl)"; break;
    case LD_E_ind_HL: str = "ld e, (hl)"; break;
    case LD_H_ind_HL: str = "ld h, (hl)"; break;
    case LD_L_ind_HL: str = "ld l, (hl)"; break;
    case LD_ind_HL_A: str = "ld (hl), a"; break;
    case LD_ind_HL_B: str = "ld (hl), b"; break;
    case LD_ind_HL_C: str = "ld (hl), c"; break;
    case LD_ind_HL_D: str = "ld (hl), d"; break;
    case LD_ind_HL_E: str = "ld (hl), e"; break;
    case LD_ind_HL_F: str = "ld (hl), f"; break;
    case LD_ind_HL_L: str = "ld (hl), l"; break;
    case LD_ind_BC_A: str = "ld (bc), a"; break;
    case LD_ind_DE_A: str = "ld (de), a"; break;
    case LD_ext_A: str = "ld (0x" + (String) next16() + "), a"; break;
    case ADD_A_A: str = "add a, a"; break;
    case ADD_A_B: str = "add a, b"; break;
    case ADD_A_C: str = "add a, c"; break;
    case ADD_A_D: str = "add a, d"; break;
    case ADD_A_E: str = "add a, e"; break;
    case ADD_A_F: str = "add a, f"; break;
    case ADD_A_L: str = "add a, l"; break;
    case ADD_A_ind_HL: str = "add a, (hl)"; break;
    case ADD_A_imm: str = "add a, 0x"  + (String)next(); break;
    case ADC_A_A: str = "adc a, a"; break;
    case ADC_A_B: str = "adc a, b"; break;
    case ADC_A_C: str = "adc a, c"; break;
    case ADC_A_D: str = "adc a, d"; break;
    case ADC_A_E: str = "adc a, e"; break;
    case ADC_A_F: str = "adc a, f"; break;
    case ADC_A_L: str = "adc a, l"; break;
    case ADC_A_ind_HL: str = "adc a, (hl)"; break;
    case ADC_A_imm: str = "adc a, 0x"  + (String)next(); break;
    case SUB_A_A: str = "sub a, a"; break;
    case SUB_A_B: str = "sub a, b"; break;
    case SUB_A_C: str = "sub a, c"; break;
    case SUB_A_D: str = "sub a, d"; break;
    case SUB_A_E: str = "sub a, e"; break;
    case SUB_A_F: str = "sub a, f"; break;
    case SUB_A_L: str = "sub a, l"; break;
    case SUB_A_ind_HL: str = "sub a, (hl)"; break;
    case SUB_A_imm: str = "sub a, 0x"  + (String)next(); break;
    case SBC_A_A: str = "sbc a, a"; break;
    case SBC_A_B: str = "sbc a, b"; break;
    case SBC_A_C: str = "sbc a, c"; break;
    case SBC_A_D: str = "sbc a, d"; break;
    case SBC_A_E: str = "sbc a, e"; break;
    case SBC_A_F: str = "sbc a, f"; break;
    case SBC_A_L: str = "sbc a, l"; break;
    case SBC_A_ind_HL: str = "sbc a, (hl)"; break;
    case SBC_A_imm: str = "sbc a, 0x"  + (String)next(); break;
    case AND_A_A: str = "and a, a"; break;
    case AND_A_B: str = "and a, b"; break;
    case AND_A_C: str = "and a, c"; break;
    case AND_A_D: str = "and a, d"; break;
    case AND_A_E: str = "and a, e"; break;
    case AND_A_F: str = "and a, f"; break;
    case AND_A_L: str = "and a, l"; break;
    case AND_A_ind_HL: str = "and a, (hl)"; break;
    case AND_A_imm: str = "and a, 0x"  + (String)next(); break;
    case XOR_A_A: str = "xor a, a"; break;
    case XOR_A_B: str = "xor a, b"; break;
    case XOR_A_C: str = "xor a, c"; break;
    case XOR_A_D: str = "xor a, d"; break;
    case XOR_A_E: str = "xor a, e"; break;
    case XOR_A_F: str = "xor a, f"; break;
    case XOR_A_L: str = "xor a, l"; break;
    case XOR_A_ind_HL: str = "xor a, (hl)"; break;
    case XOR_A_imm: str = "xor a, 0x"  + (String)next(); break;
    case OR_A_A: str = "or a, a"; break;
    case OR_A_B: str = "or a, b"; break;
    case OR_A_C: str = "or a, c"; break;
    case OR_A_D: str = "or a, d"; break;
    case OR_A_E: str = "or a, e"; break;
    case OR_A_F: str = "or a, f"; break;
    case OR_A_L: str = "or a, l"; break;
    case OR_A_ind_HL: str = "or a, (hl)"; break;
    case OR_A_imm: str = "or a, 0x"  + (String)next(); break;
    case CP_A: str = "cp a"; break;
    case CP_B: str = "cp b"; break;
    case CP_C: str = "cp c"; break;
    case CP_D: str = "cp d"; break;
    case CP_E: str = "cp e"; break;
    case CP_F: str = "cp f"; break;
    case CP_L: str = "cp l"; break;
    case CP_ind_HL: str = "cp (hl)"; break;
    case CP_imm: str = "cp 0x"  + (String)next(); break;
    case INC_A: str = "inc a"; break;
    case INC_B: str = "inc b"; break;
    case INC_C: str = "inc c"; break;
    case INC_D: str = "inc d"; break;
    case INC_E: str = "inc e"; break;
    case INC_F: str = "inc f"; break;
    case INC_L: str = "inc l"; break;
    case INC_ind_HL: str = "inc (hl)"; break;
    case DEC_A: str = "dec a"; break;
    case DEC_B: str = "dec b"; break;
    case DEC_C: str = "dec c"; break;
    case DEC_D: str = "dec d"; break;
    case DEC_E: str = "dec e"; break;
    case DEC_F: str = "dec f"; break;
    case DEC_L: str = "dec l"; break;
    case DEC_ind_HL: str = "dec (hl)"; break;
    case JP: str = "jp 0x"  + next16(); break;
    case JP_C: str = "jp c, 0x"  + next16(); break;
    case JP_NC: str = "jp nc, 0x"  + next16(); break;
    case JP_Z: str = "jp z, 0x"  + next16(); break;
    case JP_NZ: str = "jp nz, 0x"  + next16(); break;
    case JP_PO: str = "jp po, 0x"  + next16(); break;
    case JP_PE: str = "jp pe, 0x"  + next16(); break;
    case JP_M: str = "jp m, 0x"  + next16(); break;
    case JP_P: str = "jp p, 0x"  + next16(); break;
    case JP_ind_HL: str = "jp (hl)"; break;
    case JR: str = "jr 0x"  + (String)next(); break;
    case JR_C: str = "jr c, 0x"  + (String)next(); break;
    case JR_NC: str = "jr nc, 0x"  + (String)next(); break;
    case JR_Z: str = "jr z, 0x"  + (String)next(); break;
    case JR_NZ: str = "jr nz, 0x"  + (String)next(); break;
    case OUT_nn_A: str = "OUT nn,A ->  0x"  + (String)next(); break;
    case IN_A_nn: str = "IN  A,nn -> 0x"  + (String)next(); break;

    case EXT_DD:
      switch (code = next()) {
        case DD_LD_B_imm: str = "ld b, 0x"  + (String)next(); break;
        case DD_LD_C_imm: str = "ld c, 0x"  + (String)next(); break;
        case DD_LD_D_imm: str = "ld d, 0x"  + (String)next(); break;
        case DD_LD_E_imm: str = "ld e, 0x"  + (String)next(); break;
        case DD_LD_H_imm: str = "ld h, 0x"  + (String)next(); break;
        case DD_LD_A_idx_IY: str = "ld a, (iy + 0x"  + (String)next() + ")"; break;
        case DD_LD_B_idx_IX: str = "ld b, (ix + 0x"  + (String)next() + ")"; break;
        case DD_LD_C_idx_IX: str = "ld c, (ix + 0x"  + (String)next() + ")"; break;
        case DD_LD_D_idx_IX: str = "ld d, (ix + 0x"  + (String)next() + ")"; break;
        case DD_LD_E_idx_IX: str = "ld e, (ix + 0x"  + (String)next() + ")"; break;
        case DD_LD_H_idx_IX: str = "ld h, (ix + 0x"  + (String)next() + ")"; break;
        case DD_LD_L_idx_IX: str = "ld l, (ix + 0x"  + (String)next() + ")"; break;
        case DD_LD_idx_IX_A: str = "ld (ix + 0x"  + (String)next() + "), a"; break;
        case DD_LD_idx_IX_B: str = "ld (ix + 0x"  + (String)next() + "), b"; break;
        case DD_LD_idx_IX_C: str = "ld (ix + 0x"  + (String)next() + "), c"; break;
        case DD_LD_idx_IX_D: str = "ld (ix + 0x"  + (String)next() + "), d"; break;
        case DD_LD_idx_IX_E: str = "ld (ix + 0x"  + (String)next() + "), e"; break;
        case DD_LD_idx_IX_F: str = "ld (ix + 0x"  + (String)next() + "), f"; break;
        case DD_LD_idx_IX_L: str = "ld (ix + 0x"  + (String)next() + "), l"; break;
        case DD_LD_idx_IX_imm: str = "ld (ix + 0x"  + (String)next() + "), 0x"  + (String)next(); break;
        case DD_LD_ind_HL_imm: str = "ld (hl), 0x"  + (String)next(); break;
        case DD_ADD_A_idx_IX: str = "add a, (ix + 0x"  + (String)next() + ")"; break;
        case DD_ADC_A_idx_IX: str = "adc a, (ix + 0x"  + (String)next() + ")"; break;
        case DD_SUB_A_idx_IX: str = "sub a, (ix + 0x"  + (String)next() + ")"; break;
        case DD_SBC_A_idx_IX: str = "sbc a, (ix + 0x"  + (String)next() + ")"; break;
        case DD_AND_A_idx_IX: str = "and a, (ix + 0x"  + (String)next() + ")"; break;
        case DD_XOR_A_idx_IX: str = "xor a, (ix + 0x"  + (String)next() + ")"; break;
        case DD_OR_A_idx_IX: str = "or a, (ix + 0x"  + (String)next() + ")"; break;
        case DD_CP_idx_IX: str = "cp (ix + 0x"  + (String)next() + ")"; break;
        case DD_JP_ind_IX: str = "jp (ix)"; break;
        default: str = "0x" + (0xDD00 & code); break;
      }
      break;

    case EXT_ED:
      switch (next()) {
        case ED_LD_imp_I_A: str = "ld i, a"; break;
        case ED_LD_imp_R_A: str = "ld r, a"; break;
        default: str = "0x" + (0xED00 & code); break;
      }
      break;

    case EXT_FD:
      switch (code = next()) {
        case FD_LD_A_imm: str = "ld a, 0x"  + (String)next(); break;
        case FD_LD_A_ext: str = "ld a, (0x"  + (String)next16() + ")"; break;
        case FD_LD_A_idx_IX: str = "ld a, (ix + 0x"  + (String)next() + ")"; break;
        case FD_LD_B_idx_IY: str = "ld b, (iy + 0x"  + (String)next() + ")"; break;
        case FD_LD_C_idx_IY: str = "ld c, (iy + 0x"  + (String)next() + ")"; break;
        case FD_LD_D_idx_IY: str = "ld d, (iy + 0x"  + (String)next() + ")"; break;
        case FD_LD_E_idx_IY: str = "ld e, (iy + 0x"  + (String)next() + ")"; break;
        case FD_LD_H_idx_IY: str = "ld h, (iy + 0x"  + (String)next() + ")"; break;
        case FD_LD_idx_IY_A: str = "ld (iy + 0x"  + (String)next() + "), a"; break;
        case FD_LD_idx_IY_B: str = "ld (iy + 0x"  + (String)next() + "), b"; break;
        case FD_LD_idx_IY_C: str = "ld (iy + 0x"  + (String)next() + "), c"; break;
        case FD_LD_idx_IY_D: str = "ld (iy + 0x"  + (String)next() + "), d"; break;
        case FD_LD_idx_IY_E: str = "ld (iy + 0x"  + (String)next() + "), e"; break;
        case FD_LD_idx_IY_F: str = "ld (iy + 0x"  + (String)next() + "), f"; break;
        case FD_LD_idx_IY_L: str = "ld (iy + 0x"  + (String)next() + "), l"; break;
        case FD_LD_idx_IY_imm: str = "ld (iy + 0x"  + (String)next() + "), 0x"  + (String)next(); break;
        case FD_ADD_A_idx_IY: str = "add a, (iy + 0x"  + (String)next() + ")"; break;
        case FD_ADC_A_idx_IY: str = "adc a, (iy + 0x"  + (String)next() + ")"; break;
        case FD_SUB_A_idx_IY: str = "sub a, (iy + 0x"  + (String)next() + ")"; break;
        case FD_SBC_A_idx_IY: str = "sbc a, (iy + 0x"  + (String)next() + ")"; break;
        case FD_AND_A_idx_IY: str = "and a, (iy + 0x"  + (String)next() + ")"; break;
        case FD_XOR_A_idx_IY: str = "xor a, (iy + 0x"  + (String)next() + ")"; break;
        case FD_OR_A_idx_IY: str = "or a, (iy + 0x"  + (String)next() + ")"; break;
        case FD_CP_idx_IY: str = "cp (iy + 0x"  + (String)next() + ")"; break;
        case FD_JP_ind_IY: str = "jp (iy)"; break;
        default: str = "0x" + (0xFD00 & code); break;
      }
      break;

    default:
      str = "0x" + (String)code;;
      break;
  }

  rpc_ = old_pc;
  return str;
}

void ArduZ80::dump_regs()
{
  Serial.println("\n ");
  Serial.print("\n\nA: 0x"); Serial.print(ra_ );
  Serial.print("    F: 0x"); Serial.println(rf_);
  Serial.print("A': 0x"); Serial.print(ra2_ );
  Serial.print("    F': 0x"); Serial.println(rf2_ );
  Serial.println("\n");
  Serial.print("B: 0x"); Serial.print (rb_);
  Serial.print("    C: 0x"); Serial.println(rc_);
  Serial.print("B': 0x"); Serial.print(rb2_);
  Serial.print("    C': 0x"); Serial.println(rc2_ );
  Serial.println("\n");
  Serial.print("D: 0x"); Serial.print(rd_ );
  Serial.print("    E: 0x"); Serial.println(re_);
  Serial.print("D': 0x"); Serial.print(rd2_);
  Serial.print("    E': 0x"); Serial.println(re2_ );
  Serial.println("\n");
  Serial.print("H: 0x"); Serial.print(rh_);
  Serial.print("    L: 0x"); Serial.println(rl_);
  Serial.print("H': 0x"); Serial.print(rh2_);
  Serial.print("    L': 0x"); Serial.println(rl2_);
  Serial.println("\n");
  Serial.print( "I: 0x"); Serial.println(ri_);
  Serial.print("R: 0x" ); Serial.println(rr_);
  Serial.print("IX: 0x"); Serial.println(rix_);
  Serial.print("IY: 0x"); Serial.println(riy_);
  Serial.print("IY: 0x"); Serial.println(riy_);
  Serial.println("\n");
  Serial.print("SP: 0x"); Serial.println(rsp_);
  Serial.print("PC: 0x"); Serial.println(rpc_);
  Serial.println("\n");
  Serial.print("S: "); Serial.println(fs());
  Serial.print( "Z: "); Serial.println(fz());
  Serial.print("H: "); Serial.println(fh());
  Serial.print("PV: "); Serial.println(fpv());
  Serial.print("N: "); Serial.println(fn());
  Serial.print("C: "); Serial.println( fc());


}


/*
 *
 *
 *
 *
 *
 *
 *
 *
 */

void ArduZ80::step() {
  uint8_t tmp;
  uint16_t tmp16;

  uint8_t code;
  switch (code = next()) {
    case LD_A_A: break;
    case LD_A_B: ra_ = rb_; break;;
    case LD_A_C: ra_ = rc_; break;
    case LD_A_D: ra_ = rd_; break;
    case LD_A_E: ra_ = re_; break;
    case LD_A_F: ra_ = rf_; break;
    case LD_A_L: ra_ = rl_; break;
    case LD_B_A: rb_ = ra_; break;
    case LD_B_B: break;
    case LD_B_C: rb_ = rc_; break;
    case LD_B_D: rb_ = rd_; break;
    case LD_B_E: rb_ = re_; break;
    case LD_B_F: rb_ = rf_; break;
    case LD_B_L: rb_ = rl_; break;
    case LD_C_A: rc_ = ra_; break;
    case LD_C_B: rc_ = rb_; break;
    case LD_C_C: break;
    case LD_C_D: rc_ = rd_; break;
    case LD_C_E: rc_ = re_; break;
    case LD_C_F: rc_ = rf_; break;
    case LD_C_L: rc_ = rl_; break;
    case LD_D_A: rd_ = ra_; break;
    case LD_D_B: rd_ = rb_; break;
    case LD_D_C: rd_ = rc_; break;
    case LD_D_D: break;
    case LD_D_E: rd_ = re_; break;
    case LD_D_F: rd_ = rf_; break;
    case LD_D_L: rd_ = rl_; break;
    case LD_E_A: re_ = ra_; break;
    case LD_E_B: re_ = rb_; break;
    case LD_E_C: re_ = rc_; break;
    case LD_E_D: re_ = rd_; break;
    case LD_E_E: break;
    case LD_E_F: re_ = rf_; break;
    case LD_E_L: re_ = rl_; break;
    case LD_H_A: rh_ = ra_; break;
    case LD_H_B: rh_ = rb_; break;
    case LD_H_C: rh_ = rc_; break;
    case LD_H_D: rh_ = rd_; break;
    case LD_H_E: rh_ = re_; break;
    case LD_H_F: rh_ = rf_; break;
    case LD_H_L: rf_ = rl_; break;
    case LD_L_A: rl_ = ra_; break;
    case LD_L_B: rl_ = rb_; break;
    case LD_L_C: rl_ = rc_; break;
    case LD_L_D: rl_ = rd_; break;
    case LD_L_E: rl_ = re_; break;
    case LD_L_F: rl_ = rf_; break;
    case LD_L_L: break;
    case LD_A_ind_HL: ra_ = read(rhl()); break;
    case LD_A_ind_BC: ra_ = read(rbc()); break;
    case LD_A_ind_DE: ra_ = read(rde()); break;
    case LD_B_ind_HL: rb_ = read(rhl()); break;
    case LD_C_ind_HL: rc_ = read(rhl()); break;
    case LD_D_ind_HL: rd_ = read(rhl()); break;
    case LD_E_ind_HL: re_ = read(rhl()); break;
    case LD_H_ind_HL: rh_ = read(rhl()); break;
    case LD_L_ind_HL: rl_ = read(rhl()); break;
    case LD_ind_HL_A: write(rhl(), ra_); break;
    case LD_ind_HL_B: write(rhl(), rb_); break;
    case LD_ind_HL_C: write(rhl(), rc_); break;
    case LD_ind_HL_D: write(rhl(), rd_); break;
    case LD_ind_HL_E: write(rhl(), re_); break;
    case LD_ind_HL_F: write(rhl(), rf_); break;
    case LD_ind_HL_L: write(rhl(), rl_); break;
    case LD_ind_BC_A: write(rbc(), ra_); break;
    case LD_ind_DE_A: write(rde(), ra_); break;
    case LD_ext_A: write(next16(), ra_); break;
    case ADD_A_A: ra_ = op_add(ra_, ra_); break;
    case ADD_A_B: ra_ = op_add(ra_, rb_); break;
    case ADD_A_C: ra_ = op_add(ra_, rc_); break;
    case ADD_A_D: ra_ = op_add(ra_, rd_); break;
    case ADD_A_E: ra_ = op_add(ra_, re_); break;
    case ADD_A_F: ra_ = op_add(ra_, rf_); break;
    case ADD_A_L: ra_ = op_add(ra_, rl_); break;
    case ADD_A_ind_HL: ra_ = op_add(ra_, read(rhl())); break;
    case ADD_A_imm: ra_ = op_add(ra_, next()); break;
    case ADC_A_A: ra_ = op_adc(ra_, ra_); break;
    case ADC_A_B: ra_ = op_adc(ra_, rb_); break;
    case ADC_A_C: ra_ = op_adc(ra_, rc_); break;
    case ADC_A_D: ra_ = op_adc(ra_, rd_); break;
    case ADC_A_E: ra_ = op_adc(ra_, re_); break;
    case ADC_A_F: ra_ = op_adc(ra_, rf_); break;
    case ADC_A_L: ra_ = op_adc(ra_, rl_); break;
    case ADC_A_ind_HL: ra_ = op_adc(ra_, read(rhl())); break;
    case ADC_A_imm: ra_ = op_adc(ra_, next()); break;
    case SUB_A_A: ra_ = op_sub(ra_, ra_); break;
    case SUB_A_B: ra_ = op_sub(ra_, rb_); break;
    case SUB_A_C: ra_ = op_sub(ra_, rc_); break;
    case SUB_A_D: ra_ = op_sub(ra_, rd_); break;
    case SUB_A_E: ra_ = op_sub(ra_, re_); break;
    case SUB_A_F: ra_ = op_sub(ra_, rf_); break;
    case SUB_A_L: ra_ = op_sub(ra_, rl_); break;
    case SUB_A_ind_HL: ra_ = op_sub(ra_, read(rhl())); break;
    case SUB_A_imm: ra_ = op_sub(ra_, next()); break;
    case SBC_A_A: ra_ = op_sbc(ra_, ra_); break;
    case SBC_A_B: ra_ = op_sbc(ra_, rb_); break;
    case SBC_A_C: ra_ = op_sbc(ra_, rc_); break;
    case SBC_A_D: ra_ = op_sbc(ra_, rd_); break;
    case SBC_A_E: ra_ = op_sbc(ra_, re_); break;
    case SBC_A_F: ra_ = op_sbc(ra_, rf_); break;
    case SBC_A_L: ra_ = op_sbc(ra_, rl_); break;
    case SBC_A_ind_HL: ra_ = op_sbc(ra_, read(rhl())); break;
    case SBC_A_imm: ra_ = op_sbc(ra_, next()); break;
    case AND_A_A: ra_ = op_and(ra_, ra_); break;
    case AND_A_B: ra_ = op_and(ra_, rb_); break;
    case AND_A_C: ra_ = op_and(ra_, rc_); break;
    case AND_A_D: ra_ = op_and(ra_, rd_); break;
    case AND_A_E: ra_ = op_and(ra_, re_); break;
    case AND_A_F: ra_ = op_and(ra_, rf_); break;
    case AND_A_L: ra_ = op_and(ra_, rl_); break;
    case AND_A_ind_HL: ra_ = op_and(ra_, read(rhl())); break;
    case AND_A_imm: ra_ = op_and(ra_, next()); break;
    case XOR_A_A: ra_ = op_xor(ra_, ra_); break;
    case XOR_A_B: ra_ = op_xor(ra_, rb_); break;
    case XOR_A_C: ra_ = op_xor(ra_, rc_); break;
    case XOR_A_D: ra_ = op_xor(ra_, rd_); break;
    case XOR_A_E: ra_ = op_xor(ra_, re_); break;
    case XOR_A_F: ra_ = op_xor(ra_, rf_); break;
    case XOR_A_L: ra_ = op_xor(ra_, rl_); break;
    case XOR_A_ind_HL: ra_ = op_xor(ra_, read(rhl())); break;
    case XOR_A_imm: ra_ = op_xor(ra_, next()); break;
    case OR_A_A: ra_ = op_or(ra_, ra_); break;
    case OR_A_B: ra_ = op_or(ra_, rb_); break;
    case OR_A_C: ra_ = op_or(ra_, rc_); break;
    case OR_A_D: ra_ = op_or(ra_, rd_); break;
    case OR_A_E: ra_ = op_or(ra_, re_); break;
    case OR_A_F: ra_ = op_or(ra_, rf_); break;
    case OR_A_L: ra_ = op_or(ra_, rl_); break;
    case OR_A_ind_HL: ra_ = op_or(ra_, read(rhl())); break;
    case OR_A_imm: ra_ = op_or(ra_, next()); break;
    case CP_A: op_cp(ra_); break;
    case CP_B: op_cp(rb_); break;
    case CP_C: op_cp(rc_); break;
    case CP_D: op_cp(rd_); break;
    case CP_E: op_cp(re_); break;
    case CP_F: op_cp(rf_); break;
    case CP_L: op_cp(rl_); break;
    case CP_ind_HL: op_cp(read(rhl())); break;
    case CP_imm: op_cp(next()); break;
    case INC_A: ra_ = op_inc(ra_); break;
    case INC_B: rb_ = op_inc(rb_); break;
    case INC_C: rc_ = op_inc(rc_); break;
    case INC_D: rd_ = op_inc(rd_); break;
    case INC_E: re_ = op_inc(re_); break;
    case INC_F: rf_ = op_inc(rf_); break;
    case INC_L: rl_ = op_inc(rl_); break;
    case INC_ind_HL: tmp = read(rhl()) + next(); write(tmp, op_inc(read(tmp))); break;
    case DEC_A: ra_ = op_dec(ra_); break;
    case DEC_B: rb_ = op_dec(rb_); break;
    case DEC_C: rc_ = op_dec(rc_); break;
    case DEC_D: rd_ = op_dec(rd_); break;
    case DEC_E: re_ = op_dec(re_); break;
    case DEC_F: rf_ = op_dec(rf_); break;
    case DEC_L: rl_ = op_dec(rl_); break;
    case DEC_ind_HL: tmp = read(rhl()) + next(); write(tmp, op_dec(read(tmp))); break;
    case JP: rpc_ = next16(); break;
    case JP_C: tmp16 = next16(); if (fc()) rpc_ = tmp16; break;
    case JP_NC: tmp16 = next16(); if (!fc()) rpc_ = tmp16; break;
    case JP_Z: tmp16 = next16(); if (fz()) rpc_ = tmp16; break;
    case JP_NZ: tmp16 = next16(); if (!fz()) rpc_ = tmp16; break;
    case JP_PO: tmp16 = next16(); if (!fpv()) rpc_ = tmp16; break;
    case JP_PE: tmp16 = next16(); if (fpv()) rpc_ = tmp16; break;
    case JP_M: tmp16 = next16(); if (fs()) rpc_ = tmp16; break;
    case JP_P: tmp16 = next16(); if (!fs()) rpc_ = tmp16; break;
    case JP_ind_HL: rpc_ = read(rhl()); break;
    case JR: tmp = next(); rpc_ = *((int8_t*)&tmp); break;
    case JR_C: tmp = next(); if (fc()) rpc_ = *((int8_t*)&tmp); break;
    case JR_NC: tmp = next(); if (!fc()) rpc_ = *((int8_t*)&tmp); break;
    case JR_Z: tmp = next(); if (fz()) rpc_ = *((int8_t*)&tmp); break;
    case JR_NZ: tmp = next(); if (!fz()) rpc_ = *((int8_t*)&tmp); break;
    case DJNZ: tmp = next(); if (--rb_) rpc_ = *((int8_t*)&tmp); break;
    case OUT_nn_A: write_io(next() , ra_); break;
    case IN_A_nn:  ra_ = read_io(next()); break;

    case EXT_DD:
      switch (code = next()) {
        case DD_LD_B_imm: rb_ = next(); break;
        case DD_LD_C_imm: rc_ = next(); break;
        case DD_LD_D_imm: rd_ = next(); break;
        case DD_LD_E_imm: re_ = next(); break;
        case DD_LD_H_imm: rh_ = next(); break;
        case DD_LD_A_idx_IY: ra_ = read(riy_ + next()); break;
        case DD_LD_B_idx_IX: rb_ = read(rix_ + next()); break;
        case DD_LD_C_idx_IX: rc_ = read(rix_ + next()); break;
        case DD_LD_D_idx_IX: rd_ = read(rix_ + next()); break;
        case DD_LD_E_idx_IX: re_ = read(rix_ + next()); break;
        case DD_LD_H_idx_IX: rh_ = read(rix_ + next()); break;
        case DD_LD_L_idx_IX: rl_ = read(rix_ + next()); break;
        case DD_LD_idx_IX_A: write(rix_ + next(), ra_); break;
        case DD_LD_idx_IX_B: write(rix_ + next(), rb_); break;
        case DD_LD_idx_IX_C: write(rix_ + next(), rc_); break;
        case DD_LD_idx_IX_D: write(rix_ + next(), rd_); break;
        case DD_LD_idx_IX_E: write(rix_ + next(), re_); break;
        case DD_LD_idx_IX_F: write(rix_ + next(), rf_); break;
        case DD_LD_idx_IX_L: write(rix_ + next(), rl_); break;
        case DD_LD_idx_IX_imm: write(rix_ + next(), next()); break;
        case DD_LD_ind_HL_imm: write(rhl(), next()); break;
        case DD_ADD_A_idx_IX: ra_ = op_add(ra_, read(rix_ + next())); break;
        case DD_ADC_A_idx_IX: ra_ = op_adc(ra_, read(rix_ + next())); break;
        case DD_SUB_A_idx_IX: ra_ = op_sub(ra_, read(rix_ + next())); break;
        case DD_SBC_A_idx_IX: ra_ = op_sbc(ra_, read(rix_ + next())); break;
        case DD_AND_A_idx_IX: ra_ = op_and(ra_, read(rix_ + next())); break;
        case DD_XOR_A_idx_IX: ra_ = op_xor(ra_, read(rix_ + next())); break;
        case DD_OR_A_idx_IX: ra_ = op_or(ra_, read(rix_ + next())); break;
        case DD_CP_idx_IX: op_cp(read(rix_ + next())); break;
        case DD_JP_ind_IX: rpc_ = read(rix_); break;

        default:
      	  Serial.print(cerr);
          Serial.print("unknown opcode: 0x")
          Serial.print((String)code);
          break;
      }
      break;

    case EXT_ED:
      switch (next()) {
        case ED_LD_imp_I_A: ri_ = ra_; break;
        case ED_LD_imp_R_A: rr_ = ra_; break;

        default:
      	  Serial.print(cerr);
      	  Serial.print("unknown opcode: 0x")
      	  Serial.print((String)code);
          break;
      }
      break;

    case EXT_FD:
      switch (code = next()) {
        case FD_LD_A_imm: ra_ = next(); break;
        case FD_LD_A_ext: ra_ = read(next16()); break;
        case FD_LD_A_idx_IX: ra_ = read(rix_ + next()); break;
        case FD_LD_B_idx_IY: rb_ = read(riy_ + next()); break;
        case FD_LD_C_idx_IY: rc_ = read(riy_ + next()); break;
        case FD_LD_D_idx_IY: rd_ = read(riy_ + next()); break;
        case FD_LD_E_idx_IY: re_ = read(riy_ + next()); break;
        case FD_LD_H_idx_IY: rh_ = read(riy_ + next()); break;
        case FD_LD_idx_IY_A: write(riy_ + next(), ra_); break;
        case FD_LD_idx_IY_B: write(riy_ + next(), rb_); break;
        case FD_LD_idx_IY_C: write(riy_ + next(), rc_); break;
        case FD_LD_idx_IY_D: write(riy_ + next(), rd_); break;
        case FD_LD_idx_IY_E: write(riy_ + next(), re_); break;
        case FD_LD_idx_IY_F: write(riy_ + next(), rf_); break;
        case FD_LD_idx_IY_L: write(riy_ + next(), rl_); break;
        case FD_LD_idx_IY_imm: write(riy_ + next(), next()); break;
        case FD_ADD_A_idx_IY: ra_ = op_add(ra_, read(riy_ + next())); break;
        case FD_ADC_A_idx_IY: ra_ = op_adc(ra_, read(riy_ + next())); break;
        case FD_SUB_A_idx_IY: ra_ = op_sub(ra_, read(riy_ + next())); break;
        case FD_SBC_A_idx_IY: ra_ = op_sbc(ra_, read(riy_ + next())); break;
        case FD_AND_A_idx_IY: ra_ = op_and(ra_, read(riy_ + next())); break;
        case FD_XOR_A_idx_IY: ra_ = op_xor(ra_, read(riy_ + next())); break;
        case FD_OR_A_idx_IY: ra_ = op_or(ra_, read(riy_ + next())); break;
        case FD_CP_idx_IY: op_cp(read(riy_ + next())); break;
        case FD_JP_ind_IY: rpc_ = read(riy_); break;

        default:
  	  Serial.print(cerr);
          Serial.print("unknown opcode: 0x")
      	  Serial.print((String)code);
          break;
      }

      break;

    default:
      Serial.print(cerr);
      Serial.print("unknown opcode: 0x")
      Serial.print((String)code);
      break;
  }
}



/*
 *
 *
 *
 *
 *
 *
 *
 *
 */
void ArduZ80::run_to_nop(bool print) {

  Serial.println("\n========= Emulator Log ===========");

  if (print) {

    dump_regs();

  }

  while (read(rpc_)) {

    if (print) {

      Serial.print("> " + pc_str());

    }

    step();

    if (print) {

      dump_regs();
      Serial.print("\n");
 
    }
  }

  if (print) {
    Serial.print("> nop");
  }

}


