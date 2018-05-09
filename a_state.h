

#ifndef A_STATE_H
#define A_STATE_H



#include "astro.h"
#include "a_object.h"
#include "a_mem.h"


typedef struct Table_String {

    as_String **hash;
    int num_use;
    int size;

}Table_String;


void debug_strt(as_State *S);




typedef void *(*as_alloc)(void *ptr, size_t size_object, size_t size_new, size_t num);


typedef struct global_State {

    Table_String strt;  /*string table*/
    as_alloc fn_alloc;


}global_State;

                                           

typedef struct as_State {

    int size_stack;
    global_State *G;



}as_State;


#define G(S) ((S)->G)











as_State *asE_newState(void);
void asE_closeState(as_State *S);



#endif







