
#ifndef A_VM_H
#define A_VM_H


#include "astro.h"
#include "a_object.h"
#include "a_state.h"
#include "a_mem.h"
#include "a_code.h"
#include "a_debug.h"


int asV_objectEqual(const as_Value *v1, const as_Value *v2);
void asV_execute(as_State *S);

















#endif


