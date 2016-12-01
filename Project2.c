/*
Author: John San Diego
COS 331 operating system
Project 2 - PBrain12 Interpreter
Version .80 - 10/23/2016

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
#include "Vars.h"
#include "Opcodes.h"

void PrintQ(struct PCB *Current);
struct PCB *GetNextProcess(struct PCB **RQ);
void MoveToTail(struct PCB *Current, struct PCB **RQT);
void DeletePCB(struct PCB *Current);
void RestoreState(struct PCB *NextProc);
void SaveState(struct PCB **PrevProc);
void LoadProgram(int PID, struct PCB **tmp);
int ExecuteProc(struct PCB *CurrentProc);

/*These variables are associated with the implementation of the VM*/
int i, j, k ;
int ProgSize ;
char input_line [7] ;
int PID ;
short int PC, P0, P1, P2, P3;
int IC ; //number of instructions before preemption (i.e., time slice)
int R0, R1, R2, R3 ;
char PSW[2] ;
int ACC ;
int BaseReg, LimitReg ;
int main(int argc, char *argv[])
{
 //Variables used by OS

 	struct PCB *RQ, *tmp, *RQT, *Current ;

        RQ = (struct PCB *) malloc (sizeof (struct PCB));
        RQ->PID = 0;
        RQ->IC = 2;
        tmp = RQ;
        printf("About to create a linked list\n" );
        for(i = 1; i < 10; i++)
        {
          tmp->Next_PCB = (struct PCB *) malloc (sizeof (struct PCB)) ;
          tmp->Next_PCB->PID = i ;
          tmp->Next_PCB->IC = (rand() % 10) + 1 ; //rand returns 0 .. MAX
          tmp->Next_PCB->Next_PCB = NULL ;
          tmp = tmp->Next_PCB ;
        }
        printf("created a linked list\n" );

        RQT = tmp ;
        RQT->Next_PCB = NULL ;

	tmp = RQ ;
	for (i = 0; i < 10 ; i++)
		{
      printf("load a program\n" );

		 LoadProgram( i, &tmp) ;
		 printf("LimitReg = %d. IC = %d\n",tmp->LimitReg, tmp->IC) ;
		 //tmp->IC = i + 2 ;
		 tmp = tmp->Next_PCB ;
		}

	printf("Now let's EXECUTE IT! WOOOEEEEEE!!!\n") ;

	while(1)
  {
    Current = GetNextProcess(&RQ) ;
		RestoreState(Current);
    printf("CURRENT PID %d, IC %d\n", Current->PID, Current->IC) ;
    //Current->IC-- ;
		int Completed = ExecuteProc(Current) ;
    if (Completed)
    {
      printf("Removing PID %d\n", Current->PID) ;
      DeletePCB(Current) ;
    }
    else
    {
      SaveState(&Current);
			printf("Moving PID %d to TAIL\n", Current->PID) ;
      MoveToTail(Current, &RQT) ;
      printf("RQT is %d\n", RQT->PID) ;
			if(RQ == NULL)
        RQ = RQT ;
    }

      PrintQ(RQ) ;
      sleep(1) ;
      if (RQ == NULL)
        break ;

    }
    return 0;
}

/*	This function returns the PCB at the head of the RQ and updates
	RQ to point to the next PCB in the list
*/

struct PCB *GetNextProcess(struct PCB **RQ)
	{
    struct PCB *temp = *RQ;
    (*RQ) = (*RQ)->Next_PCB;
    temp->Next_PCB = NULL;

    return temp;


  }


/*	Deletes the PCB (using free) */

void DeletePCB(struct PCB *Current)
	{

      free(Current);

  }

/*	This function places the PCB pointed to by Current at the tail of the
	Ready Queue and updates the RQT pointer.
*/

void MoveToTail (struct PCB *Current, struct PCB **RQT)
	{
    if((*RQT) != Current){
      (*RQT)->Next_PCB = Current; //RQT next pcb points to the current running process
      (*RQT) = Current;}  // RQT points to the Current
  }


/*	Prints out the elements of a linked list */

void PrintQ(struct PCB *Current)
	{
    struct PCB *temp = (struct PCB *)malloc(sizeof(struct PCB));
    temp = Current;
    int limit = 15;
     while (temp != NULL && limit>0) {
       limit--;
      printf("PQ tmp PID:%d\n",temp->PID);
      temp = temp->Next_PCB;
     }
     if(limit==0){
       usleep(100000);
     }


  }

