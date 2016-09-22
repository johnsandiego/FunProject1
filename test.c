#include <stdio.h>
#include <string.h>
#include <stdint.h>
void OP4(char *IR);
void PrintIR(char *IR) ;
int ACC;
char IR[6];
char memory[100][6];
char x;
char *y;
short int P0 ; //these are the pointer registers
short int P1 ;
short int P2 ;
short int P3 ;
main(){

  int i;
    printf("enter 6 character: \n");
    //scanf("%c\n", IR[4] );
    scanf("%c\n", &IR[0] );
    scanf("%c", &IR[1] );
    scanf("%c\n", &IR[2] );
    scanf("%c", &IR[3] );
    scanf("%c\n", &IR[4] );
    scanf("%c", &IR[5] );
    //ACC = IR[4]-'0' + IR[5]-'0';
  //  printf("%c", IR[4]);
    //printf("%c\n", IR[5]);
    //printf("%i\n", ACC);
    for( i = 0; i<6;i++){
    printf("%i\n", IR[i]-'0');
    }
    OP4(IR);

}

void OP4(char *IR){
  int PREG, VAL, ADDR ;


  	 PREG = 2; // PREG = pointer register
     P2 = 2;
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
