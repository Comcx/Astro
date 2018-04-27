

#include "astro.h"
#include "a_object.h"



typedef struct Table_String {

    as_String **hash;
    int num_use;
    int size;

}Table_String;







typedef void (*as_alloc)(void *ptr, size_t size_object, size_t size_new);


typedef struct global_State {

    Table_String strt;  /*string table*/
    as_alloc fn_alloc;


}global_State;

                                           

typedef struct as_State {

    int size_stack;
    global_State *G;



}as_State;


#define G(S) (S->G)











as_State *asE_newState(void);












