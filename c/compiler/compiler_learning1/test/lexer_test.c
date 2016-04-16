#include "lexer_switch.h"
#include <stdio.h>

void check_word();

int main(){
  while(1){
    if(!getword_switch()){
      break;
    }
    check_word();
  }
  return 0;
}

void check_word(){
  switch(LEXER_WORD.type){
    case WORDTYPE_IDENTIFY:
      printf("%s is an identify\n", get_from_string_table(&LEXER_STRING_TABLE, LEXER_WORD.id_in_table));
      break;

    case WORDTYPE_INT:
      printf("%i is an integer\n", get_from_number_table(&LEXER_NUMBER_TALBE, LEXER_WORD.id_in_table));
      break;

    case WORDTYPE_UNARYOP:
      printf("%s is an unary operator\n", get_from_string_table(&LEXER_STRING_TABLE, LEXER_WORD.id_in_table));
      break;

    case WORDTYPE_BOOLBINARYOP:
      printf("%s is a bool binary operator\n", get_from_string_table(&LEXER_STRING_TABLE, LEXER_WORD.id_in_table));
      break;

    case WORDTYPE_BINARYOP:
      printf("%s is a binary operator\n", get_from_string_table(&LEXER_STRING_TABLE, LEXER_WORD.id_in_table));
      break;

    case WORDTYPE_BOOLUNARYOP:
      printf("%s is a bool unary operator\n", get_from_string_table(&LEXER_STRING_TABLE, LEXER_WORD.id_in_table));
      break;

    case WORDTYPE_NULL:
      break;
      
    default:
      printf("%c is a token\n", LEXER_WORD.type);
      break;
  }
  return;
}
