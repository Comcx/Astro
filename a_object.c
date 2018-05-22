

#include "a_object.h"
#include "a_type.h"
#include "a_debug.h"
#include <stdlib.h>


void printObject(as_Value *v) {

    switch (v->type) {

        case AS_TNUMBER:
            printf("%lf", v->val.n);
            break;

        case AS_TBOOLEAN:
            printf("%d", v->val.b);
            break;

        case AS_TSTRING:
            printf("%s", getstr(cast(as_String*, v->val.gc)));
            break;

        default:
            printf("unknown type?");

    }

}



static int isNeg(const char **str) {

    if (**str == '-') {(*str)++; return 1;}
    else if (**str == '+') (*str)++;
    return 0;
}

int asO_getHexValue(int c) {

    if (as_isDigit(cast_uchar(c)))  return c - '0';
    else return as_toLower(cast_uchar(c)) - 'a' + 10;

}


static const char *str2int(const char *str, as_Integer *i) {

    as_Unsigned a = 0;
    int empty = 1;
    int neg;

    while (as_isSpace(cast_uchar(*str)))    str++;
    neg = isNeg(&str);
    if (str[0] == '0' &&
        str[1] == 'x' || str[1] == 'X') {   /*hex number*/

        str += 2;
        for (; as_isXDigit(cast_uchar(*str)); str++) {

            a = a * 16 + asO_getHexValue(*str);
            empty = 0;
        }
    } else {    /*decimal number*/

        for (; as_isDigit(cast_uchar(*str)); str++) {

            int d = *str - '0';
            if (d >= 10) {

                return NULL;
            }
            a = a * 10 + d;
            empty = 0;
        }
    }

    while (as_isSpace(cast_uchar(*str)))    str++;
    if (empty || *str != '\0')  return NULL;
    else {

        *i = cast(as_Integer, (neg? -a : a));
        return str;
    }

}


static const char *str2flt(const char *str, as_Number *n) {

    as_Number a;
    char *ptr_end;
    a = cast(as_Number, strtod(str, &ptr_end));

    if (*ptr_end != '\0') {

        return NULL;
    } else {

        *n = a;
        return ptr_end;
    }

}


size_t asO_str2num(const char *str, as_Value *obj) {

    as_Number n;
    as_Integer i;
    const char *e;

    if ((e = str2int(str, &i)) != NULL) {

        setInteger(obj, i);    
    } else if ((e = str2flt(str, &n)) != NULL) {

        setNumber(obj, n);
    } else return 0;

    return e - str + 1;
}




















