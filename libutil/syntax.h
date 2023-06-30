#ifndef ZCC_SYNTAX_H
#define ZCC_SYNTAX_H

typedef struct TYPE_LIST{
    char type_size;
    int id;
    struct TYPE_LIST* next;
}type_list;

char *readASen();
void addType(char type_size, char *name);
void initBaseType();
char getTypeSize(char *name);
char checkKeyWord(char *token);
char checkLegalToken(char *token);

extern int char_index_before_read;

#define ILLEGAL 0
#define LEGAL 1

#endif
