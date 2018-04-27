
#include "astro.h"




typedef struct GCObject GCObject;

#define GCHeader GCObject *next; as_Byte t; as_Byte marked



/*
** Astro Common Value
 */

typedef struct as_Value {

    int type;

    union {
        
        GCObject *gc;
        as_Integer b;
        as_Number n;
        void *p;

    }val;


}as_Value;






/*
** Astro String Object
 */

typedef union as_String {

    //align?
    struct {

        GCHeader;
        as_Byte reservrd;
        unsigned int hash;
        size_t len;

    }header;


}as_String;




























