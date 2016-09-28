/*
Author: John San Diego
COS 331 operating system
Project 1 - PBrain12 Interpreter
Version 1.00 - 09/26/2016

Brief: Interprets all PBrain12 functions


*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

//Helper functions
int ParseOp1 (char *IR);
int ParseOp2 (char *IR);
int ParseOP1andOP2Imm(char *IR);
int ParseOp1Reg (char *IR);
int ParseOp2Reg (char *IR);
int FetchData(int Memory_Location);
void PrintIR(char *IR);
void printMEM(int upto);
void setMEM(int index, int number);


//operational codes
void OP0(char *IR);
void OP1(char *IR);
void OP2(char *IR);
void OP3(char *IR);
void OP4(char *IR);
void OP5(char *IR);
void OP6(char *IR);
void OP7(char *IR);
void OP8(char *IR);
void OP9(char *IR);
void OP10(char *IR);
void OP11(char *IR);
void OP12(char *IR);
void OP13(char *IR);
void OP14(char *IR);
void OP15(char *IR);
void OP16(char *IR);
void OP17(char *IR);
void OP18(char *IR);
void OP19(char *IR);
void OP20(char *IR);
void OP21(char *IR);
void OP22(char *IR);
void OP23(char *IR);
void OP24(char *IR, char *PSW);
void OP25(char *IR, char *PSW);
void OP26(char *IR, char *PSW);
void OP27(char *IR, char *PSW);
void OP28(char *IR, char *PSW);
void OP29(char *IR, char *PSW);
void OP30(char *IR, char *PSW);
void OP31(char *IR, char *PSW);
void OP32(char *IR, char *PSW);
void OP33(char *IR, char *PSW, short int *PC);
void OP34(char *IR, char *PSW, short int *PC);
void OP35(char *IR, short int *PC);
void OP99();
/*These variables are associated with the implementation of the VM*/
int fp ;
int i ;
int j, k ;
char input_line [7] ;

/*These are variables representing the VM itself*/

char IR[6] ;
short int PC = 0 ;

short int P0 ; //these are the pointer registers
short int P1 ;
short int P2 ;
short int P3 ;

int R0 ; //GP regs
int R1 ;
int R2 ;
int R3 ;

int ACC ;
char PSW[2] ;
char memory [100][6]  ; //this is the program memory for first program
short int opcode ;            //nice to know what we are doing
int program_line = 0 ;