/*	This function executes a process for the number of instructions in its "time slice",
	which is held in the IC register of its PCB. It returns a 1 if the process has completed
	its execution (i.e., it has terminated), or a 0 if it has not yet terminated.
*/
int	ExecuteProc(struct PCB *CurrentProc)
	{
    int i;
    int Done = 0;
    int Completed = 0;
    int BaseAddress = CurrentProc->BaseReg;
    int MaxAddress = CurrentProc->LimitReg;
    int NumbInstruction = CurrentProc->IC;

    // leave PC in range of 0..99
    //Effective address is PC + BaseAddress

    while(1)
    {

      for(i = 0; i<6; i++){
        IR[i] = memory[PC + BaseAddress][i];
        //printf("%c\n", IR[i]);
        opcode = ((IR[0])-48)*10;
        opcode += ((IR[1])-48);

      }
      printf("\n loop: New PC is %d opcode is %d \n",PC, opcode );
      switch (opcode) {
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
    		case 33: OP33(IR, PSW, &PC); break ;
    		case 34: OP34(IR, PSW, &PC); break ;
        case 35: OP35(IR, &PC); break ;
    		case 99: printf("ALL DONE\n") ; Done = 1 ; Completed = 1;break;
    		default: printf("Instruction %d not found!!~\n", opcode);
    			 exit(0) ;
    		}
        NumbInstruction--;    //decrease the number of Instruction
        if(NumbInstruction == 0){

          Done = 1;
        //  Completed = 1;
        }
        printf("NumbInstruction: %d\n", NumbInstruction);

        if(Done)
          break;


    }
    return Completed;


  }

/*	This function restores the state of the process that is set to begin its
	execution
*/

void RestoreState(struct PCB *NextProc)
	{
    PID = NextProc->PID;
    IC = NextProc->IC;

    PC = NextProc->PC;

    P0 = NextProc->P0;
    P1 = NextProc->P1;
    P2 = NextProc->P2;
    P3 = NextProc->P3;

    R0 = NextProc->R0;
    R1 = NextProc->R1;
    R2 = NextProc->R2;
    R3 = NextProc->R3;

    ACC = NextProc->ACC;

    LimitReg = NextProc-> LimitReg;
    BaseReg = NextProc->BaseReg;

    PSW[0] = NextProc->PSW[0];
    PSW[1] = NextProc->PSW[1];

  }

/*	This function saves the state of the VM into the PCB of the process that
	just completed its "time slice"
*/
void SaveState(struct PCB **PrevProc)
	{

      //*temp->
      (*PrevProc)->PID = PID;
      (*PrevProc)->IC = IC;
      (*PrevProc)->PC = PC;

      (*PrevProc)->R0 = R0;
      (*PrevProc)->R1 = R1;
      (*PrevProc)->R2 = R2;
      (*PrevProc)->R3 = R3;

      (*PrevProc)->P0 = P0;
      (*PrevProc)->P1 = P1;
      (*PrevProc)->P2 = P2;
      (*PrevProc)->P3 = P3;

      (*PrevProc)->ACC = ACC;
      (*PrevProc)->BaseReg = BaseReg;
      (*PrevProc)->LimitReg = LimitReg;
      (*PrevProc)->PSW[0] = PSW[0];
      (*PrevProc)->PSW[1] = PSW[1];



  }
/* 	This function loads in 10 copies of the same program. You can do likewise,
	or load in different programs. It needs to work in either case.
*/
void LoadProgram(int PID, struct PCB **tmp)
{
  int i, fp ;
	int program_line = 100 * PID ;
	//(*tmp)->BaseReg  = program_line ;
	//(*tmp)->LimitReg = program_line + 100;
  fp = open("program3", O_RDONLY) ; //always check the return value.
    printf("Open is %d\n", fp) ;

        if (fp < 0) //error in read
                {printf("Could not open file\n");
                 exit(0) ;
                }

 	int ret = read (fp, input_line, 7 ) ; //returns number of characters read`

	while (1)
  {
         	 if (ret <= 0) //indicates end of file or error
                	break ; //breaks out of infinite loop

        	 printf("Copying Program line %d into memory\n", program_line) ;
        	 for (i = 0; i < 6 ; i++)
              {
                	 memory[program_line][i] = input_line[i] ;
                	 printf("%c ", memory[program_line][i]) ;
            	}
        	 printf("\n") ;

        	 ret = read (fp, input_line, 7 ) ;

        	//if the firat character is a 'Z' then you are reading data.
        	//No more program code so break out of loop

		        if(input_line[0] == 'Z')
      	       break ;

        	program_line++ ; //now at a new line in the prog
  }

  printf("Read in Code. Closing File\n") ;
  close(fp) ;
}
