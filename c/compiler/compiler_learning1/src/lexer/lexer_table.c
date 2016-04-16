#include "../../inc/lexer/lexer_table.h"
#include <string.h>
#include <assert.h>

int add_to_string_table(LexerStringTable *table, char *content){
  if(MAX_TABLE_ITEM_COUNT == ++table->current_point){
    table->current_point = 0;
  }
  assert(strlen(content) < MAX_STRING_LENGTH);
  strcpy(table->content[table->current_point], content);
  return table->current_point;
}

const char *get_from_string_table(LexerStringTable *table, int point){
  return table->content[point];
}

int add_to_number_table(LexerNumberTable *table, double number){
  if(MAX_TABLE_ITEM_COUNT == ++table->current_point){
    table->current_point = 0;
  }
  table->number[table->current_point] = number;
  return table->current_point;
}

const int get_from_number_table(LexerNumberTable *table, int point){
  return table->number[point];
}
