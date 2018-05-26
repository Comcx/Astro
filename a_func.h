

#ifndef A_FUNC_H
#define A_FUNC_H

#include "a_object.h"




typedef struct UpVal {

    as_Value *v;
    size_t count_ref;
    union {
        struct {
            struct UpVal *next;
            int touched;
        } open;
        as_Value value;
    } u;

} UpVal;


















#endif




