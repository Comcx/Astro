

#ifndef A_UI_H
#define A_UI_H


#include "astro.h"
#include "a_mem.h"
#include "a_state.h"


/*Astro alloc default function*/
void *asU_alloc(void *ptr, size_t size_object, size_t size_new, size_t num);

/*Astro read default function*/
const char *asU_read(as_State *S, size_t size);



















#endif


