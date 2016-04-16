#include "../../inc/lexer/lexer.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

long int LEXER_LINENUMBER = 0;
LexerWord LEXER_WORD = {WORDTYPE_NULL, -1};
LexerStringTable LEXER_STRING_TABLE = {"\0", 0};
LexerNumberTable LEXER_NUMBER_TABLE = {0, 0};

void getblank(char *ch);
BOOL getnumber(char *ch);
BOOL getidentify(char *ch);
void getdouble_or_single_token(char *ch);

BOOL getword_switch(){
  static char ch = ' ';
  if(EOF == ch){
    return FALSE;
  }
  getblank(&ch);
  if(getnumber(&ch)){
    return TRUE;
  }
  if(getidentify(&ch)){
    return TRUE;
  }
  getdouble_or_single_token(&ch);
  return TRUE;
}

void getblank(char *ch){
  if('\n' == *ch){
    ++LEXER_LINENUMBER;
    *ch = ' ';
  }

  while(' ' == *ch || '\t' == *ch){
    *ch = getchar();
    if('\n' == *ch){
      ++LEXER_LINENUMBER;
      *ch = ' ';
    }
  }
}

BOOL getnumber(char *ch){
  if(!isdigit(*ch)){
    return FALSE;
  }
  int number = 0;
  int float_pos = 0;
  while(isdigit(*ch)){
    number = number * 10 + (*ch - '0');
    *ch = getchar();
    if(float_pos == 0){
      if('.' == *ch){
        float_pos = 1;
      }
    }
    else{
      ++float_pos;
    }
  }
  if(float_pos == 0){
    LEXER_WORD.type = WORDTYPE_INT;
    LEXER_WORD.id_in_table = add_to_number_table(&LEXER_NUMBER_TALBE, number);
  }
  else{
    LEXER_WORD.type = WORDTYPE_DOUBLE;
    LEXER_WORD.id_in_table = add_to_number_table(&LEXER_NUMBER_TABLE, number * 1.0 / float_pos);
  }
  return TRUE;
}

BOOL getidentify(char *ch){
  if(!(isalpha(*ch) || '_' == *ch)){
    return FALSE;
  }
  char str[MAX_STRING_LENGTH] = "\0";
  while(isalnum(*ch) || '_' == *ch){
    assert(strlen(str) < MAX_STRING_LENGTH);
    strcat(str, ch);
    *ch = getchar();
  }
  LEXER_WORD.type = WORDTYPE_IDENTIFY;
  LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, str);
  return TRUE;
}

