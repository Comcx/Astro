

#ifndef A_STRING_H
#define A_STRING_H


#include "a_object.h"
#include "a_state.h"
#include <string.h>

unsigned int ELFhash(const char *str);
unsigned int asS_hash(as_State *S, const char *str);
int asS_equal(as_String *s, const char *str);

as_String *asS_newString(as_State *S, const char *str);
as_String *asS_freeString(as_State *S, as_String *str);




void debug_String(as_State *S, as_String *str);



#endif









