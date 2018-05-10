

#include "a_table.h"
#include "a_mem.h"
#include "a_object.h"


as_Table *newBox(as_State *S, int flag_array, int flag_dict, int size_array, int size_dict) {
    
    as_Table *t = asM_malloc();

    if (flag_array && flag_dict) {

                 
    } else if (flag_array) {


    } else if (flag_dict) {


    } else {

    }


    return t;
}
























