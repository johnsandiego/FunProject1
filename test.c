#include <stdio.h>
int ParseOp1(char *IR);
void OP6(char *IR);
int ParseOp1Reg(char *IR);
int ParseOP1andOP2Imm(char *IR);

char IR[6];
int operand;
int main(){

  IR[0] = '0';
  IR[1] = '4';
  IR[2] = '0';
  IR[3] = '0';
  IR[4] = '0';
  IR[5] = '9';

  //ParseOp1(IR);


  printf("%i\n", ParseOP1andOP2Imm(IR));

}

int ParseOp1 (char *IR)
    {

      operand = ((IR[2]-48)*10+(IR[3]-48)*1);
      return operand;

    }

int ParseOp1Reg(char *IR){



}

int ParseOP1andOP2Imm(char *IR)
    {
      int ParseOP1andOP2;
      ParseOP1andOP2 = ((IR[2]-48)*1000+(IR[3]-48)*100+(IR[4]-48)*10+(IR[5]-48)*1);
        return ParseOP1andOP2;


    }
