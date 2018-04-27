

/*
** a_mem.h, Astro memory management
 * Comcx, 2018
 *
 */

#ifndef A_MEM_H
#define A_MEM_H


#include <stdlib.h>

#include "astro.h"
#include "a_state.h"


void *asM_alloc(void *ptr, size_t size_object, size_t size_new);

void *asM_malloc(as_State *S, size_t size);
void *asM_realloc(as_State *S, void *ptr, size_t size_new);
void asM_free(as_State *S, void *ptr);

#define asM_newVector(S, size, t) \
    cast(t *, asM_malloc(S, size))



#endif

















