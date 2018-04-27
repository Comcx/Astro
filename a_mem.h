

/*
** a_mem.h, Astro memory management
 * Comcx, 2018
 *
 */


#include <stdlib.h>

#include "astro.h"



void *as_malloc(as_State *S, size_t size);
void *as_realloc(as_State *S, void *ptr, size_t size_new);
void as_free(as_State *S, void *ptr);

void *as_newVector(as_State *S, size_t size, );





