void getdouble_or_single_token(char *ch){
  //处理空字符后可能遇到文件尾
  if(EOF == *ch){
    LEXER_WORD.type = WORDTYPE_NULL;
    return;
  }
  switch(*ch){
    case '+':
      *ch = getchar();
      switch(*ch){
        case '+':
          LEXER_WORD.type = WORDTYPE_UNARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "++");
          *ch = ' ';
          break;
        case '=':
          LEXER_WORD.type = WORDTYPE_BINARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "+=");
          *ch = ' ';
          break;
        default:
          LEXER_WORD.type = WORDTYPE_BINARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "+");
          break;
      }
      return;
      
    case '-':
      *ch = getchar();
      switch(*ch){
        case '-':
          LEXER_WORD.type = WORDTYPE_UNARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "--");
          *ch = ' ';
          break;
        case '=':
          LEXER_WORD.type = WORDTYPE_BINARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "-=");
          *ch = ' ';
          break;
        default:
          LEXER_WORD.type = WORDTYPE_BINARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "-");
          break;
      }
      return;
    case '/':
      *ch = getchar();
      switch(*ch){
        case '=':
          LEXER_WORD.type = WORDTYPE_BINARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "/=");
          *ch = ' ';
          break;
        case '/':
          do{
            *ch = getchar();
          }while('\n' != *ch);
          getword_switch();
          break;
        case '*':
          *ch = getchar();
          while(1){
            while(*ch != '*'){
              *ch = getchar();
            }
            if('/' == (*ch = getchar())){
              break;
            }
          }
          getword_switch();
          break;
        default:
          LEXER_WORD.type = WORDTYPE_BINARYOP;
          LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "/");
          break;
      }
      return;
    case '=':
      *ch = getchar();
      if('=' == *ch){
        LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
        LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "==");
        *ch = ' ';
        return;
      }
      LEXER_WORD.type = WORDTYPE_BINARYOP;
      LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "+");
      return;
    case '<':
      *ch = getchar();
      if('=' == *ch){
        LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
        LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "<=");
        *ch = ' ';
        return;
      }
      LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
      LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "<");
      return;
    case '>':
      *ch = getchar();
      if('=' == *ch){
        LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
        LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, ">=");
        *ch = ' ';
        return;
      }
      LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
      LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, ">");
      return;
    case '*':
      *ch = getchar();
      if('=' == *ch){
        LEXER_WORD.type = WORDTYPE_BINARYOP;
        LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "*=");
        *ch = ' ';
        return;
      }
      LEXER_WORD.type = WORDTYPE_BINARYOP;
      LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "*");
      return;
    case '&':
      *ch = getchar();
      if('&' == *ch){
        LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
        LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE,"&&");
        *ch = ' ';
        return;
      }
    case '|':
      *ch = getchar();
      if('|' == *ch){        
        LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
        LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE,"||");
        *ch = ' ';
        return;
      }
    case '!':
      *ch = getchar();
      if('=' == *ch){
        LEXER_WORD.type = WORDTYPE_BOOLBINARYOP;
        LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE,"!=");
        *ch = ' ';
        return;  
      }
      LEXER_WORD.type = WORDTYPE_BOOLUNARYOP;
      LEXER_WORD.id_in_table = add_to_string_table(&LEXER_STRING_TABLE, "!");
      return;
    default:
      LEXER_WORD.type = *ch;
      *ch = ' ';
      return;
  }
}


typedef enum LexerDfmState_{
  LEXERDFM_START,
  LEXERDFM_IDENTIFY,
  LEXERDFM_INT,
  LEXERDFM_DOUBLE,
  LEXERDFM_PLUS,
  LEXERDFM_PLUSPLUS,
  LEXERDFM_PLUSEQ,
  LEXERDFM_MINUS,
  LEXERDFM_MINUSMINUS,
  LEXERDFM_MINUSEQ,
  LEXERDFM_MULTIPLE,
  LEXERDFM_MULTIPLEEQ,
  LEXERDFM_DIVIDE,
  LEXERDFM_LINECOMMENT,
  LEXERDFM_BLOCKCOMMENT,
  LEXERDFM_DIVIDEEQ,
  LEXERDFM_GREAT,
  LEXERDFM_GREATEQ,
  LEXERDFM_LESS,
  LEXERDFM_LESSEQ,
  LEXERDFM_ASSIGN,
  LEXERDFM_EQ,
  LEXERDFM_NOT,
  LEXERDFM_NOTEQ,
  LEXERDFM_AND,
  LEXERDFM_BOOLAND,
  LEXERDFM_OR,
  LEXERDFM_BOOLOR,
  LEXERDFM_ELSE,
  LEXERDFM_ERROR,
  LEXERDFM_COUNT
}LexerDfmState

typedef enum LexerInputType_{
  INPUTTYPE_ALPHAUNDERLINE = 0,
  INPUTTYPE_NUMBER,
  INPUTTYPE_DOT,
  INPUTTYPE_PLUS,
  INPUTTYPE_EQUAL,
  INPUTTYPE_MINUS,
  INPUTTYPE_MULTIPLE,
  INPUTTYPE_DIVIDE,
  INPUTTYPE_GREAT,
  INPUTTYPE_LESS,
  INPUTTYPE_NOT,
  INPUTTYPE_AND,
  INPUTTYPE_NOT,
  INPUTTYPE_ELSE,
  INPUTTYPE_COUNT
}LexerInputType

int dfm[LEXERDFM_COUNT][INPUTTYPE_COUNT] = {
  {LEXERDFM_IDENTIFY, LEXERDFM_INT, LEXERDFM_PLUS,}
}

BOOL getword_dfm(){
  return TRUE;
}
