#ifndef ZCC_STR_H
#define ZCC_STR_H

void srcRollback();
void asmRollback();
void srcSeek(int type, long offset);
void asmSeek(int type, long offset);
char *readASen(_Bool rollBack);

#endif
