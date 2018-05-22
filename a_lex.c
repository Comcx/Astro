


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


static void lexError(LexState *ls, const char *msg, int token) {

    printf("\nError with %c, %s", cast_uchar(token), msg);
    exit(-1);

}
                                                                   

static void save(LexState *ls, int c) {

    as_Buffer *buff = ls->buffer;
    /*if buffer is not big enough?*/
    if (asI_bufferLen(buff) + 1 > asI_bufferSize(buff)) {

        size_t size_new;
        if (asI_bufferSize(buff) >= INT_MAX/2)
            lexError(ls, "buffer size too big!", 0);
        size_new = asI_bufferSize(buff) * 2;
        asI_resizeBuffer(ls->S, buff, size_new);
    }

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
//exit(-1);printf("\ninto numeral\n");
    as_Value obj;
    const char *expo = "Ee";
    int first = ls->current;
    as_assert(as_isDigit(cast_uchar(first)));
    
    save_and_next(ls);
    if (first == '0' && checkNext2(ls, "xX")) {

        expo = "Pp";
    }

    for (;;) {

        if (checkNext2(ls, expo))
            checkNext2(ls, "-+");
        if (as_isXDigit(ls->current))
            save_and_next(ls);
        else if (ls->current == '.')
            save_and_next(ls);
        else break;
    }
    save(ls, '\0');
    
    if (asO_str2num(asI_buffer(ls->buffer), &obj) == 0)
        lexError(ls, "wrong format of number", 0);

    if (typeIsInteger(&obj)) {
        
        seminfo->i = getValue(&obj).i;
        return TK_INT;
    } else {
        
        as_assert(typeIsNumber(&obj));
        //printf("\nflt!\n");
        seminfo->r = getValue(&obj).n;
        return TK_FLT;
    }

}


static int skip(LexState *ls) {

    int count = 0;
    int s = ls->current;



}



static int lex(LexState *ls, SemInfo *seminfo) {
//exit(-1);
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
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9': {
                return readNumeral(ls, seminfo);
            }
            case '=': {
                next(ls);
                if (checkNext1(ls, '='))    return TK_EQ;
                else return '=';
            }
            case '<': {
                next(ls);
                if (checkNext1(ls, '='))    return TK_LE;
                else if (checkNext1(ls, '<'))   return TK_SHL;
                else return '<';
            }
            case '>': {
                next(ls);
                if (checkNext1(ls, '='))    return TK_GE;
                else if (checkNext1(ls, '>'))   return TK_SHR;
                else return '>';
            }
            case '~': {
                next(ls);
                if (checkNext1(ls, '='))    return TK_NE;
                else return '~';
            }

            default: {
                return -1;
            }

        }

    }

    return 0;
}


int asX_next(LexState *ls) {

    ls->t.token = lex(ls, &ls->t.semInfo);

    //printf("%d", ls->t.token == TK_FLT);
    return ls->t.token;

}




