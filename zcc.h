#ifndef ZCC_ZCC_H
#define ZCC_ZCC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "libutil/util.h"
#include "function.h"
#include "ctree.h"
#include "asm.h"
#include "expr.h"
#include "global.h"
#include "i386.h"

extern FILE *srcfp;
extern FILE *asmfp;





// global var flags
//   high<<<<<bit                                                           bit>>>>>low
//    b7     |     b6   |    b5    |     b4     |    b3   |   b2   |   b1   |   b0  |
//  reserved | reserved | reserved | PTR OF PTR | pointer | extern | static | const |



#define BYTE 1
#define WORD 2
#define DWORD 3
#define ARRAY 4
#define POINTER 5

#define GLOBAL_VAR_DEF_SENT 0
#define GLOBAL_FUNC_DEF_SENT 1

#endif
