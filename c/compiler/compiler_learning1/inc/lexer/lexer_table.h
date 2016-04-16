#ifndef _INKSMALLFROG_COMPILER_LEARNING_LEXER_STRING_TABLE_
#define _INKSMALLFROG_COMPILER_LEARNING_LEXER_STRING_TABLE_

#define MAX_STRING_LENGTH 128
#define MAX_TABLE_ITEM_COUNT 3

typedef struct LexerStringTable_{
  char content[MAX_TABLE_ITEM_COUNT][MAX_STRING_LENGTH];
  int current_point;
}LexerStringTable;

int add_to_string_table(LexerStringTable *table, char *content);
const char *get_from_string_table(LexerStringTable *table, int point);

typedef struct LexerNumberTable_{
  double number[MAX_TABLE_ITEM_COUNT];
  int current_point;
}LexerNumberTable;

int add_to_number_table(LexerNumberTable *table, double number);
const int get_from_number_table(LexerNumberTable *table, int point);

#endif
