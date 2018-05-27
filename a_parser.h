

#ifndef A_PARSER_H
#define A_PARSER_H

#include "a_object.h"
#include "a_lex.h"



typedef enum {

    EX_VOID,    /*empty list, that is no expression*/
    EX_NIL,     /*constant nil*/
    EX_TRUE,    /*constant true*/
    EX_FALSE,   /*constant false*/
    EX_K,       /*constant k(info := index in k list)*/
    EX_FLT,     /*floating constant(n := numerical float value)*/
    EX_INT,     /*integer constant(i := numerical int value)*/
    EX_FIXED,   /*expression has its value in a fixed register(info := result register)*/
    EX_LOCAL,   /*local variable(info := local register)*/
    EX_UPVAL,   /*UpVal variable(info := index of upval in upvals)*/
    EX_INDEXED, /*indexed variable
                (ind.vt := whether 't' is register or upval;
                 ind.t := table register or upval;
                 ind.idx = key's R/K index)*/
    
    EX_JMP,     /*expression is a test or comparison
                (info := pc of corresponding jump instruction)*/
    EX_FIXABLE, /*expression can be put result in any register(info := instruction pc)*/
    EX_CALL,    /*expression is a function call(info := instruction pc)*/
    EX_VARARG   /*vararg expression(info := instruction pc)*/


} as_ExpKind;



typedef struct ExpDesc {

    as_ExpKind kind;

    union {
        as_Integer i;
        as_Number n;
        int info;
        struct {
            short idx;
            as_Byte t;
            as_Byte vt;
        } ind;

    } u;

    int list_t; /*patch list of true*/
    int list_f; /*patch list of false*/

} ExpDesc;



struct Block;


typedef struct FuncState {

    Proto *f;   /*current function*/
    struct FuncState *prev; /*previous function*/
    struct LexState *ls;    /*lex*/
    struct Block *bl;       /*chain of blocks*/

    int pc; /*next position to code*/
    int lastTarget; /*label of last jump label*/
    int pc_j;  /*list of pending jumps*/
    int num_k;  /*number of elements in k*/
    int num_p;  /*number of elements in p*/
    int num_absLineInfo;    /**/
    int firstLocal; /*index of the first loal var*/
    short num_LocVar;   /*number of local vars*/
    as_Byte num_actVar; /*number of active local vars*/
    as_Byte num_UpVal;  /*number of UpVals*/
    as_Byte freeReg;    /*first free register*/


} FuncState;





as_AClosure *asY_parser(as_State *S, as_IO *io, as_Buffer *buffer, 
                        const char *name, int firstChar);













#endif



