


#include "a_lex.h"
#include "a_debug.h"
#include "a_object.h"
#include <limits.h>



#define next(ls) ((ls)->current = as_getc((ls)->io))
#define save_and_next(ls) (save(ls, ls->current), next(ls))


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


static void save(LexState *ls, int c) {

    as_Buffer *buff = ls->buffer;
    /*if buffer is not big enough?*/


    buff->buffer[asI_bufferLen(buff)++] = cast(char, c);
}


const char *asX_token2str(LexState *ls, int token) {

    if (token < FIRST_RESERVED) {   /*single byte char?*/

        as_assert(token == cast_uchar(token));
        return "underwork...";
    } else {

        const char *s = asX_tokens[token - FIRST_RESERVED];
        //note! we have not deal with format str or token > TK_EOS!
        return s;
    }
}



static void incLineNumber(LexState *ls) {

    int old = ls->current;
    as_assert(as_isNewLine(ls));
    next(ls);

    if (++ls->num_line > INT_MAX) {

        printf("too many lines!?");
    }

}



/***************************************************************************
** Main Lexer!
 */


static int checkNext1(LexState *ls, int c) {

    if (ls->current == c) {

        next(ls);
        return 1;
    }
    return 0;
}


static int checkNext2(LexState *ls, const char *set) {

    as_assert(set[2] == '\0');
    if (ls->current == set[0] || ls->current == set[1]) {

        save_and_next(ls);
        return 1;
    }
    return 0;
}



/*Astro Numbers*/
/*
** Function to read as_Numbers
 */

static int readNumeral(LexState *ls, SemInfo *seminfo) {

    


}


static int skip(LexState *ls) {

    int count = 0;
    int s = ls->current;



}



static int lex(LexState *ls, SemInfo *seminfo) {

    asI_resetBuffer(ls->buffer);
    while (1) {

        switch (ls->current) {

            case '\n': case '\r': { /*end of line*/
                incLineNumber(ls);
                break;
            }
            case ' ': case '\f': case '\t': case '\v': {    /*spaces*/
                next(ls);
                break;
            }
            case '-': { /*'-' or '--'comment?*/
                next(ls);
                if (ls->current != '-') return '-';

                next(ls);
                if (ls->current == '"') { /*long comment*/

                }
            }

        }

    }

    return 0;
}







