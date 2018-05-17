

#ifndef A_STATE_H
#define A_STATE_H



#include "astro.h"
#include "a_conf.h"
#include "a_object.h"
#include "a_mem.h"


typedef struct Table_String {

    as_String **hash;
    int num_use;
    int size;

}Table_String;


void debug_strt(as_State *S);



/*Information about a function call*/

typedef struct CallInfo {

    StkId func;
    StkId top;
    struct CallInfo *next, *prev;

    StkId base;
    
    int num_result;
    unsigned short status;

} CallInfo;





//typedef void *(*as_Alloc)(void *ptr, size_t size_object, size_t size_new, size_t num);


/*Global state especially for GC*/
typedef struct global_State {

    Table_String strt;  /*string table*/
    as_Alloc fn_alloc;


}global_State;

                                           
/*Main Astro state, used every where*/

typedef struct as_State {
    
    Instruction *oldPc;
    StkId base;
    StkId top;
    StkId stack;
    
    CallInfo ci;
    CallInfo *callList;

    int size_stack;
    global_State *G;

    GCObject *gclist;


}as_State;


#define G(S) ((S)->G)











as_State *asE_newState(void);
as_State *asE_closeState(as_State *S);



#endif







