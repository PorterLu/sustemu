#ifndef __EXPR_H__
#define __EXPR_H__
#include <common.h>

typedef struct token {
  int type;
  char str[64];
} Token;

word_t expr(char *e, bool *success);
void init_regex();

#endif