


#include "a_string.h"
#include "a_mem.h"


as_String *asS_newString(as_State *S, char *str) {

    as_String *ans = (as_String*)asM_malloc(S, sizeof(as_String));
    
    ans->reserved = 0;
    ans->hash = str[0];
    ans->hnext = NULL;
    ans->len = 2;
    
    return ans;
}



void debug_String(as_State *S, as_String *str) {

    printf("reserved: %d\nhash: %d\nhnext: %d\nlen: %d\n", str->reserved, str->hash, str->hnext, str->len);

}
















