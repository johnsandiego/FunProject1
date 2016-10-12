#include <stdio.h>

void PrintQ(struct PCB *Current);
struct PCB *GetNextProcess(struct PCB **Head);
void MyToTail(struct PCB *Current, struct PCB **RQT);
void DeletePCB(struct PCB *Current);

struct PCB{
  struct PCB *NEXT_PCB;
  int PID;
  int IC;

}


int main() {
  struct PCB *RQ, *RQT, *Current;
  int i;
  for(i = 0; i<10; i++){
    Current -> NEXT_PCB = (struct PCB *)malloc(sizeof(struct PCB));
    Current -> NEXT_PCB -> NEXT_PCB = NULL;
    Current -> NEXT_PCB -> PID = i;
    Current -> Current -> NEXT_PCB;

  }
  Current = RQ;

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

    printf("NEW LIST OF READY PROCESSES\n", );
    PrintQ(RQ);
    sleep(1);

    if(RQ == NULL)
    break;
  }
  return 0;
}

void PrintQ(struct PCB *Current) {

}
struct PCB *GetNextProcess(struct PCB **Head){
  *Head->NEXT_PCB = (struct PCB *)malloc(sizeof(struct PCB));

}
void MyToTail(struct PCB *Current, struct PCB **RQT){

}
void DeletePCB(struct PCB *Current){
  struct PCB *temp = Current;

  free(temp);
}
