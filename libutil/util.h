#ifndef ZCC_STR_H
#define ZCC_STR_H

#include "syntax.h"

void srcRollback();
void asmRollback();
void srcSeek(int type, long offset);
void asmSeek(int type, long offset);
int hash(char *str);
void itoa(int n, char s[]);
void loggerf(int level, char *str);


#define HEAD 0
#define CURR 1

#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define FATAL 5



#endif
