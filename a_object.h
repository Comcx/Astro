
#include "astro.h"




typedef union GCObject GCObject;

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




typedef struct Key {

    as_Value val;
    struct Node *next;

}Key;

typedef struct Node {

    as_Value val;
    Key key;

}Node;

typedef struct as_Table {

    GCHeader;

    int flag_array;
    int flag_dict;
    int flag_string;

    as_Value *array;
    Node *node;

    GCObject *gclist;
    as_Unsigned size_array;
    as_Unsigned size_node;

}as_Table;





union GDObject {

    GCHeader;
    as_String s;
    as_Closure cl;
    as_Table t;

};





























