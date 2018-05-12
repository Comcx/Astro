

#include "a_object.h"
#include "a_debug.h"


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

























