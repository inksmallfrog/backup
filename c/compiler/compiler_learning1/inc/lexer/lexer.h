#ifndef _INKSMALLFROG_COMPILER_LEARNING_LEXER_
#define _INKSMALLFROG_COMPILER_LEARNING_LEXER_

#include "../share/util.h"
#include "lexer_wordtype.h"
#include "lexer_table.h"

typedef struct LexerWord_{
  LexerWordType type;
  int id_in_table;
}LexerWord;

long int LEXER_LINENUMBER;
LexerWord LEXER_WORD;
LexerStringTable LEXER_STRING_TABLE;
LexerNumberTable LEXER_NUMBER_TALBE;

BOOL getword_switch();

BOOL getword_dfm();

#endif
