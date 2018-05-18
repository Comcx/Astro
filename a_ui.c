

#include "a_ui.h"



void *asU_alloc(void *ptr, size_t size_object, size_t size_new, size_t num) {

    if (size_object != 0) {
        
        ptr = calloc(num, size_object + size_new);
        return ptr;

    } else {
        
        if (size_new == 0) {

            free(ptr); 
            return NULL;
        } else {

            return realloc(ptr, size_new);    
        }
    }
}







/*
** Astro default file reading settings, you can change it if needed
 *
 */






const char *asU_read(as_State *S, size_t size) {

    


}



















