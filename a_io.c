

#include "astro.h"
#include "a_mem.h"
#include "a_io.h"
#include "a_ui.h"
#include "a_state.h"


void asI_init(as_State *S, as_IO *io, as_Reader reader) {

    io->S = S;
    io->reader = reader;
    io->n = 0;
    io->p = NULL;

}


int asI_fill(as_IO *io) {

    as_State *S = io->S;
    const char *buffer;
    size_t size;

    buffer = io->reader(S, &size);

    if (buffer == NULL || size == 0) {

        return EOI;
    }
    io->n = size - 1;
    io->p = buffer;

    return cast_uchar(*(io->p++));
}


size_t asI_read(as_IO *io, void *b, size_t n) {

    while (n) {

        size_t m;
        if (io->n == 0) {

            if (asI_fill(io) == EOI)
                return n;
            else {

                io->n++;
                io->p--;
            }
        }
        m = (n <= io->n) ? n : io->n;
        memcpy(b, io->p, m);
        io->n -= m;
        io->p += m;
        b = (char*)b + m;
        n -= m;
    }

    return 0;
}






















