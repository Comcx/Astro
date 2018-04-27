

#include "a_state.h"
#include "a_mem.h"







void asE_initState(as_State *S) {

    S->size_stack = 1;

    //global_State *g;
    G(S) = asM_alloc(G(S), sizeof(global_State), 0, 1);
    G(S)->fn_alloc = asM_alloc;
    G(S)->strt.hash = asM_newVector(S, 26, as_String*);


}

                                                             
as_State *asE_newState(void) {

    as_State *S;
    S = asM_alloc(S, sizeof(as_State), 0, 1);
    
    asE_initState(S);

    return S;
}


void asE_closeState(as_State *S) {

    

}



















