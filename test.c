#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
struct PCB{
  struct PCB *NEXT_PCB;
  int PID;
  int IC;
};
void PrintQ(struct PCB *Current);
struct PCB *GetNextProcess(struct PCB **Head);
void MoveToTail(struct PCB *Current, struct PCB **RQT);
void DeletePCB(struct PCB *Current);




int main() {
  // RQ is the head , RQT is the TAIL, Current is a current running process
  struct PCB *RQ, *RQT, *Current, *temp;
  int i;
  RQ = NULL;
  RQ = (struct PCB*)malloc(sizeof(struct PCB));
  RQ->PID = 0;
  RQ->IC = 2;
  Current = RQ;
  for(i = 1; i<10; i++){
    temp = (struct PCB *)malloc(sizeof(struct PCB));
    temp-> NEXT_PCB = NULL;
    temp-> PID = i;
    temp-> IC = i + 2;

    // if(i==9){
    //   RQ = Current;
    // }
    //printf("%d\n", Current->PID );

    Current -> NEXT_PCB = temp;
    Current = Current -> NEXT_PCB;
    printf("in the loop: %d\n",temp->IC);
    RQT = Current;
  }

  PrintQ(RQ);
  while (RQ != NULL) {
    Current = GetNextProcess(&RQ);
    Current -> IC--;
    if(Current->NEXT_PCB != NULL){

      printf("Current PID:%d\n", Current->PID);
    }
    printf("IC :%d\n", Current->IC);
    if(Current -> IC ==0){
      DeletePCB(Current);
      printf("\n" );
    }
    else{
        MoveToTail(Current, &RQT);
        if(RQ == NULL){
          RQ = Current;
          }


    }

    printf("NEW LIST OF READY PROCESSES\n" );
    PrintQ(RQ);
    usleep(100000);
    if(RQ == NULL)
    break;
  }
  return 0;
}

void PrintQ(struct PCB *Current) {
  struct PCB *temp = (struct PCB *)malloc(sizeof(struct PCB));
  temp = Current;
  int limit = 15;
   while (temp != NULL && limit>0) {
     limit--;
    printf("PQ tmp PID:%d\n",temp->PID);
    temp = temp -> NEXT_PCB;
   }
   if(limit==0){
     usleep(10000000);
   }

}
//removes pcb at head of the list and returns a pointer to it
struct PCB *GetNextProcess(struct PCB **Head){
  struct PCB *temp = *Head;
  (*Head) = (*Head) -> NEXT_PCB;
  temp -> NEXT_PCB = NULL;

  return temp;

  // struct PCB *temp = (struct PCB *)malloc(sizeof(struct PCB));
  // temp = *Head;
  // temp = temp->NEXT_PCB;
  // printf("Head was: %d, Now: %d\n",temp->PID, (*Head)->PID );
  // return temp;
}

void MoveToTail(struct PCB *Current, struct PCB **RQT){
if((*RQT) != Current){
  (*RQT)->NEXT_PCB = Current; //RQT next pcb points to the current running process
  (*RQT) = Current;}  // RQT points to the Current

//  (*RQT) -> NEXT_PCB = NULL; //stops the loop


}
void DeletePCB(struct PCB *Current){
  free(Current);
}
