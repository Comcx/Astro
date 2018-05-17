

#ifndef A_IO_H
#define A_IO_H


#include "astro.h"
#include "a_mem.h"
#include "a_state.h"


typedef struct as_IO as_IO;

#define as_getc(I) ( ((I)->n--)>0 ? cast_uchar(*(I)->p++) : asI_fill(I) )


typedef struct as_Buffer {

    char *buffer;
    size_t n;
    size_t size;

} as_Buffer;





struct as_IO {

    size_t num_left;
    const char *p;
    as_Reader reader;
    void *data;
    as_State S;

};








#endif




