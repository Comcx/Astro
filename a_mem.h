

/*
** a_mem.h, Astro memory management
 * Comcx, 2018
 *
 */


#include <stdlib.h>

#include "astro.h"



void *asM_malloc(as_State *S, size_t size);
void *asM_realloc(as_State *S, void *ptr, size_t size_new);
void asM_free(as_State *S, void *ptr);

#define asM_newVector(S, size, t) \
    cast(t *, asM_malloc(S, size))





















