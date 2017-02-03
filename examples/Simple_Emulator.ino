/*
 * ArduZ80 - Simple Emulator Example
 *
 * This sketch runs a program that multiply 2 numbers togther
 * and XORs the result with 255
 *  
 * Also implements the write_io & read_io functions
 *
 */

#include "ArduZ80.h"


/*
 * This function runs whenever OUT instruction is executed
 * Emulates the data and address buses
 * Can be used to output data to pins as real Z80 or to LCD, Serial, TV..etc 
 *
 */
void ArduZ80::write_io(uint16_t addr, uint8_t val){

    Serial.print("Address = ");
    Serial.println(addr);
    Serial.print("Value = ");
    Serial.println(val);
  
}

/*
 * This function runs whenever IN instruction is executed
 * Emulates the data and address buses
 * Can be used to output data to pins as real Z80 or to LCD, Serial, TV..etc 
 *
 */
uint8_t ArduZ80::read_io(uint16_t addr){

    int data = 0;

    if (Serial.available() > 0) {
 
	int data = Serial.read();
	Serial.print("I received: ");
        Serial.println(data);

    }

    return data;
}



void setup() {

  Serial.begin(9600);

}


void loop() {

  ArduZ80 cpu;
  
  /*
   * Simple Z80 Program
   * Loads 0x00 to accumlator
   * Loads 0x05 to Register B
   * Loads 0x03 to Register C
   * Performs repeated addition by ADD and DJNZ Instructions
   * XORs the result with 0xFF
   * 
   */
  uint8_t t[30] = {

    EXT_FD, FD_LD_A_imm, 0x00,
    EXT_DD, DD_LD_B_imm, 0x05,
    EXT_DD, DD_LD_C_imm, 0x03,
    ADD_A_C,
    DJNZ, 0x09,

    XOR_A_imm, 0xFF,

    NOP
  };



  //Copies data from ROM to RAM
  for (int i = 0; i < 30; i++) {

    cpu.ram_[i] = t[i];


  }
  
  //Runs the CPU
  cpu.run_to_nop(true);

}
