

#ifndef A_LEX_H
#define A_LEX_H


#include "a_state.h"
#include "a_object.h"
#include "a_io.h"


typedef struct SemInfo {

    as_Number r;
    as_Integer i;
    as_String str;

} SemInfo;


typedef struct Token {

    int token;
    SemInfo semInfo;

} Token;



typedef struct LexState {

    int current;
    int num_line;
    int lastLine;

    Token t;
    Token t_pre;

    as_State *S;
    as_IO io;
    as_Buffer buffer;

    as_String *source;


} LexState;



















#endif

