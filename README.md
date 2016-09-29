# FunProject1
Author: John San Diego
COS 331 operating system
Project 1 - PBrain12 Interpreter
Version 1.00 - 09/29/2016

To compile: gcc Interpreter.c -o Interpreter.out

Brief: The Interpreter for PBrain12 Operating system. The Interpreter consists of
the following variables
IR = Instruction Register - 6 element character array which hold the instructions
P0-P3 = pointer registers
R0-R3 = program registers
PC = program counter
PSW[2] = program status word - character that can be either T or F
memory = is the character 2d array where process and IR is stored  

There are 9 helper functions which supports all of the operand functions
-ParseOp1 - returns IR[2] and IR[3]
-ParseOp2 - returns IR[4] and IR[5]
-ParseOp1Reg - returns IR[3]
-ParseOp2Reg - returns IR[5]
-ParseOP1andOP2Imm - returns IR[2-5]
-PrintIR - returns Instruction registers
-FetchData - returns whats in a specific memory location
-printMEM - returns all in memory
-setMEM - converts Accumulator to character and store it in index specified in   
memory.  

There are 35 Operand functions start from OP0 - OP35



Bug: Currently, I haven't found any bugs using the Fibonacci, if and else, and the for loop.
