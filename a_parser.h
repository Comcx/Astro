

#ifndef A_PARSER_H
#define A_PARSER_H

#include "a_object.h"
#include "a_lex.h"


typedef struct FuncState {

    Proto *f;
    struct FuncState *prev;
    struct LexState *ls;
    //struct BlockCnt *bl;

    int pc;
    int lastTarget;
    int line_prev;
    int num_k;
    int num_p;
    int num_absLineInfo;
    int firstLocal;
    short num_LocVar;
    as_Byte num_actVar;
    as_Byte num_UpVal;
    as_Byte freeReg;


} FuncState;



















#endif



