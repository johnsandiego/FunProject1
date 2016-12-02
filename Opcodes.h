#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
void OP36(char *IR);
void OP37(char *IR,int a, int b);

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

//converts and stores Accumulator value into memory
void setMEM(int index, int number)
         {
             int i, currentDigit = 0;

             for(i = 0; i<6; i++){
             currentDigit = number%10;
             number/=10;
             memory[index][5-i] = currentDigit+48;
						 printf("currentDigit: %d\n",memory[index][i] );

           }
         }

//Now its time for the instruction execution functions.
void OP0(char *IR){
    int PREG, VAL ;
	  printf("Opcode = 00. Load Pointer Immediate\n") ;
   	  PrintIR(IR) ;

  	 PREG = ParseOp1Reg(IR) ;
  	 VAL = 	ParseOp2 (IR) ;

	    switch(PREG)
		    {
          case 0: P0 = VAL ;break;
  		    case 1: P1 = VAL ;break;
		      case 2: P2 = VAL ;break;
		      case 3: P3 = VAL ;break;
		    }

        printf("ACC = %i\n", ACC);
        printf("P0 = %i\n", P0);
        printf("P1 = %i\n", P1);
        printf("P2 = %i\n", P2);
        printf("P3 = %i\n", P3);

	  //Will print out junk until the two helper functions are implemented!
	  //printf("Loaded P[%d] with immediate value %d\n", PREG, VAL ) ;
}

//add pn = pn + xx
void OP1(char *IR)
 {
   //pn <- pn - xx,x:{0..9}
   int PREG, VAL ;
   printf("Opcode = 01. Add to Pointer Immediate\n") ;
       PrintIR(IR) ;

    PREG = ParseOp1Reg(IR) ;
    VAL = 	ParseOp2 (IR) ;

 switch(PREG)
   { case 0: P0 = P0 + VAL ;break ;
     case 1: P1 = P1 + VAL ;break ;
     case 2: P2 = P2 + VAL ;break ;
     case 3: P3 = P3 + VAL ;break ;
   }
   printf("P0 = %i\n", P0);
   printf("P1 = %i\n", P1);
   printf("P2 = %i\n", P2);
   printf("P3 = %i\n", P3);
   printf("ACC = %i\n", ACC);

 }
 //Pn = Pn - XX

//Pointer decremented by XX
void OP2(char *IR)
 { int PREG, VAL ;
   printf("Opcode = 02. Subtract Pointer Immediate\n") ;
       PrintIR(IR) ;

    PREG = ParseOp1Reg(IR) ;
    VAL = 	ParseOp2 (IR) ;

 switch(PREG)
   { case 0: P0 = P0 - VAL ;break ;
     case 1: P1 = P1 - VAL ;break ;
     case 2: P2 = P2 - VAL ;break ;
     case 3: P3 = P3 - VAL ;break ;
   }
   printf("P0 = %i\n", P0);
   printf("P1 = %i\n", P1);
   printf("P2 = %i\n", P2);
   printf("P3 = %i\n", P3);
   printf("ACC = %i\n", ACC);

 }
 // store op1 and op2 in Accululator

//Load integer value XXXX into accumulator
void OP3(char *IR)
 { int  VAL ; // value of operand 1 and 2 combined
   printf("Opcode = 03. Load Accumulator Immediate\n") ;
       PrintIR(IR) ;


    VAL = ParseOP1andOP2Imm(IR) ;
    ACC = VAL;
    printf("ACC = %i\n", ACC);

 }
 //stores value in memory location specified into Accululator

//Load accumulator with contents of memory address contained in Pn, n{0..3}
void OP4(char *IR){
    int PREG, VAL, ADDR ;
      printf("Opcode = 04. Load Accululator Register Addressing\n") ;
        PrintIR(IR) ;

       PREG = ParseOp1Reg(IR) ; // PREG = pointer register

    switch(PREG)
      {
        case 0: ADDR = P0;break;
        case 1: ADDR = P1;break;
        case 2: ADDR = P2;break;
        case 3: ADDR = P3;break;
      }
      VAL = (int)(memory[ADDR][2]-48)*1000;
      VAL += (int)(memory[ADDR][3]-48)*100;
      VAL += (int)(memory[ADDR][4]-48)*10;
      VAL += (int)(memory[ADDR][5]-48)*1;

      ACC = VAL;
      printf("ACC = %i\n", ACC);

  }
  //load memory location xx into Accululator

