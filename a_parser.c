

#include "a_parser.h"
#include "a_debug.h"
#include "a_func.h"
#include "a_string.h"
#include "a_code.h"



typedef struct Block {

    struct Block *prev;
    int firstLabel;
    int firstGoto;
    as_Byte num_actVar;
    as_Byte hasUpVal;
    as_Byte isLoop;

} Block;





static void openFunc(LexState *ls, FuncState *fs, Block *bl) {

    Proto *f = fs->f;
    fs->prev = ls->fs;
    ls->fs = fs;
    fs->pc = 0;
    fs->lastTarget = 0;
    fs->pc_j = NO_JUMP;
    fs->freeReg = 0;
    fs->num_k = 0;
    fs->num_p = 0;
    fs->num_UpVal = 0;
    fs->num_LocVar = 0;
    fs->num_actVar = 0;
    fs->firstLocal = 0; /*this is unfinished!*/
    fs->bl = NULL;
    f->source = ls->source;
    f->size_maxStack = 2;

}



static void mainFunc(LexState *ls, FuncState *fs) {

    Block bl;
    ExpDesc e;
    openFunc(ls, fs, &bl);

}



as_AClosure *asY_parser(as_State *S, as_IO *io, as_Buffer *buffer, 
                        const char *name, int firstChar) {

    LexState lexState;
    FuncState funcState;
    as_AClosure *cl = asF_newAClosure(S, 1);
    funcState.f = asF_newProto(S);
    funcState.f->source = asS_newString(S, name);
    lexState.buffer = buffer;

    asX_setInput(S, &lexState, io, funcState.f->source, firstChar);

    /*TEST AREA, should be removed later*/
    asX_next(&lexState);
    printf("%lf\n", lexState.t.semInfo.r);
    
    asX_next(&lexState);
    printf("%d\n", lexState.t.semInfo.i);

    asX_next(&lexState);
    printf("%lf\n", lexState.t.semInfo.r);

    asX_next(&lexState);
    printf("%s\n", lexState.buffer->buffer);
    
    /*Since we haven't make use of GC system, we free spaces bu hand*/
    funcState.f->source = asS_freeString(S, funcState.f->source);
    funcState.f = asM_free(S, funcState.f);

    return cl;
}





















