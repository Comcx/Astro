
#ifndef A_TABLE_H
#define A_TABLE_H


#include "a_object.h"
#include "a_state.h"


as_Table *asT_newBox(as_State *S, int flag_array, int flag_dict, int size_array, int size_dict);

#define asT_newArray(S, size_array) asT_newBox(S, 1, 0, size_array, 0)
#define asT_newDict(sS, ize_dict) asT_newBox(S, 0, 1, 0, size_dict)
#define asT_newTable(S, size_array, size_dict) asT_newBox(S, 1, 1, size_array, size_dict)




#endif


















