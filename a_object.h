

#ifndef A_OBJECT_H
#define A_OBJECT_H




#include "astro.h"

#include <stddef.h>



/*
** Some extra type definitions and variants
 *
 * 6                5-4         0-3
 * collectable      variants    basic type
 *
 */

#define AS_TPROTO AS_NUMTAGS
#define AS_TDEADKEY (AS_NUMTAGS + 1)

#define AS_TACL (AS_TFUNCTION | (0 << 4)) 
#define AS_TACF (AS_TFUNCTION | (1 << 4))
#define AS_TCCL (AS_TFUNCTION | (2 << 4))

#define AS_TSHTSTR (AS_TSTRING | (0 << 4))
#define AS_TLNGSTR (AS_TSTRING | (1 << 4))

#define AS_TMUNFLT (AS_TNUMBER | (0 << 4))
#define AS_TNUMINT (AS_TNUMBER | (1 << 4))



/*
** Tools for types and variants
 */

#define BIT_ISCOLLECTABLE (1 << 6)
#define setCollectable(t) ((t) | BIT_ISCOLLECTABLE)





typedef union GCObject GCObject;

#define GCHeader GCObject *next; as_Byte type; as_Byte marked



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


#define getValue(o) ((o)->val)
#define getTypeRaw(o) ((o)->type)
#define removeVar(x) ((x) & 0x0F)
#define getTypeWithVar(o) (getTypeRaw(o) & 0x3F)
#define getTypeNoVar(o) (removeVar(getTypeRaw(o)))



/*
** Astro Table Container
 */


typedef struct as_Key {

    as_Value val;
    struct as_Node *next;

}as_Key;

typedef struct as_Node {

    as_Value val;
    as_Key key;

}as_Node;

typedef struct as_Table {

    GCHeader;

    int flag_array; /*used as array?*/
    int flag_dict;  /*used as dictionary*/
    int flag_string;/*used as pure string?*/
    int flag_tabel;

    as_Value *array;/*array ptr*/
    as_Node *node;  /*dict ptr*/

    GCObject *gclist;
    as_Unsigned size_array; /*array size*/
    as_Unsigned size_Node;  /*dict key size*/

}as_Table;
                               




/*
** Astro String Object
 */

typedef struct as_String {

    //align?
    //struct {

        GCHeader;
        as_Byte reserved;
        unsigned int hash;
        struct as_String *hnext;
        size_t len;

    //}header;

    as_Table str;    

}as_String;




/*
** Astro Closure Object
 */

#define ClosureHeader GCHeader; as_Byte num_upvalue; GCObject *gclist


typedef struct as_CClosure {

    ClosureHeader;
    as_Value upvalue[1];


}as_CClosure;


typedef struct as_AClosure {

    ClosureHeader;
    


}as_AClosure;


typedef union as_Closure {

    as_CClosure c;
    as_AClosure a;

}as_Closure;






/*
** Astro GCObject -- objects that use GC System
 */

union GCObject {

    GCHeader;
    as_String s;
    as_Closure cl;
    as_Table t;

};













#endif















