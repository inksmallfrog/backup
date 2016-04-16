#include "expr.h"
#include "lexer.h"
#include <stdio.h>

int main(){
  lexer_getch();
  if(expr() == 0){
    printf("not a expr!\n");
  }
  printf("\n");
  return 0;
}
