
#ifndef A_TYPE_H
#define A_TYPE_H


#include <ctype.h>

#define as_isNewLine(ls) ((ls)->current == '\n' || (ls)->current == '\r')

#define as_isSpace(c) (isspace(c))
#define as_isAlpha(c) (isalpha(c) || (c) == '_')
#define as_isAlnum(c) (isalnum(c) || (c) == '_')
#define as_isDigit(c) (isdigit(c))
#define as_isSpace(c) (isspace(c))
#define as_isPrint(c) (isprint(c))
#define as_isXDigit(c) (isxdigit(c))
#define as_toLower(c) (tolower(c))
                                                                          




















#endif

