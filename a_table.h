
#ifndef A_TABLE_H
#define A_TABLE_H


#include "a_object.h"
#include "a_state.h"




#define getNode(t, i) (&(t)->node[i])
#define getNodeValue(n) (&(n)->val)
#define getKey(n) (cast(const as_Value*, (&(n->key.val))))
#define getNodeNext(n) ((n)->key.next)



as_Table *asT_new(as_State *S, int flag_array, int flag_dict, int size_array, int size_dict);

#define asT_newArray(S, size_array) asT_new(S, 1, 0, size_array, 0)
#define asT_newDict(S, size_dict) asT_new(S, 0, 1, 0, size_dict)
#define asT_newTable(S, size_array, size_dict) asT_new(S, 1, 1, size_array, size_dict)


as_Value *asT_set(as_State *S, as_Table *t, as_Value *key);

as_Table *asT_free(as_State *S, as_Table *t);

void debug_Table(as_Table *t);




#endif


















