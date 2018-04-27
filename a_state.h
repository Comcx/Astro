

#include "astro.h"




typedef struct Table_String {

    as_String **hash;
    int num_use;
    int size;

}Table_String;







typedef void (*as_alloc)(void *ptr, size_t size_object, size_t size_new);


typedef struct as_State {

    int size_stack;
    global_State *G;

    as_alloc fn_alloc;


}as_State;





typedef struct global_State {

    


}global_State;

























