

#include "a_vm.h"
#include "a_debug.h"
#include "a_string.h"
#include <math.h>









int asV_objectEqual(as_Value *v1, as_Value *v2) {

    if (getTypeWithVar(v1) != getTypeWithVar(v2)) {
        if(getTypeNoVar(v1) != getTypeNoVar(v2) || getTypeNoVar(v1) != AS_TNUMBER)
            return 0;
        else {
            as_Integer i1, i2;
            switch (getTypeWithVar(v1)) {   /*We temporarily compare int and float by converting both to int*/

                case AS_TNUMINT: {
                    as_assert(getTypeWithVar(v2) == AS_TNUMFLT);
                    i1 = getValue(v1).i;
                    i2 = (int)(getValue(v2).n);
                    break;
                }
                case AS_TNUMFLT: {
                    as_assert(getTypeWithVar(v2) == AS_TNUMINT);
                    i1 = (int)(getValue(v1).n);
                    i2 = getValue(v2).i;
                    break;
                }
                default:
                    as_assert(0);
            }
        }
    }

    /*type tag is equal!*/
    switch (getTypeWithVar(v1)) {
    
        case AS_TNIL:       return 0;
        case AS_TNUMINT:    return getValue(v1).i == getValue(v2).i;
        case AS_TNUMFLT:    return getValue(v1).n == getValue(v2).n;
        case AS_TBOOLEAN:   return getValue(v1).b == getValue(v2).b;
        case AS_TACL:       return 0;   /*unfinished!*/
        case AS_TSHTSTR:    return asS_equal(cast(as_String*, getValue(v1).gc), strValue(v2));
        case AS_TLNGSTR:    return 0;   /*unfinished!*/
        case AS_TTABLE:     return 0;   /*unfinished!*/

        default:    return 0;   /*unfinished!*/
    
    }


    return 0;
}


void asV_execute(as_State *S) {


}























