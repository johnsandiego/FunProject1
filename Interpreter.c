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



int OP0(char *IR);
int OP1(char *IR);
int OP2();
int OP3(char *IR);
int OP4(char *IR);
int OP5();
int OP6(char *IR);
int OP7();
int OP8();
int OP9();
int OP10();
int OP11();
int OP12();
int OP13();
int OP14(char *IR);
int OP15(char *IR);
int OP16(char *IR);
int OP17();
int OP18();
int OP19();
int OP20(char *IR);
int OP21();
int OP22();
int OP23();
int OP24();
int OP25();
int OP26(char *IR);
int OP27();
int OP28();
int OP29(char *IR);
int OP30();
int OP31();
int OP32();
int OP33(char *IR);
int OP34(char *IR);
int OP35();
int HALT();

void printMEM() ;
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


 /* Provide implementation of the helper functions. You are free to provide as
    many additional helper functions as desired.
 */


	//This function returns the integer value of operand 1
	//when this operand is an immediate two-byte integer.

	int ParseOp1 (char *IR)
	    {
        int operand;
        operand = ((IR[2]-48)+(IR[3]-48)*10);
        return operand;

      }

	// returns the integer value of operand 2 when this operand is a two-byte integer.
	int ParseOp2 (char *IR)
	    {
        int operand2;
        operand2 = ((IR[4]-48)+(IR[5]-48)*10);
        return operand2;
      }

	//returns the integer value of operands 1 and 2 combined to form a 4-byte integer.
	int ParseOP1andOP2Imm(char *IR)
	    {
          return ParseOp1(*IR) + ParseOp2(*IR);


      }

	// returns the register number of the register used as operand  1 of an instruction.
	// Can be either Pointer or General-Purpose register.
	int ParseOp1Reg (char *IR)
	    {
            return ParseOp1();

      }





	// returns the register number of a register used as operand  2 of an instruction.
	// Can be either a Pointer or General-Purpose register.
	int ParseOp2Reg (char *IR)
	    {


        return register number;


      }

	// returns the data stored at memory location Memory_Location
	int FetchData(int Memory_Location)
	    {



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
        for(int i = 0; i<100; i++)
        {
          printf("%i\n", memory[i] );


        }

     }

//Now its time for the instruction execution functions.
// Here is the first.

	OP0(char *IR)
	{ int PREG, VAL ;
	  printf("Opcode = 00. Load Pointer Immediate\n") ;
   	  PrintIR(IR) ;

  	 PREG = ParseOp1Reg(IR) ;
  	 VAL = 	ParseOp2 (IR) ;

	switch(PREG)
		{case 0: P0 = VAL ;
		  case 1: P1 = VAL ;
		  case 2: P2 = VAL ;
		  case 3: P3 = VAL ;
		}
	  //Will print out junk until the two helper functions are implemented!
	  //printf("Loaded P[%d] with immediate value %d\n", PREG, VAL ) ;
	}

/* Now its your turn! Provide the prototype and implementation for the remaining opcodes.
 */
 OP1(char *IR)
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
 OP2(char *IR)
 { int PREG, VAL ;
   printf("Opcode = 00. Subtract Pointer Immediate\n") ;
       PrintIR(IR) ;

    PREG = ParseOp1Reg(IR) ;
    VAL = 	ParseOp2 (IR) ;

 switch(PREG)
   {case 0: P0 -= VAL ;
     case 1: P1 -= VAL ;
     case 2: P2 -= VAL ;
     case 3: P3 -= VAL ;
   }

 }
 OP3(char *IR)
 { int  VAL ; // value of operand 1 and 2 combined
   printf("Opcode = 00. Load Accumulator Immediate\n") ;
       PrintIR(IR) ;


    VAL = 	ParseOP1andOP2Imm(IR) ;

 switch(PREG)
   {case 0: ACC = VAL ;
     case 1: ACC = VAL ;
     case 2: ACC = VAL ;
     case 3: ACC = VAL ;
   }

 }
  OP4(char *IR){
    int PREG, VAL, ADDR ;
      printf("Opcode = 04. Load Pointer Immediate\n") ;
        PrintIR(IR) ;

       PREG = ParseOp1Reg(IR) ; // PREG = pointer register
       //PREG = 12 ;
       //pointer register = operand 1
       //memory location = pointer register
       //acc = memory location

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
