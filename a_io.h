

#ifndef A_IO_H
#define A_IO_H


#include "astro.h"
#include "a_mem.h"
#include "a_state.h"


#define EOI -1



typedef struct as_IO as_IO;

#define as_getc(I) ( ((I)->n--)>0 ? cast_uchar(*(I)->p++) : asI_fill(I) )


typedef struct as_Buffer {

    char *buffer;
    size_t n;
    size_t size;

} as_Buffer;





struct as_IO {

    size_t n;
    const char *p;
    as_Reader reader;
    void *data;
    as_State *S;

};




void asI_init(as_State *S, as_IO *io, as_Reader reader);
size_t asI_read(as_IO *io, void *b, size_t n);
int asI_fill(as_IO *io);





#endif




