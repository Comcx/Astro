
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astro.h"
#include "a_mem.h"
#include "a_state.h"
#include "a_string.h"
#include "a_table.h"
#include "a_code.h"
#include "a_debug.h"




int main(int argc, char *argv[]) {

    
    //memcpy(getstr(test), "can you?" ,8);
    
    as_State *S = asE_newState();
    //test = asM_malloc(S, sizeof(struct Test));
    /*
    int *arr = asM_newVector(S, 3, int);
    arr[2] = 2;
    arr = asM_free(S, arr);
    printf("\n\n%d", arr[2]);
    */
    
    as_String *str = asS_newString(S, "2333");

    as_Value v;
    setString(S, &v, str);
    
    as_Table *t = asT_newArray(S, 10);
    t->array[0] = v;
    debug_Table(t);

    asS_freeString(S, str);

    int order = 0x0001;
    OpCode code = OP_MOVE;
    printf("%d", code == getOpCode(order));


    return 0;
}














