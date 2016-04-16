#include "lexer.h"
#include "token.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

Token CURRENT_TOKEN;
int CURRENT_LINE_NUMBER = 1;

void lexer_getch(){
  static char next_char = ' ';
  int state = discard_symbol(&next_char);
  if(1 == state){
    return;
  }
  else if(2 == state){
    lexer_getch();
  }
  if(1 == check_operator(&next_char)){
    return;
  }
  if(1 == check_number(&next_char)){
    return;
  }
  if(1 == check_variable(&next_char)){
    return;
  }
  CURRENT_TOKEN.name[0] = next_char;
  CURRENT_TOKEN.type = TokenType_Unknown;
  CURRENT_TOKEN.value = 0.0;
}

int discard_symbol(char *character){
  //处理空字符和换行
  while(*character == ' ' || *character == '\t' || *character == '\n'){
    if(*character == '\n'){
      ++CURRENT_LINE_NUMBER;
    }
    *character = getchar();
  }
  //处理注释，也有可能是除法
  if(*character == '/'){
    *character = getchar();
    //单行注释
    if(*character == '/'){
      do{
        *character = getchar();
      }while(*character == '\n');
      return 2;
    }
    //多行注释
    else if(*character == '*'){
      do{
        *character = getchar();
        //！！考虑引号的嵌套层次
      }while(!(*character == '*' && (*character = getchar()) == '/'));
      return 2;
    }
    //除法
    else{
      CURRENT_TOKEN.name[0] = '/';
      CURRENT_TOKEN.type = TokenType_Operator;
      CURRENT_TOKEN.value = 0.0;
      return 1;
    }
  }
  if(*character == EOF){
    CURRENT_TOKEN.name[0] = ' ';
    CURRENT_TOKEN.type = TokenType_Lineend;
    CURRENT_TOKEN.value = 0.0;
    return 1;
  }

  return 0;
}

int check_operator(char *character){
  switch(*character){
    case '+':
    case '-':
    case '*':
    case '%':
      CURRENT_TOKEN.name[0] = *character;
      CURRENT_TOKEN.type = TokenType_Operator;
      CURRENT_TOKEN.value = 0.0;
      *character = ' ';
      return 1;
    case ';':
      CURRENT_TOKEN.name[0] = *character;
      CURRENT_TOKEN.type = TokenType_Lineend;
      CURRENT_TOKEN.value = 0.0;
      *character = ' ';
      return 1;

    case '(':
      CURRENT_TOKEN.name[0] = '(';
      CURRENT_TOKEN.type = TokenType_Lbrace;
      CURRENT_TOKEN.value = 0.0;
      *character = ' ';
      return 1;

    case ')':
      CURRENT_TOKEN.name[0] = ')';
      CURRENT_TOKEN.type = TokenType_Rbrace;
      CURRENT_TOKEN.value = 0.0;
      *character = ' ';
      return 1;

    default:
      break;
  }
  return 0;
}

int check_number(char *character){
  if(isdigit(*character)){
    int value = 0;
    int pos = 0;
    int is_float = 0;
    do{
      if(is_float == 1){
        ++pos;
      }
      value = value * 10 + (*character - '0');
      *character = getchar();
      if(*character == '.'){
        is_float = 1;
        *character = getchar();
      }
    }while(isdigit(*character));

    strcpy(CURRENT_TOKEN.name, "number");
    CURRENT_TOKEN.type = (is_float == 0)?TokenType_Integer : TokenType_Float;
    CURRENT_TOKEN.value = (pos == 0)?value : value / (pos * 1.0f);
    return 1;
  }
  return 0;
}

int check_variable(char *character){
  if(isalpha(*character) || *character == '_'){
    int i = 0;
    do{
      CURRENT_TOKEN.name[i] = *character;
      ++i;
      if(i > _MAX_TOKEN_LENGTH_ - 1){
        //出错信息，超长的命名
        break;
      }
    }while(isalnum(*character) || *character == '_');
    CURRENT_TOKEN.type = TokenType_Id;
    CURRENT_TOKEN.value = 0.0;
    return 1;
  }
  return 0;
}
