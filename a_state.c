
#include "astro.h"
#include "a_state.h"
#include "a_mem.h"
#include "a_ui.h"
#include <stdio.h>





void asE_initStack(as_State *S) {

    S->stack = asM_newVector(S, MIN_STACK, as_Value);    
    S->top = S->stack;
    S->base = NULL;

}



as_State *as_newState(as_Alloc f) {

    as_State *S;
    S = f(S, sizeof(as_State), 0, 1);

    S->size_stack = 1;

    /*init global_State *g*/
    G(S) = f(G(S), sizeof(global_State), 0, 1);
    G(S)->fn_alloc = f;
    G(S)->strt.hash = asM_newVector(S, 26, as_String*);
    G(S)->strt.size = 26;

    int i = 0;
    for (; i < G(S)->strt.size; i++) {

        G(S)->strt.hash[i] = NULL;
    }
    
    /*init Astro stack*/
    asE_initStack(S);


    return S;
}

                                                             
as_State *asE_newState(void) {

    return as_newState(asU_alloc);
}


as_State *asE_closeState(as_State *S) {

    S->stack = asM_free(S, S->stack);
    
    G(S)->strt.hash = asM_free(S, G(S)->strt.hash);
    G(S) = asM_free(S, G(S));
    
    free(S);    /*since we can not free S by S itself, we use raw free function*/

    return NULL;
}



/*Debug functions*/
void debug_strt(as_State *S) {

    if (S == NULL)  return;

    Table_String *strt = &(G(S)->strt);

    int i = 0;
    for (; i < strt->size; i++) {
        
        printf("%d:\t%d\t", i, strt->hash[i]);
        as_String *node = strt->hash[i];
        as_String *p = node;
        while (p) {

            printf("%d: ", p->hash);
            printf("%s\t", getstr(p));
            p = p->hnext;
        }
        printf("\n");
    }


}














