

#ifndef A_FUNC_H
#define A_FUNC_H

#include "a_object.h"




struct UpVal {

    as_Value *v;
    size_t count_ref;
    union {
        struct {
            struct UpVal *next;
            int touched;
        } open;
        as_Value value;
    } u;

};







Proto *asF_newProto(as_State *S);
as_AClosure *asF_newAClosure(as_State *S, int n);   /*n is not used right now*/










#endif




