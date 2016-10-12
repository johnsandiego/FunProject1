#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct PCB{
  struct PCB *NEXT_PCB;
  int PID;
  int IC;

};
struct PCB *PrintQ(struct PCB *Current);
struct PCB *GetNextProcess(struct PCB **Head);
void MyToTail(struct PCB *Current, struct PCB **RQT);
void DeletePCB(struct PCB *Current);




int main() {
  struct PCB *RQ, *RQT, *Current;
  int i;
  for(i = 0; i<10; i++){
    Current -> NEXT_PCB = (struct PCB *)malloc(sizeof(struct PCB));
    Current -> NEXT_PCB -> NEXT_PCB = NULL;
    Current -> NEXT_PCB -> PID = i;
    Current -> NEXT_PCB -> IC = Current->NEXT_PCB->PID + 2;
    Current = Current -> NEXT_PCB;

  }


  PrintQ(RQ);
  while (1) {
    Current = GetNextProcess(&RQ);
    Current -> IC--;
    if(Current -> IC ==0){
      DeletePCB(Current);
    }
    else{
      MyToTail(Current, &RQT);
    }

    printf("NEW LIST OF READY PROCESSES\n" );
    PrintQ(RQ);
    sleep(1);

    if(RQ == NULL)
    break;
  }
  return 0;
}

struct PCB *PrintQ(struct PCB *Current) {
  struct PCB *temp = Current;
  while (temp != NULL) {
    printf("%d\n",temp->PID);
    temp = temp -> NEXT_PCB;
  }
}
struct PCB *GetNextProcess(struct PCB **Head){
  struct PCB *temp = *Head;
  temp = temp->NEXT_PCB;
  return temp;
}
void MyToTail(struct PCB *Current, struct PCB **RQT){
  
  Current = *RQT;

}
void DeletePCB(struct PCB *Current){
  struct PCB *temp = Current;

  free(temp);
}
