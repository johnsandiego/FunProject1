#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Vars.h"

struct PCB *GetNextProcess() ;
void printMEM() ;
/*These variables are associated with the implementation of the VM*/
int i, j, k ;
int ProgSize ;
char input_line [7] ;


main(int argc, char *argv[])
{
 //Variables used by OS

 	struct PCB *RQ, *tmp, *RQT, *Current ;

        RQ = (struct PCB *) malloc (sizeof (struct PCB)) ;
        RQ->PID = 0;
        RQ->IC = 2 ;
        tmp = RQ ;
        for(i = 1; i < 10; i++)
                {tmp->Next_PCB = (struct PCB *) malloc (sizeof (struct PCB)) ;
                 tmp->Next_PCB->PID = i ;

                 tmp->Next_PCB->IC = (rand() % 10) + 1 ; //rand returns 0 .. MAX
                 tmp->Next_PCB->Next_PCB = NULL ;
                 tmp = tmp->Next_PCB ;
                }

        RQT = tmp ;
        RQT->Next_PCB = NULL ;

	tmp = RQ ;
	for (i = 0; i < 10 ; i++)
		{

		 LoadProgram( i, &tmp) ;
		 printf("LimitReg = %d. IC = %d\n",tmp->LimitReg, tmp->IC) ;
		 //tmp->IC = i + 2 ;
		 tmp = tmp->Next_PCB ;
		}




	printf("Now let's EXECUTE IT! WOOOEEEEEE!!!\n") ;

	while(1)
          {

                Current = GetNextProcess(&RQ) ;
		RestoreState(Current) ;
                printf("CURRENT PID %d, IC %d\n", Current->PID, Current->IC) ;
                //Current->IC-- ;

		int Completed = ExecuteProc(Current) ;
                if (Completed)
                        {
                         printf("Removing PID %d\n", Current->PID) ;
                         DeletePCB(Current) ;
                        }

                else
                        {SaveState(&Current) ;
			 printf("Moving PID %d to TAIL\n", Current->PID) ;
                         MvToTail(Current, &RQT) ;
                         printf("RQT is %d\n", RQT->PID) ;
			 if(RQ == NULL)
                                RQ = RQT ;
                        }

                PrintQ(RQ) ;
                sleep(1) ;
                if (RQ == NULL)
                        break ;

        }

}

/*	This function returns the PCB at the head of the RQ and updates
	RQ to point to the next PCB in the list
*/

	struct PCB *GetNextProcess(struct PCB **RQ)
	{
    struct PCB *temp = *Head;
    (*Head) = (*Head) -> NEXT_PCB;
    temp -> NEXT_PCB = NULL;

    return temp;


  }


/*	Deletes the PCB (using free) */

	DeletePCB(struct PCB *Current)
	{
      free(Current);

  }

/*	This function places the PCB pointed to by Current at the tail of the
	Ready Queue and updates the RQT pointer.
*/

	MvToTail (struct PCB *Current, struct PCB **RQT)
	{


  }


/*	Prints out the elements of a linked list */

	PrintQ(struct PCB *Head)
	{



  }

/*	This function executes a process for the number of instructions in its "time slice",
	which is held in the IC register of its PCB. It returns a 1 if the process has completed
	its execution (i.e., it has terminated), or a 0 if it has not yet terminated.
*/

	ExecuteProc(struct PCB *CurrentProc)
	{



  }

/*	This function restores the state of the process that is set to begin its
	execution
*/

	RestoreState(struct PCB *NextProc)
	{



  }

/*	This function saves the state of the VM into the PCB of the process that
	just completed its "time slice"
*/
	SaveState(struct PCB **PrevProc)
	{


  }


/* 	This function loads in 10 copies of the same program. You can do likewise,
	or load in different programs. It needs to work in either case.
*/


LoadProgram(int PID, struct PCB **tmp)
  {
        int i, fp ;
	int program_line = 100 * PID ;
	(*tmp)->BaseReg  = program_line ;
	(*tmp)->LimitReg = program_line + 100;
        fp = open("Fib.PB", O_RDONLY) ; //always check the return value.
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
