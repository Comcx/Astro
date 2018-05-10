
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astro.h"
#include "a_mem.h"
#include "a_state.h"
#include "a_string.h"
#include <assert.h>

struct Test {

    int a;
    int b;

};



int main(int argc, char *argv[]) {

    
    as_Integer i = 5;
    as_Number n = 6.0;

    

    //memcpy(getstr(test), "can you?" ,8);

    //printf("%s", getstr(test));
    
    //test = asM_alloc((void*)test, 0, 0, 0);
    
    //printf("%d\n", test->a);    
    as_State *S = asE_newState();
    //test = asM_malloc(S, sizeof(struct Test));
    //test->a = 7;

    //printf("%d\n", test->a);
    
    /*
    int *arr = asM_newVector(S, 3, int);
    arr[2] = 2;
    arr = asM_free(S, arr);
    printf("\n\n%d", arr[2]);
    */

    as_String *s = asS_newString(S, "sfdgfd");
    debug_String(S, s);

    printf("\n");
    as_String *ss = asS_newString(S, "qwret");
    debug_String(S, ss);

    printf("\n");
    as_String *sss = asS_newString(S, "adsjdbvgf");
    debug_String(S, sss);

    //s = asS_freeString(S, s);
    
    debug_strt(S);
    //assert(0);

    return 0;
}














