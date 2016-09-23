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



void OP0(char *IR);
void OP1(char *IR);
void OP2(char *IR);
void OP3(char *IR);
void OP4(char *IR);
void OP5(char *IR);
void OP6(char *IR);
void OP7();
void OP8();
void OP9();
void OP10();
void OP11();
void OP12();
void OP13();
void OP14(char *IR);
void OP15(char *IR);
void OP16(char *IR);
void OP17();
void OP18();
void OP19();
void OP20(char *IR);
void OP21();
void OP22();
void OP23();
void OP24();
void OP25();
void OP26(char *IR);
void OP27();
void OP28();
void OP29(char *IR);
void OP30();
void OP31();
void OP32();
void OP33(char *IR);
void OP34(char *IR);
void OP35();
void HALT();

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

main(int argc, char *argv[])
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

     printf("PROGRAM COPIED INTO VM MEMORY!!\n") ;

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
		//case 1: OP1(IR) ; PC++; break ;
		//case 3: OP3(IR) ; PC++ ; break ;
		case 4: OP4(IR) ; PC++ ; break ;
		//case 6: OP6(IR) ; PC++ ; break ;
		//case 14: OP14(IR) ; PC++; break ;
		//case 15: OP15(IR) ; PC++; break ;
		//case 16: OP16(IR) ; PC++; break ;
		//case 20: OP20(IR) ; PC++; break ;
		//case 26: OP26(IR, PSW) ; PC++ ; break;
		//case 29: OP29(IR,PSW); PC++ ; break ;
		//case 33: OP33(IR, PSW, &PC) ; break ;
		//case 34: OP34(IR, PSW, &PC) ; break ;
		//case 99: printf("ALL DONE\n") ; Done = 1 ;
		default: printf("Instruction %d not found!~\n", opcode) ;
			 exit(0) ;
		}
	      }
}

	//This function returns the integer value of operand 1
	//when this operand is an immediate two-byte integer.

	int ParseOp1 (char *IR)
	    {
        int operand;
        operand = ((IR[2]-48)*10+(IR[3]-48)*1);
        return operand;

      }

	// returns the integer value of operand 2 when this operand is a two-byte integer.
	int ParseOp2 (char *IR)
	    {
        int operand2;
        operand2 = ((IR[4]-48)*10+(IR[5]-48)*1);
        return operand2;
      }

	//returns the integer value of operands 1 and 2 combined to form a 4-byte integer.
	int ParseOP1andOP2Imm(char *IR)
	    {
        int ParseOP1andOP2;
        ParseOP1andOP2 = ((IR[2]-48)*1000+(IR[3]-48)*100+(IR[2]-48)*10+(IR[3]-48)*1);
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
          MEM = (memory[Memory_Location][i])-48;
        }
          return MEM;
      }
	//Prints out the contents of the IR on the same line.
	void PrintIR(char *IR)
	    {
          printf("%c\n", IR);


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

 }
 //done - need revision and test
void OP3(char *IR)
 { int  VAL ; // value of operand 1 and 2 combined
   printf("Opcode = 03. Load Accumulator Immediate\n") ;
       PrintIR(IR) ;


    VAL = 	ParseOP1andOP2Imm(IR) ;
    ACC = VAL;

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
      ACC = VAL;
    printf("%i\n", ACC);

  }
  //done - need revision and test
void OP5(char *IR){
    int PREG, VAL, ADDR ;
      printf("Opcode = 05. Load Accululator Direct Addressing\n") ;
        PrintIR(IR) ;

       PREG = ParseOp1(IR) ; // PREG = pointer register

       VAL = (memory[PREG][2]-48)*10;
       VAL += (memory[PREG][3]-48)*1;
       ACC = VAL;

  }
void OP6(char *IR){
    int PREG, VAL, ADDR , i;
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

          memory[ADDR][3] = ACC-48;

  }
void OP7(char *IR){
    int PREG, ADDR;
      printf("Opcode = 07. Store Accumulator Direct Addressing\n") ;
        PrintIR(IR) ;
        PREG = IR[2]-48;
        ADDR = IR[3]-48;
       memory[PREG][ADDR] = ACC;


  }
void OP8(char *IR){

  




}
void OP9(){}
void OP10(){}
void OP11(){}
void OP12(){}
void OP13(){}
void OP14(char *IR){}
void OP15(char *IR){}
void OP16(char *IR){}
void OP17(){}
void OP18(){}
void OP19(){}
void OP20(char *IR){}
void OP21(){}
void OP22(){}
void OP23(){}
void OP24(){}
void OP25(){}
void OP26(char *IR){}
void OP27(){}
void OP28(){}
void OP29(char *IR){}
void OP30(){}
void OP31(){}
void OP32(){}
void OP33(char *IR){}
void OP34(char *IR){}
void OP35(){}
void HALT(){}
