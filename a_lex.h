

#ifndef A_LEX_H
#define A_LEX_H


#include "a_state.h"
#include "a_object.h"
#include "a_type.h"
#include "a_io.h"

/*
#define as_isNewLine(ls) ((ls)->current == '\n' || (ls)->current == '\r')

#define as_isAlpha(c) (isalpha(c) || (c) == '_')
#define as_isAlnum(c) (isalnum(c) || (c) == '_')
#define as_isDigit(c) (isdigit(c))
#define as_isSpace(c) (isspace(c))
#define as_isPrint(c) (isprint(c))
#define as_isXDigit(c) (isxdigit(c))
#define as_toLower(c) (tolower(c))
*/                                                                          



#define FIRST_RESERVED 257


typedef enum as_reserved {

    /* terminal symbols denoted by reserved words */
    TK_AND = FIRST_RESERVED, TK_BREAK,
    TK_DO, TK_ELSE, TK_ELSEIF, TK_END, TK_FALSE, TK_FOR, TK_FUNCTION,
    TK_GOTO, TK_IF, TK_IN, TK_LOCAL, TK_NIL, TK_NOT, TK_OR, TK_REPEAT,
    TK_RETURN, TK_THEN, TK_TRUE, TK_UNTIL, TK_WHILE,
    /* other terminal symbols */
    TK_IDIV, TK_CONCAT, TK_DOTS, TK_EQ, TK_GE, TK_LE, TK_NE,
    TK_SHL, TK_SHR,
    TK_DBCOLON, TK_EOS,
    TK_FLT, TK_INT, TK_NAME, TK_STRING

} as_reserved;

#define NUM_RESERVED (cast(int, TK_WHILE - FIRST_RESERVED + 1))




typedef struct SemInfo {

    as_Number r;
    as_Integer i;
    as_String *str;

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
    struct FuncState *fs;
    struct DynData *dyd;
    as_IO *io;
    as_Buffer *buffer;
    as_Table *table;    /*table to avoid collecting*/

    as_String *source;
    as_String *env;

} LexState;




void asX_setInput(as_State *S, LexState *ls, as_IO *io, as_String *source, int firstChar);
//void asX_next(as_State *S);

const char *asX_token2str(LexState *ls, int token);
int asX_next(LexState *ls);











#endif