//Load Accumulator with contents of address XX, X{0..9}
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
  //store Pn into the Accululator

//Store contents of Accumulator to the memory location held in Pn
void OP6(char *IR){
    int PREG, ADDR;
    //chargcc  AC[4];
      printf("Opcode = 06. Store Accumulator Register Addressing\n") ;
        PrintIR(IR);

        PREG = ParseOp1Reg(IR) ; // PREG = pointer register
        switch(PREG)
          {
            case 0: ADDR = P0;break;
            case 1: ADDR = P1;break;
            case 2: ADDR = P2;break;
            case 3: ADDR = P3;break;
          }
          setMEM(ADDR, ACC);

          printMEM(ADDR);
          printf("ACC = %i\n", ACC);


  }

//Store	contents	of	Accumulator	to	the	memory	location	held	in	Pn.
void OP7(char *IR){
    int  ADDR;
    char AC[4];
      printf("Opcode = 07. Store Accumulator Direct Addressing\n") ;
        PrintIR(IR) ;
        ADDR = ParseOp1(IR);

        setMEM(ADDR, ACC);
        printf("ACC = %i\n", ACC);



  }

//Store	contents	of	AC	into	memory	location	XX,	X{0..9}.
void OP8(char *IR){
  int PREG, ADDR, VAL_R, VAL_P;
  char AC[4];
  printf("Opcode = 08. Store Register to memory: Register Addressing\n") ;
  PrintIR(IR) ;
  PREG = ParseOp1Reg(IR);
  ADDR = ParseOp2Reg(IR);

  switch (PREG) {
    case 0: VAL_R = R0;break ;
    case 1: VAL_R = R1;break ;
    case 2: VAL_R = R2;break ;
    case 3: VAL_R = R3;break ;
  }

  switch (ADDR) {
    case 0: VAL_P = P0;break ;
    case 1: VAL_P = P1;break ;
    case 2: VAL_P = P2;break ;
    case 3: VAL_P = P3;break ;
  }
  setMEM(VAL_P, VAL_R);

  printf("ACC = %i\n", ACC);


}

//Store	contents	of	register	Rn into	memory
//address	pointed	to	by	Pn,	n{0..3}
void OP9(char* IR){
  printf("Opcode = 09. Store Register to memory: Direct Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR, VAL_R;
    char AC[4];
    PREG = ParseOp1Reg(IR);
    ADDR = ParseOp2(IR);

    switch (PREG) {
      case 0: VAL_R = R0;break ;
      case 1: VAL_R = R1;break ;
      case 2: VAL_R = R2;break ;
      case 3: VAL_R = R3;break ;
      }

      setMEM(ADDR, VAL_R);

      printf("ACC = %i\n", ACC);

}

//Store	contents	of	Register	n,	n{0..3}
//to	Memory	location XX,	X{0..9}.
void OP10(char *IR){
  printf("Opcode = 10. Load Register from memory: Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR, VAL, VAL2;
    PREG = ParseOp1Reg(IR);
    ADDR = ParseOp2Reg(IR);

    switch (ADDR) {
      case 0: VAL2 = P0;break ;
      case 1: VAL2 = P1;break ;
      case 2: VAL2 = P2;break ;
      case 3: VAL2 = P3;break ;

    }
    VAL = (memory[VAL2][2]-48)*1000;
    VAL += (memory[VAL2][3]-48)*100;
    VAL += (memory[VAL2][4]-48)*10;
    VAL += (memory[VAL2][5]-48)*1;

    switch (PREG) {
      case 0: R0 = VAL;break ;
      case 1: R1 = VAL;break ;
      case 2: R2 = VAL;break ;
      case 3: R3 = VAL;break ;
    }
    printf("ACC = %i\n", ACC);

}

//Load	Register	Rn with	the	contents	of	memory	location
//pointed	to	by	Pn,	n{0..3}.
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
      case 0: R0 = VAL;break ;
      case 1: R1 = VAL;break ;
      case 2: R2 = VAL;break ;
      case 3: R3 = VAL;break ;
    }
    printf("ACC = %i\n", ACC);

}

