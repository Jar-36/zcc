#ifndef ZCC_EXPR_H
#define ZCC_EXPR_H


extern local_var *headLocalVar;
void constructLocalVar(char *expr);

#define EXPR_DEF 1
#define EXPR_R2L 2
#define EXPR_BLK 5

#endif