int main(int argc, char *argv[])
{

 //Step 1 Read file into VM memory. Assume the file name is program2.

   fp = open("program2", O_RDONLY) ; //always check the return value.
   printf("Open is %d\n", fp) ;

 if (fp < 0) //error in read
        {printf("Could not open file\n");
         exit(0) ;
        }


 //read in the first line of the program

 int ret = read (fp, input_line, 7 ) ; //returns number of characters read`

  while (1)
        {
         if (ret <= 0) //indicates end of file or error
                break ; //breaks out of infinite loop

	//copy from input line into program memory

	printf("Copying Program line %d into memory\n", program_line) ;
        for (i = 0; i < 6 ; i++)
		{
                memory[program_line][i] = input_line[i] ;
		printf("%c ", memory[program_line][i]) ;
		}
	   printf("\n") ;

        //read in next line of code

    ret = read (fp, input_line, 7 ) ;

	//if the firat character is a 'Z' then you are reading data.
	//No more program code so break out of loop


	if(input_line[0] == 'Z')
		break ;

        program_line++ ; //now at a new line in the prog
     }

     printf("PROGRAM COPIED INTO VM MEMORY!!!\n") ;

	int Done = 0 ;
	PC = 0;
	while (!Done)
		{for (i = 0; i < 6 ; i++)
			IR[i] = memory[PC][i] ;

		 opcode = ((int) (IR[0])- 48) * 10 ;
		 opcode += ((int) (IR[1])- 48) ;
	   printf("\n In Program Execution Loop: New PC is %d OPCODE IS %d\n\n", PC, opcode) ;

		/* You need to put in the case statements for the remaining opcodes */
		switch(opcode) {
		case 0: OP0(IR) ; PC++; break ;
		case 1: OP1(IR) ; PC++; break ;
    case 2: OP2(IR) ; PC++; break ;
		case 3: OP3(IR) ; PC++ ; break ;
		case 4: OP4(IR) ; PC++ ; break ;
    case 5: OP5(IR) ; PC++; break ;
		case 6: OP6(IR) ; PC++ ; break ;
    case 7: OP7(IR) ; PC++; break ;
    case 8: OP8(IR) ; PC++; break ;
    case 9: OP9(IR) ; PC++; break ;
    case 10: OP10(IR) ; PC++; break ;
    case 11: OP11(IR) ; PC++; break ;
    case 12: OP12(IR) ; PC++; break ;
    case 13: OP13(IR) ; PC++; break ;
		case 14: OP14(IR) ; PC++; break ;
		case 15: OP15(IR) ; PC++; break ;
		case 16: OP16(IR) ; PC++; break ;
    case 17: OP17(IR) ; PC++; break ;
    case 18: OP18(IR) ; PC++; break ;
    case 19: OP19(IR) ; PC++; break ;
		case 20: OP20(IR) ; PC++; break ;
    case 21: OP21(IR) ; PC++; break ;
    case 22: OP22(IR) ; PC++; break ;
    case 23: OP23(IR) ; PC++; break ;
    case 24: OP24(IR, PSW) ; PC++; break ;
    case 25: OP25(IR, PSW) ; PC++; break ;
		case 26: OP26(IR, PSW) ; PC++ ; break;
    case 27: OP27(IR, PSW) ; PC++; break ;
    case 28: OP28(IR, PSW) ; PC++; break ;
		case 29: OP29(IR, PSW) ; PC++ ; break ;
    case 30: OP30(IR, PSW) ; PC++; break ;
    case 31: OP31(IR, PSW) ; PC++; break ;
    case 32: OP32(IR, PSW) ; PC++; break ;
		case 33: OP33(IR, PSW, &PC) ; break ;
		case 34: OP34(IR, PSW, &PC) ; break ;
    case 35: OP35(IR, &PC) ; break ;
		case 99: printf("ALL DONE\n") ; Done = 1 ; break;
		default: printf("Instruction %d not found!!~\n", opcode);
			 exit(0) ;
		}
	      }
}

	//This function returns the integer value of operand 1
	//when this operand is an immediate two-byte integer.

	int ParseOp1 (char *IR)
	    {
        int operand;
        operand = ((int) (IR[2])- 48) * 10 ;
   		  operand += ((int) (IR[3])- 48) ;
        return operand;

      }



	// returns the integer value of operand 2 when this operand is a two-byte integer.
	int ParseOp2 (char *IR)
	    {
        int operand2;
        operand2 = ((int) (IR[4])- 48) * 10 ;
        operand2 += ((int) (IR[5])- 48) ;
        return operand2;
      }

	//returns the integer value of operands 1 and 2 combined to form a 4-byte integer.
	int ParseOP1andOP2Imm(char *IR)
	    {
        int ParseOP1andOP2;
        ParseOP1andOP2 = ((int) (IR[2])- 48) *1000 ;
        ParseOP1andOP2 += ((int) (IR[3])- 48)*100;
        ParseOP1andOP2 += ((int) (IR[4])- 48) *10 ;
        ParseOP1andOP2 += ((int) (IR[5])- 48)*1 ;
        return ParseOP1andOP2;


      }

	// returns the register number of the register used as operand  1 of an instruction.
	// Can be either Pointer or General-Purpose register.
	int ParseOp1Reg (char *IR)
	    {
          int PREG = IR[3]-48;
          return PREG;


      }


	// returns the register number of a register used as operand  2 of an instruction.
	// Can be either a Pointer or General-Purpose register.
	int ParseOp2Reg (char *IR)
	    {


        int PREG = IR[5]-48;
        return PREG;

      }

	// returns the data stored at memory location Memory_Location
	int FetchData(int Memory_Location)
	    {
        int i , MEM;
        for(i=0;i<6;i++){
          MEM += (memory[Memory_Location][i])-48;
        }
          return MEM;
      }
	//Prints out the contents of the IR on the same line.
	void PrintIR(char *IR)
	    {
          printf("%s\n", IR);


      }

	//prints out the contents of memory from row 0 to row upto.
	//This should print out all instructions and data stored in memory.
	void printMEM(int upto)
	   {
       int i,j;
        for(i= 0; i<upto; i++)
        {
          for(j =0; j<6;j++){
          printf("%c", memory[i][j] );
            }
            printf("\n" );

        }

     }

     void setMEM(int index, int number)
         {
             int i, currentDigit = 0;

             for(i = 0; i<6; i++){
             currentDigit = number%10;
             number/=10;
             memory[index][5-i] = currentDigit+48;
           }
         }

