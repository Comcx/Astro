

#include "astro.h"
#include "a_io.h"
#include "a_ui.h"
#include "a_state.h"


int asI_fill(as_IO *io) {

    as_State *S = io->S;
    const char *buffer;
    size_t size;

    buffer = io->reader(S, &size);

    if (buffer == NULL || size == 0) {

        return -1;
    }
    io->n = size-1;
    io->p = buffer;

    return cast_uchar(*(io->p++));
}

























