

/*
** a_mem.h, Astro memory management
 * Comcx, 2018
 *
 */

#ifndef A_MEM_H
#define A_MEM_H


#include <stdlib.h>
#include <string.h>

#include "astro.h"
#include "a_state.h"
//#include "a_ui.h"


//void *asM_alloc(void *ptr, size_t size_object, size_t size_new, size_t num);

#define asM_malloc(S, size) ((S)->G->fn_alloc(NULL, size, 0, 1))
#define asM_realloc(S, ptr, size_new) ((S)->G->fn_alloc(ptr, 0, size_new, 0))
#define asM_free(S, ptr) ((S)->G->fn_alloc(ptr, 0, 0, 0))

#define asM_newVector(S, num, t) \
    cast(t *, ((S)->G->fn_alloc(NULL, sizeof(t), 0, num)))



#endif

















