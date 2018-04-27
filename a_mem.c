

#include "a_mem.h"



void *asM_alloc(void *ptr, size_t size_object, size_t size_new, size_t num) {

    if (size_object != 0) {
        
        ptr = calloc(num, size_object + size_new);
        return ptr;

    } else {
        
        if (size_new == 0) {

            free(ptr); 
            return NULL;
        } else {

            return realloc(ptr, size_object + size_new);    
        }
    }


}


//as_State *asM_malloc()


















