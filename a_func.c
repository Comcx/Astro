

#include "a_func.h"
#include "a_mem.h"
#include "a_gc.h"





Proto *asF_newProto(as_State *S) {

    GCObject *obj = asG_newObject(S, AS_TPROTO, sizeof(Proto));
    Proto *f = cast(Proto*, obj);

    f->k = NULL;
    f->size_k = 0;
    f->p = NULL;
    f->size_p = 0;
    f->code = NULL;
    f->size_code = 0;
    f->info_line = NULL;
    f->size_lineInfo = 0;
    f->upVal = NULL;
    f->size_UpVal = 0;
    f->num_param = 0;
    f->size_maxStack = 0;
    f->locVar = NULL;
    f->size_LocVar = 0;
    f->source = NULL;

    return f;
}





as_AClosure *asF_newAClosure(as_State *S, int n) {

    GCObject *obj = asG_newObject(S, AS_TACL, sizeof(as_AClosure)+sizeof(as_Value)*(n-1));
    as_AClosure *cl = cast(as_AClosure*, obj);

    cl->num_upval = cast(as_Byte, n);
    return cl;
}






























