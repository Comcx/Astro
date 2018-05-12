

#include "a_table.h"
#include "a_mem.h"
#include "a_object.h"
#include "a_debug.h"


as_Table *asT_new(as_State *S, int flag_array, int flag_dict, int size_array, int size_dict) {
    
    as_Table *t = (as_Table*)asM_malloc(S, sizeof(as_Table));

    t->flag_array = flag_array;
    t->flag_dict = flag_dict;
    t->size_array = size_array;
    t->size_dict = size_dict;

    if (flag_array && flag_dict) {

        t->array = asM_newVector(S, size_array, as_Value);
        t->node = asM_newVector(S, size_dict, as_Node);
    } else if (flag_array) {

        t->array = asM_newVector(S, size_array, as_Value);
    } else if (flag_dict) {

        t->node = asM_newVector(S, size_dict, as_Node);
    } else {
        as_assert(0);
    }


    return t;
}


void debug_table(as_Table *t) {

    if (t->flag_array && t->flag_dict) {
    
        printf("\n-> array part:\n");


    } else if (t->flag_array) {

        
    
    } else if (t->flag_dict) {

        
    }


}





















