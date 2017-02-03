# ArduZ80 

The first Z80 emulation library for Arduino, bringing bad the old Z80

# Introduction 

Studying microprocessors for a semester project, I had to write an emulator, and I chose Z80 to be my study case. my project had to be in arduino, so the emulator itself must run on arduino, I searched the internet and no working project or library where found for Z80 to emulate it on arduino, I decided to write my own library and emulator system and revive the Z80 through Arduino, it was a great processor for hobbyists and students and very good to study computer architeture on it. 

# Zilog Z80 
The Z80 microprocessor is an 8 bit CPU with a 16 bit address bus.
It has a language of 252 root instructions and an additional 308
instructions.<br/>
The Z80 was modeled after the 8080 and contains the 78 opcodes of
8080 opcodes as a subset to it's language.<br/>
Programming features include an accumulator and six eight bit
registers that can be paired as Three 16 bit registers.<br/>
In addition to the general registers, a stack-pointer, program-counter, and two
index (memory pointers) registers are provided.<br/>

# Features 

- Written and optimized for Arduino.<br/>
- Tested on Arduino Nano, Uno, Mega.<br/>
- AlU, Buses, Registers, Control Unit emulated.<br/>
- Emulates 260 Instructions (177 Basic Instructions, 83 Extended Instructions).<br/>
- Implementation of IN and OUT instruction left for developer to customize his system.<br/>
- built with customization and extensibility in mind, adding a new instruction takes 3 lines only.<br/>

# Usage 

Step 1: 

    //Make an array to hold the program
    uint8_t t[30] = {
    
    EXT_FD, FD_LD_A_imm, 0x00,
    EXT_DD, DD_LD_B_imm, 0x09,
    EXT_DD, DD_LD_C_imm, 0x03,
    XOR_A_B, 0xFF,
    XOR_A_C, 0xFF,
    XOR_A_imm, 0xFF,
    NOP
    
    };
    
Step 2 : 

    //Copy the program to RAM 
    for (int i = 0; i < 30; i++) {

        cpu.ram_[i] = t[i];
   
    }

Step 3 : 

    //Run the CPU 
    cpu.run_to_nop(true);

Step 4 (Optional) : 

    //Implement write_io and read_io 
    
    void ArduZ80::write_io(uint16_t addr, uint8_t val){ }

    uint8_t ArduZ80::read_io(uint16_t addr){ return data; }
    
    
# Credits
- Sijmen Smulder for his C++ emulator, helped as a base for my Arduino version.<br/>
- Gabriel Gambetta for his C library, helped to understand some instructions and tweak emulator.<br/>

# License 

This library is signed under MIT License, Reproduce under it's terms. 
