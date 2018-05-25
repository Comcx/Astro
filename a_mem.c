

#include "a_mem.h"
#include "a_debug.h"




void *asM_reallocVector(as_State *S, void *ptr, size_t size_new, size_t limit) {

    if (size_new > limit) {
        
        as_assert(0);
    }
    ptr = asM_realloc(S, ptr, size_new);
    return ptr;

}


















