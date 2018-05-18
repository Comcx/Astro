

#include "a_lex.h"


#define next(ls) ((ls)->current = as_getc((ls)->io))



static const char *asX_tokens[] = {

    "and", "break", "do", "else", "elseif",
    "end", "false", "for", "function", "goto", "if",
    "in", "local", "nil", "not", "or", "repeat",
    "return", "then", "true", "until", "while",
    "//", "..", "...", "==", ">=", "<=", "~=",
    "<<", ">>", "::", "<eof>",
    "<number>", "<integer>", "<name>", "<string>"

};


void asX_setInput(as_State *S, LexState *ls, as_IO *io, as_String *source, int firstChar) {

    ls->t.token = 0;
    ls->S = S;
    ls->current = firstChar;

    ls->io = io;
    ls->num_line = 1;
    ls->lastLine = 1;
    ls->source = source;

}





















