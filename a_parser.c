

#include "a_parser.h"
#include "a_debug.h"
#include "a_func.h"
#include "a_string.h"


static void openFunc(LexState *ls, FuncState *fs) {



}



static void mainFunc(LexState *ls, FuncState *fs) {

    

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





















