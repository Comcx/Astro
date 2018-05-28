

#include "a_io.h"
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
/*
typedef struct FileLoader {

    int n;
    FILE *file;
    char buffer[SIZE_BUFFER];


} FileLoader;
                                
*/


const char *asU_read(as_State *S, size_t *size, void *ud) {

    FileLoader *fl = (FileLoader *)ud;
    (void)S;
    
    if (fl->n > 0) {

        *size = fl->n;
        fl->n = 0;
    } else {

        if (feof(fl->file)) return NULL;
        *size = fread(fl->buffer, 1, sizeof(fl->buffer), fl->file);
    }

    return fl->buffer;
}



















