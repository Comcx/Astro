

#include "astro.h"


typedef void (*fn_alloc)(void *ptr, size_t size_object, size_t size_new);


typedef struct as_State {

    int size_stack;
    global_State *G;

    fn_alloc fnM_alloc;


}as_State;





typedef struct global_State {

    


}global_State;

























