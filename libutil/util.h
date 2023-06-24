#ifndef ZCC_STR_H
#define ZCC_STR_H

void srcRollback();
void asmRollback();
void srcSeek(int type, long offset);
void asmSeek(int type, long offset);
char *readASen(_Bool rollBack);
void addType(char type_size, char *name);
void initBaseType();
char getTypeSize(char *name);
void loggerf(int level, char *str);
char checkKeyWord(char *token);


#define HEAD 0
#define CURR 1

#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define FATAL 5

#endif