//Now its time for the instruction execution functions.
// Here is the first.
void OP0(char *IR){
    int PREG, VAL ;
	  printf("Opcode = 00. Load Pointer Immediate\n") ;
   	  PrintIR(IR) ;

  	 PREG = ParseOp1Reg(IR) ;
  	 VAL = 	ParseOp2 (IR) ;

	    switch(PREG)
		    {
          case 0: P0 = VAL ;
  		    case 1: P1 = VAL ;
		      case 2: P2 = VAL ;
		      case 3: P3 = VAL ;
		    }

        printf("ACC = %i\n", ACC);
        printf("P0 = %i\n", P0);
        printf("P1 = %i\n", P1);
        printf("P2 = %i\n", P2);
        printf("P3 = %i\n", P3);

	  //Will print out junk until the two helper functions are implemented!
	  //printf("Loaded P[%d] with immediate value %d\n", PREG, VAL ) ;
}
void OP1(char *IR)
 {
   //pn <- pn - xx,x:{0..9}
   int PREG, VAL ;
   printf("Opcode = 01. Add to Pointer Immediate\n") ;
       PrintIR(IR) ;

    PREG = ParseOp1Reg(IR) ;
    VAL = 	ParseOp2 (IR) ;

 switch(PREG)
   { case 0: P0 = P0 + VAL ;
     case 1: P1 = P1 + VAL ;
     case 2: P2 = P2 + VAL ;
     case 3: P3 = P3 + VAL ;
   }
   printf("ACC = %i\n", ACC);

 }
 //done - need revision and test
void OP2(char *IR)
 { int PREG, VAL ;
   printf("Opcode = 02. Subtract Pointer Immediate\n") ;
       PrintIR(IR) ;

    PREG = ParseOp1Reg(IR) ;
    VAL = 	ParseOp2 (IR) ;

 switch(PREG)
   { case 0: P0 = P0 - VAL ;
     case 1: P1 = P1 - VAL ;
     case 2: P2 = P2 - VAL ;
     case 3: P3 = P3 - VAL ;
   }
   printf("ACC = %i\n", ACC);

 }
 //done - need revision and test
void OP3(char *IR)
 { int  VAL ; // value of operand 1 and 2 combined
   printf("Opcode = 03. Load Accumulator Immediate\n") ;
       PrintIR(IR) ;


    VAL = ParseOP1andOP2Imm(IR) ;
    ACC = VAL;
    printf("ACC = %i\n", ACC);

 }
