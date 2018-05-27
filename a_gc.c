


#include "a_gc.h"


GCObject *asG_newObject(as_State *S, int type, size_t sz) {

    GCObject *obj = cast(GCObject*, asM_malloc(S, sz));
    obj->type = type;
    obj->marked = 0;    /*this is unfinished!*/

    return obj;
}

























