#ifndef ZCC_STR_H
#define ZCC_STR_H

void srcRollback();
void asmRollback();
void srcSeek(int type, long offset);
void asmSeek(int type, long offset);
char *readASen(_Bool rollBack);
char checkLegalToken(char *token);
void addType(char type_size, char *name);
void initBaseType();
char getTypeSize(char *name);


#define HEAD 0
#define CURR 1

#endif
