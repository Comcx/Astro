

#include "a_object.h"
#include "a_state.h"


as_Table *asT_newBox(int flag_array, int flag_dict, int size_array, int size_dict);

#define asT_newArray(size_array) asT_newBox(1, 0, size_array, 0)
#define asT_newDict(size_dict) asT_newBox(0, 1, 0, size_dict)
#define asT_newTable(size_array, size_dict) asT_newBox(1, 1, size_array, size_dict)