void OP4(char *IR){
    int PREG, VAL, ADDR ;
      printf("Opcode = 04. Load Accululator Register Addressing\n") ;
        PrintIR(IR) ;

       PREG = ParseOp1Reg(IR) ; // PREG = pointer register

    switch(PREG)
      {
        case 0: ADDR = P0;
        case 1: ADDR = P1;
        case 2: ADDR = P2;
        case 3: ADDR = P3;
      }
      VAL = (memory[ADDR][2]-48)*1000;
      VAL += (memory[ADDR][3]-48)*100;
      VAL += (memory[ADDR][4]-48)*10;
      VAL += (memory[ADDR][5]-48)*1;
      printf("P0 = %i\n", P0);
      printf("P1 = %i\n", P1);
      printf("P2 = %i\n", P2);
      printf("P3 = %i\n", P3);
      ACC = VAL;
      printf("ACC = %i\n", VAL);

  }
  //done - need revision and test
void OP5(char *IR){
    int PREG, VAL;
      printf("Opcode = 05. Load Accululator Direct Addressing\n") ;
        PrintIR(IR) ;

       PREG = ParseOp1(IR) ; // PREG = pointer register

       VAL = (memory[PREG][2]-48)*1000;
       VAL += (memory[PREG][3]-48)*100;
       VAL += (memory[PREG][4]-48)*10;
       VAL += (memory[PREG][5]-48)*1;
       ACC = VAL;
       printf("ACC = %i\n", ACC);

  }
void OP6(char *IR){
    int PREG, ADDR;
    //chargcc  AC[4];
      printf("Opcode = 06. Store Accumulator Register Addressing\n") ;
        PrintIR(IR);

        PREG = ParseOp1Reg(IR) ; // PREG = pointer register
        switch(PREG)
          {
            case 0: ADDR = P0;
            case 1: ADDR = P1;
            case 2: ADDR = P2;
            case 3: ADDR = P3;
          }
          setMEM(ADDR, ACC);
          printMEM(ADDR);
          printf("ACC = %i\n", ACC);

  }
void OP7(char *IR){
    int  ADDR;
    char AC[4];
      printf("Opcode = 07. Store Accumulator Direct Addressing\n") ;
        PrintIR(IR) ;
        ADDR = ParseOp1(IR);

        AC[0] = (char)((ACC%10000)/1000);
        AC[1] = (char)((ACC%1000)/100);
        AC[2] = (char)((ACC%100)/10);
        AC[3] = (char)((ACC%10)/1);

        memory[ADDR][2] = AC[0];
        memory[ADDR][3] = AC[1];
        memory[ADDR][4] = AC[2];
        memory[ADDR][5] = AC[3];
        printf("ACC = %i\n", ACC);



  }
