

#include "a_state.h"
#include "a_mem.h"







void asE_initState(as_State *S) {

    S->size_stack = 1;
    G(S)->strt.hash = asM_newVector(S, 26, as_String*);


}

                                                             
as_State *asE_newState(void) {

    as_State *S;
    
    asE_initState(S);

    return S;
}






















