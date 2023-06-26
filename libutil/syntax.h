#ifndef ZCC_SYNTAX_H
#define ZCC_SYNTAX_H

char *readASen();
void addType(char type_size, char *name);
void initBaseType();
char getTypeSize(char *name);
char checkKeyWord(char *token);
char checkLegalToken(char *token);

#define ILLEGAL 0
#define LEGAL 1

#endif