//Load	Register	Rn,	n{0..3},	with	the	contents	of	memory
//location	XX,	X{0..9}.
void OP12(char *IR){
  printf("Opcode = 12. Loa d Register R0 Immediate\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOP1andOP2Imm(IR);
    R0 = PREG;
    printf("ACC = %i\n", ACC);

}

//Load	Register	R0	with	integer	value	XXXX,	X{0..9}
void OP13(char *IR){
  printf("Opcode = 13. Register to Register Transfer\n") ;
    PrintIR(IR) ;
    int REG1,REG2;
    REG1 = ParseOp1Reg(IR);
    REG2 = ParseOp2Reg(IR);

    switch (REG1) {
      case 0: R0 = REG2;break ;
      case 1: R1 = REG2;break ;
      case 2: R2 = REG2;break ;
      case 3: R3 = REG2;break ;
    }
    printf("ACC = %i\n", ACC);

}

//Rn is	assigned	the	contents	of	Rp,
//n,	p	{0..3}
void OP14(char *IR){
  printf("Opcode = 14. Load Accumulator from Register\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1Reg(IR);
    switch (PREG) {
      case 0: ACC = R0;break ;
      case 1: ACC = R1;break ;
      case 2: ACC = R2;break ;
      case 3: ACC = R3;break ;
    }
    printf("ACC = %i\n", ACC);


}

//Accumulator	assigned	the	contents	of	Rn,	n{0..3}
void OP15(char *IR){
  printf("Opcode = 15. Load Register from Accumulator\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1Reg(IR);


    switch (PREG) {
      case 0: R0 = ACC;break ;
      case 1: R1 = ACC;break ;
      case 2: R2 = ACC;break ;
      case 3: R3 = ACC;break ;
    }
    printf("ACC = %i\n", ACC);


}

//Register	Rn,	n{0..3}	assigned	the	contents	of	the accumulator
void OP16(char *IR){
  printf("Opcode = 16. Add Accumulator Immediate\n") ;
    PrintIR(IR) ;
    int PREG,VAL;
    PREG = ParseOP1andOP2Imm(IR);
    VAL = ACC + PREG;
    ACC = VAL;
    printf("ACC = %i\n", ACC);

}

//add XXXX into Accululator
void OP17(char *IR){
  printf("Opcode = 17. Subtract Accumulator Immediate\n") ;
    PrintIR(IR) ;
  int PREG,VAL;
  PREG = ParseOP1andOP2Imm(IR);
  VAL = ACC - PREG;
  ACC = VAL;
  printf("ACC = %i\n", ACC);

}

//Subtract xxxx into Accululator
void OP18(char *IR){
  printf("Opcode = 18. Add contents of Register to Accumulator\n") ;
    PrintIR(IR) ;
  int PREG,VAL;
  PREG = ParseOp1Reg(IR);

  switch (PREG) {
    case 0: VAL = ACC + R0;break ;
    case 1: VAL = ACC + R1;break ;
    case 2: VAL = ACC + R2;break ;
    case 3: VAL = ACC + R3;break ;
  }

  ACC = VAL;
  printf("ACC = %i\n", ACC);

}

//subtract Rn to accumulator
void OP19(char *IR){
  printf("Opcode = 19. Subtract contents of Register to Accumulator\n") ;
    PrintIR(IR) ;
  int PREG,VAL;
  PREG = ParseOp1Reg(IR);

  switch (PREG) {
    case 0: VAL = ACC - R0;break ;
    case 1: VAL = ACC - R1;break ;
    case 2: VAL = ACC - R2;break ;
    case 3: VAL = ACC - R3;break ;
  }
  ACC = VAL;
  printf("ACC = %i\n", ACC);

}

//Add	contents	of	memory	pointed	to	by	Pn,	n{0..3}	to	AC.
void OP20(char *IR){
  printf("Opcode = 20. Add Accumulator Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG,VAL, VAL_P;
    PREG = ParseOp1Reg(IR);
    switch (PREG) {
      case 0: VAL_P = P0;break;
      case 1: VAL_P = P1;break;
      case 2: VAL_P = P2;break;
      case 3: VAL_P = P3;break;

    }
    VAL = ACC +  (memory[VAL_P][2]-48)*1000;
    VAL += ACC + (memory[VAL_P][3]-48)*100;
    VAL += ACC + (memory[VAL_P][4]-48)*10;
    VAL += ACC + (memory[VAL_P][5]-48)*1;
    printf("VAL = %i\n", VAL);



    ACC = VAL;
    printf("ACC = %i\n", ACC);


}

//Add	contents	of	memory	location	XX	to	Accumulator X	{0..9}
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

//Subtract Contents of memory location pointed to by Pn, n{0..3} from Accumulator
void OP22(char *IR){
  printf("Opcode = 22. Subtract from Accumulator Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, VAl, VAL_P;

    PREG = ParseOp1Reg(IR);
    switch (PREG) {
      case 0: VAL_P = P0;break ;
      case 1: VAL_P = P1;break ;
      case 2: VAL_P = P2;break ;
      case 3: VAL_P = P3;break ;

    }

    VAl = ACC - (memory[VAL_P][2]-48)*1000;
    VAl += ACC - (memory[VAL_P][3]-48)*100;
    VAl += ACC - (memory[VAL_P][4]-48)*10;
    VAl += ACC - (memory[VAL_P][5]-48)*1;

    ACC = VAl;
    printf("ACC = %i\n", ACC);


}

//Subtract from accumulator contents of memory location XX.
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

//If contents of  accumulator are equal to contents of memory location pointed to by Pn,
//n{0..3}, then byte 0 of the PSW set to T, else set to F.
void OP24(char *IR, char *PSW){
  printf("Opcode = 24. Compare Equal Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR;
    PREG = ParseOp1Reg(IR);

    switch (PREG) {
      case 0: ADDR = P0;break ;
      case 1: ADDR = P1;break ;
      case 2: ADDR = P2;break ;
      case 3: ADDR = P3;break ;
    }
    if(ACC == ADDR)
      PSW[0] = 'T';
    else
      PSW[0]= 'F';

      printf("ACC = %i\n", ACC);


}

//If contents of Accumulator are less than the contents of memory location pointed to by Pn,
//n{0..3}, then byte 0 of the PSW set to T, else set to F.
void OP25(char *IR, char *PSW){
  printf("Opcode = 25. Compare Less Register Addressing\n") ;
    PrintIR(IR) ;
    int PREG, ADDR;

    PREG = ParseOp1Reg(IR);

    switch (PREG) {
      case 0: ADDR = P0;break ;
      case 1: ADDR = P1;break ;
      case 2: ADDR = P2;break ;
      case 3: ADDR = P3;break ;
    }

    if(ACC < ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);

}

//If contents of  accumulator are greater than contents of memory location pointed to by Pn,
//n{0..3}, then byte 0 of the PSW set to T, else set to F.
void OP26(char *IR, char *PSW){
  printf("Opcode = 26. Compare Greater Register Addressing\n") ;
    PrintIR(IR);
    int PREG, ADDR;

    PREG = ParseOp1Reg(IR);

    switch (PREG) {
      case 0: ADDR = P0;break ;
      case 1: ADDR = P1;break ;
      case 2: ADDR = P2;break ;
      case 3: ADDR = P3;break ;
    }

    if(ACC > ADDR){
      PSW[0] = 'T';}
    else{
      PSW[0] = 'F';}

      printf("ACC = %i\n", ACC);
      printf("PSW = %c\n", PSW[0]);



}

//If contents of Accumulator are greater than the value XXXX, then byte 0 of the PSW set to T,
//else set to F
void OP27(char *IR, char *PSW){
  printf("Opcode = 27. Compare Greater Immediate\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOP1andOP2Imm(IR);

    if(ACC > PREG){
      PSW[0] = 'T';}
    else{
      PSW[0] = 'F';
      }
      printf("PREG = %i\n", PREG);
      printf("ACC = %i\n", ACC);

}

//Compare contents of accumulator to integer
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

//Compare contents of accumulator to integer.
void OP29(char *IR, char *PSW){
  printf("Opcode = 29. Compare Less Immediate\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOP1andOP2Imm(IR);

    if(ACC < PREG){
      PSW[0] = 'T';
    }
    else{
      PSW[0] = 'F';
    }
      printf("PSW = %c\n", PSW[0]);
      printf("PREG = %i\n", PREG);
      printf("ACC = %i\n", ACC);
      printf("PC = %i\n", PC);


}

//Compare contents of accumulator to contents in register Rn, n{0..3}
void OP30(char *IR, char *PSW){
  printf("Opcode = 30. Compare Register Equal\n") ;
    PrintIR(IR) ;
    int REG, ADDR;
    REG = ParseOp1Reg(IR);
    switch (REG) {
      case 0: ADDR = R0;break ;
      case 1: ADDR = R1;break ;
      case 2: ADDR = R2;break ;
      case 3: ADDR = R3;break ;
     }
    if(ACC == ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);


}

//Compare contents of accumulator to contents in Register Rn, n{0..3}
void OP31(char *IR, char *PSW){
  printf("Opcode = 31. Compare Register Less\n") ;
    PrintIR(IR) ;
    int REG, ADDR;
    REG = ParseOp1Reg(IR);
    switch (REG) {
      case 0: ADDR = R0;break ;
      case 1: ADDR = R1;break ;
      case 2: ADDR = R2;break ;
      case 3: ADDR = R3;break ;
     }
    if(ACC < ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);

}

//Compare contents of accumulator to contents in register Rn, n{0..3
void OP32(char *IR, char *PSW){
  printf("Opcode = 32. Compare Register Greater\n") ;
    PrintIR(IR) ;
    int REG, ADDR;
    REG = ParseOp1Reg(IR);
    switch (REG) {
      case 0: ADDR = R0;break ;
      case 1: ADDR = R1;break ;
      case 2: ADDR = R2;break ;
      case 3: ADDR = R3;break ;
     }
    if(ACC > ADDR)
      PSW[0] = 'T';
    else
      PSW[0] = 'F';

      printf("ACC = %i\n", ACC);

}

//If PSW[0] = T then PC = XX, X{0..9}
void OP33(char *IR, char *PSW, short int *PC){
  printf("Opcode = 33. Branch Conditional True\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1(IR);

    if(PSW[0] == 'T'){
      *PC = PREG;
    }
    else {
      *PC += 1;
    }
    printf("PC = %i\n", *PC);
    printf("ACC = %i\n", ACC);
    printf("PREG = %i\n", PREG);
    printf("PSW = %c\n", PSW[0]);

}

//If PSW[0] = F then PC = XX, X{0..9}
void OP34(char *IR, char *PSW, short int *PC){
  printf("Opcode = 34. Branch Conditional False\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1(IR);

    if(PSW[0] == 'F'){
      *PC = PREG;
    }
    else {
      *PC += 1;
    }

    printf("PC = %i\n", *PC);
    printf("ACC = %i\n", ACC);
    printf("PREG = %i\n", PREG);
}

//PC = XX, X{0..9}
void OP35(char *IR, short int *PC){
  printf("Opcode = 35. Branch Unconditional\n") ;
    PrintIR(IR) ;
    int PREG;
    PREG = ParseOp1(IR);

      *PC = PREG;

      printf("ACC = %i\n", ACC);
}

//opcode 36
void OP36(char *IR){
  printf("Opcode = 36. Trap Instruction\n") ;
    PrintIR(IR);
    int PREG,VAL;
    PREG = ParseOp1Reg(IR);
		VAL = ParseOp2Reg(IR);
    switch (PREG) {
      case 0: R0 = PREG;break;
      case 1: R1 = PREG;break;
      case 2: R2 = PREG;break;

    }
		switch (VAL) {
			case 0: //Forks
				ACC = //forks[i]
				P0 = PID;
				break;
			case 1: //doorman semaphore
				P1 = PID;
				break;
		}


}

void OP37(char *IR, int a, int b){
  printf("Opcode = 37. Modulo Instruction\n") ;
    PrintIR(IR);
		int VAL;
		a = ParseOp1Reg(IR);
		b = ParseOp2Reg(IR);
		VAL = a%b;

		ACC = VAL;
}
