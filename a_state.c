

#include "a_state.h"
#include "a_mem.h"
#include <stdio.h>






void asE_initState(as_State *S) {

    S->size_stack = 1;

    //global_State *g;
    G(S) = asM_alloc(G(S), sizeof(global_State), 0, 1);
    G(S)->fn_alloc = asM_alloc;
    G(S)->strt.hash = asM_newVector(S, 26, as_String*);

    int i = 0;
    for (; i < 26;i++) {

        G(S)->strt.hash[i] = NULL;
    }
    //G(S)->strt.hash[0]->hnext = NULL;
    G(S)->strt.size = 26;


}

                                                             
as_State *asE_newState(void) {

    as_State *S;
    S = asM_alloc(S, sizeof(as_State), 0, 1);
    
    asE_initState(S);

    return S;
}


void asE_closeState(as_State *S) {

    

}




void debug_strt(as_State *S) {

    if (S == NULL)  return;

    Table_String *strt = &(G(S)->strt);

    int i = 0;
    for (; i < strt->size; i++) {
        
        printf("%d: %d\t", i, strt->hash[i]);
        as_String *node = strt->hash[i];
        as_String *p = node;
        while (p) {

            printf("%d ", p->hash);
            p = p->hnext;
        }
        printf("\n");
    }


}