void OP8(char *IR){
  int PREG, ADDR, VAL_R, VAL_P;
  char AC[4];
  printf("Opcode = 08. Store Register to memory: Register Addressing\n") ;
  PrintIR(IR) ;
  PREG = ParseOp1Reg(IR);
  ADDR = ParseOp2Reg(IR);

  switch (PREG) {
    case 0: VAL_R = R0;
    case 1: VAL_R = R1;
    case 2: VAL_R = R2;
    case 3: VAL_R = R3;
  }

  switch (ADDR) {
    case 0: VAL_P = P0;
    case 1: VAL_P = P1;
    case 2: VAL_P = P2;
    case 3: VAL_P = P3;
  }
  AC[0] = (char)((VAL_R%10000)/1000);
  AC[1] = (char)((VAL_R%1000)/100);
  AC[2] = (char)((VAL_R%100)/10);
  AC[3] = (char)((VAL_R%10)/1);

  memory[VAL_P][2] = AC[0];
  memory[VAL_P][3] = AC[1];
  memory[VAL_P][4] = AC[2];
  memory[VAL_P][5] = AC[3];
  printf("ACC = %i\n", ACC);


}
void OP9(char* IR){
  printf("Opcode = 09. Store Register to memory: Direct Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR, VAL_R;
    char AC[4];
    PREG = ParseOp1Reg(IR);
    ADDR = ParseOp2(IR);

    switch (PREG) {
      case 0: VAL_R = R0;
      case 1: VAL_R = R1;
      case 2: VAL_R = R2;
      case 3: VAL_R = R3;
      }

      AC[0] = (char)((VAL_R%10000)/1000)+48;
      AC[1] = (char)((VAL_R%1000)/100)+48;
      AC[2] = (char)((VAL_R%100)/10)+48;
      AC[3] = (char)((VAL_R%10)/1)+48;

      memory[ADDR][2] = AC[0];
      memory[ADDR][3] = AC[1];
      memory[ADDR][4] = AC[2];
      memory[ADDR][5] = AC[3];

      printf("ACC = %i\n", ACC);

}
void OP10(char *IR){
  printf("Opcode = 10. Load Register from memory: Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR, VAL, VAL2;
    PREG = ParseOp1Reg(IR);
    ADDR = ParseOp2Reg(IR);

    switch (ADDR) {
      case 0: VAL2 = P0;
      case 1: VAL2 = P1;
      case 2: VAL2 = P2;
      case 3: VAL2 = P3;

    }
    VAL = (memory[VAL2][2]-48)*1000;
    VAL += (memory[VAL2][3]-48)*100;
    VAL += (memory[VAL2][4]-48)*10;
    VAL += (memory[VAL2][5]-48)*1;

    switch (PREG) {
      case 0: R0 = VAL;
      case 1: R1 = VAL;
      case 2: R2 = VAL;
      case 3: R3 = VAL;
    }
    printf("ACC = %i\n", ACC);

}
void OP11(char *IR){
  printf("Opcode = 11. Load register from memory: Direct Addressing\n") ;
    PrintIR(IR) ;
    int PREG, VAL, ADDR;
    PREG = ParseOp1Reg(IR);
    ADDR = ParseOp2(IR);

    VAL = (memory[ADDR][2]-48)*1000;
    VAL += (memory[ADDR][3]-48)*100;
    VAL += (memory[ADDR][4]-48)*10;
    VAL += (memory[ADDR][5]-48)*1;

    switch (PREG) {
      case 0: R0 = VAL;
      case 1: R1 = VAL;
      case 2: R2 = VAL;
      case 3: R3 = VAL;
    }
    printf("ACC = %i\n", ACC);

}
void OP12(char *IR){
  printf("Opcode = 12. Loa d Register R0 Immediate\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOP1andOP2Imm(IR);
    R0 = PREG;
    printf("ACC = %i\n", ACC);

}
void OP13(char *IR){
  printf("Opcode = 13. Register to Register Transfer\n") ;
    PrintIR(IR) ;
    int REG1,REG2;
    REG1 = ParseOp1Reg(IR);
    REG2 = ParseOp2Reg(IR);

    switch (REG1) {
      case 0: R0 = REG2;
      case 1: R1 = REG2;
      case 2: R2 = REG2;
      case 3: R3 = REG2;
    }
    printf("ACC = %i\n", ACC);

}

void OP14(char *IR){
  printf("Opcode = 14. Load Accumulator from Register\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1Reg(IR);
    switch (PREG) {
      case 0: ACC = R0;
      case 1: ACC = R1;
      case 2: ACC = R2;
      case 3: ACC = R3;
    }
    printf("ACC = %i\n", ACC);


}
void OP15(char *IR){
  printf("Opcode = 15. Load Register from Accumulator\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1Reg(IR);


    switch (PREG) {
      case 0: R0 = ACC;
      case 1: R1 = ACC;
      case 2: R2 = ACC;
      case 3: R3 = ACC;
    }
    printf("ACC = %i\n", ACC);


}
void OP16(char *IR){
  printf("Opcode = 16. Add Accumulator Immediate\n") ;
    PrintIR(IR) ;
    int PREG,VAL;
    PREG = ParseOP1andOP2Imm(IR);
    VAL = ACC + (int)PREG;
    ACC = VAL;
    printf("ACC = %i\n", ACC);

}
//int PREG - stores op1,op2 = xxxx
void OP17(char *IR){
  printf("Opcode = 17. Subtract Accumulator Immediate\n") ;
    PrintIR(IR) ;
  int PREG,VAL;
  PREG = ParseOP1andOP2Imm(IR);
  VAL = ACC - PREG;
  ACC = VAL;
  printf("ACC = %i\n", ACC);

}
void OP18(char *IR){
  printf("Opcode = 18. Add contents of Register to Accumulator\n") ;
    PrintIR(IR) ;
  int PREG,VAL;
  PREG = ParseOp1Reg(IR);

  switch (PREG) {
    case 0: VAL = ACC + R0;
    case 1: VAL = ACC + R1;
    case 2: VAL = ACC + R2;
    case 3: VAL = ACC + R3;
  }

  ACC = VAL;
  printf("ACC = %i\n", ACC);

}
void OP19(char *IR){
  printf("Opcode = 19. Subtract contents of Register to Accumulator\n") ;
    PrintIR(IR) ;
  int PREG,VAL;
  PREG = ParseOp1Reg(IR);

  switch (PREG) {
    case 0: VAL = ACC - R0;
    case 1: VAL = ACC - R1;
    case 2: VAL = ACC - R2;
    case 3: VAL = ACC - R3;
  }
  ACC = VAL;
  printf("ACC = %i\n", ACC);

}
void OP20(char *IR){
  printf("Opcode = 20. Add Accumulator Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG,VAL, VAL_P;
    PREG = ParseOp1Reg(IR);
    switch (PREG) {
      case 0: VAL_P = P0;
      case 1: VAL_P = P1;
      case 2: VAL_P = P2;
      case 3: VAL_P = P3;

    }

    VAL = ACC + (memory[VAL_P][2]-48)*1000;
    VAL += ACC + (memory[VAL_P][3]-48)*100;
    VAL += ACC + (memory[VAL_P][4]-48)*10;
    VAL += ACC + (memory[VAL_P][5]-48)*1;

    ACC = VAL;
    printf("ACC = %i\n", ACC);


}
void OP21(char *IR){
  printf("Opcode = 21. Add Accumulator Direct Addressing\n") ;
    PrintIR(IR) ;
    int PREG, VAl;

    PREG = ParseOp1(IR);

    VAl = ACC + (memory[PREG][2]-48)*1000;
    VAl += ACC + (memory[PREG][3]-48)*100;
    VAl += ACC + (memory[PREG][4]-48)*10;
    VAl += ACC + (memory[PREG][5]-48)*1;

    ACC = VAl;
    printf("ACC = %i\n", ACC);

}
void OP22(char *IR){
  printf("Opcode = 22. Subtract from Accumulator Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, VAl, VAL_P;

    PREG = ParseOp1Reg(IR);
    switch (PREG) {
      case 0: VAL_P = P0;
      case 1: VAL_P = P1;
      case 2: VAL_P = P2;
      case 3: VAL_P = P3;

    }

    VAl = ACC - (memory[VAL_P][2]-48)*1000;
    VAl += ACC - (memory[VAL_P][3]-48)*100;
    VAl += ACC - (memory[VAL_P][4]-48)*10;
    VAl += ACC - (memory[VAL_P][5]-48)*1;

    ACC = VAl;
    printf("ACC = %i\n", ACC);


}
void OP23(char *IR){
  printf("Opcode = 23. Subtract from Accumulator Direct Addressing\n") ;
    PrintIR(IR) ;

    int PREG, VAl;

    PREG = ParseOp1(IR);

    VAl = ACC - (memory[PREG][2]-48)*1000;
    VAl += ACC - (memory[PREG][3]-48)*100;
    VAl += ACC - (memory[PREG][4]-48)*10;
    VAl += ACC - (memory[PREG][5]-48)*1;

    ACC = VAl;
    printf("ACC = %i\n", ACC);


}
void OP24(char *IR, char *PSW){
  printf("Opcode = 24. Compare Equal Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR;
    PREG = ParseOp1Reg(IR);

    switch (PREG) {
      case 0: ADDR = P0;
      case 1: ADDR = P1;
      case 2: ADDR = P2;
      case 3: ADDR = P3;
    }
    if(ACC == ADDR)
      PSW[0] = 'T';
    else
      PSW[0]= 'F';

      printf("ACC = %i\n", ACC);


}
void OP25(char *IR, char *PSW){
  printf("Opcode = 25. Compare Less Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR;

    PREG = ParseOp1Reg(IR);

    switch (PREG) {
      case 0: ADDR = P0;
      case 1: ADDR = P1;
      case 2: ADDR = P2;
      case 3: ADDR = P3;
    }

    if(ACC < ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);

}

void OP26(char *IR, char *PSW){
  printf("Opcode = 26. Compare Greater Register Addressing\n") ;
    PrintIR(IR);
    int PREG, ADDR;

    PREG = ParseOp1Reg(IR);

    switch (PREG) {
      case 0: ADDR = P0;
      case 1: ADDR = P1;
      case 2: ADDR = P2;
      case 3: ADDR = P3;
    }

    if(ACC > ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);


}
void OP27(char *IR, char *PSW){
  printf("Opcode = 27. Compare Greater Immediate\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOP1andOP2Imm(IR);

    if(ACC > PREG)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);

}
void OP28(char *IR, char *PSW){
  printf("Opcode = 28. Compare Equal Immediate\n") ;
  PrintIR(IR);
  int PREG;
  PREG = ParseOP1andOP2Imm(IR);

  if(ACC == PREG)
    PSW[0] = 'T';
  else
    PSW[0] = 'F';

    printf("ACC = %i\n", ACC);



}
void OP29(char *IR, char *PSW){
  printf("Opcode = 29. Compare Less Immediate\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOP1andOP2Imm(IR);

    if(ACC < PREG)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);


}
void OP30(char *IR, char *PSW){
  printf("Opcode = 30. Compare Register Equal\n") ;
    PrintIR(IR) ;
    int REG, ADDR;
    REG = ParseOp1Reg(IR);
    switch (REG) {
      case 0: ADDR = R0;
      case 1: ADDR = R1;
      case 2: ADDR = R2;
      case 3: ADDR = R3;
     }
    if(ACC == ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);


}
void OP31(char *IR, char *PSW){
  printf("Opcode = 31. Compare Register Less\n") ;
    PrintIR(IR) ;
    int REG, ADDR;
    REG = ParseOp1Reg(IR);
    switch (REG) {
      case 0: ADDR = R0;
      case 1: ADDR = R1;
      case 2: ADDR = R2;
      case 3: ADDR = R3;
     }
    if(ACC < ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);

}
void OP32(char *IR, char *PSW){
  printf("Opcode = 32. Compare Register Greater\n") ;
    PrintIR(IR) ;
    int REG, ADDR;
    REG = ParseOp1Reg(IR);
    switch (REG) {
      case 0: ADDR = R0;
      case 1: ADDR = R1;
      case 2: ADDR = R2;
      case 3: ADDR = R3;
     }
    if(ACC > ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);

}
void OP33(char *IR, char *PSW, short int *PC){
  printf("Opcode = 33. Branch Conditional True\n") ;
    PrintIR(IR) ;
    short int PREG;
    PREG = ParseOp1(IR);

    if(PSW[0] == 'T'){
      *PC = PREG;
    }

    printf("ACC = %i\n", ACC);

}
void OP34(char *IR, char *PSW, short int *PC){
  printf("Opcode = 34. Branch Conditional False\n") ;
    PrintIR(IR) ;
    short int PREG;
    PREG = ParseOp1(IR);

    if(PSW[0] == 'F'){
      *PC = PREG;
    }

    printf("ACC = %i\n", ACC);

}
void OP35(char *IR, short int *PC){
  printf("Opcode = 35. Branch Unconditional\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1(IR);
      *PC = PREG;

      printf("ACC = %i\n", ACC);


}
