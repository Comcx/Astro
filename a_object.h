

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
#define ctb(t) setCollectable(t)




typedef struct GCObject GCObject;

#define GCHeader GCObject *next; as_Byte type; as_Byte marked



/*
** Astro Common Value
 */

typedef struct as_Value {

    int type;

    union {
        
        GCObject *gc;
        as_Integer b;
        as_Integer i;
        as_Number n;
        void *p;

    }val;


}as_Value;


#define getValue(o) ((o)->val)
#define getTypeRaw(o) ((o)->type)
#define removeVar(x) ((x) & 0x0F)
#define getTypeWithVar(o) (getTypeRaw(o) & 0x3F)
#define getTypeNoVar(o) (removeVar(getTypeRaw(o)))

#define typeIsInteger(o) (getTypeWithVar(o) == AS_TNUMINT)
#define typeIsNumber(o) (getTypeWithVar(o) == AS_TNUMBER)
#define typeIsBoolean(o) (getTypeNoVar(o) == AS_TBOOLEAN)
#define typeIsString(o) (getTypeNoVar(o) == AS_TSTRING)

#define setType(o, t) ((o)->type = (t))
#define setNumber(o, x) \
    {as_Value *o_ = (o); getValue(o_).n = x; setType(o_, AS_TNUMBER);}
#define setInteger(o, integer) \
    {as_Value *o_ = (o); getValue(o_).i = integer; setType(o_, AS_TNUMINT);}

#define setBoolean(o, x) \
    {as_Value *o_ = (o); getValue(o_).b = x; setType(o_, AS_TBOOLEAN);}

#define setGC(S, o, g) \
    {as_Value *o_ = o; GCObject *g_ = g; \
     getValue(o_).gc = g_; setType(o_, ctb(g_->type));}

#define setString(S, o, s) \
    {as_Value *o_ = o; as_String *s_ = s; \
     getValue(o_).gc = cast(GCObject*, s_); setType(o_, AS_TSTRING);}



#define setObj(S, obj1, obj2) \
    {as_Value *o = (obj1); *o = *(obj2); \
     (void)S; }



typedef as_Value* StkId;


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
    //int flag_string;/*used as pure string?*/
    

    as_Value *array;/*array ptr*/
    as_Node *node;  /*dict ptr*/
    //char *str;      /*string ptr*/

    GCObject *gclist;
    as_Unsigned size_array; /*array size*/
    as_Unsigned size_dict;  /*dict key size*/

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

    //as_Table str;    

}as_String;



#define getstr(t) ((char*)(t) + sizeof(as_String))



/*
** Astro special objects 
 */


/*local variable*/

typedef struct LocVar{

    as_String *name;
    int p_start;
    int p_end;

}LocVar;


typedef struct UpValDesc {

    as_String *name;
    as_Byte inStack;
    as_Byte id;

} UpValDesc;




/*Proto type(function proto info)*/

typedef struct Proto{

    GCHeader;
    as_Byte num_params;     /*number of parameters*/
    as_Byte size_maxStack;  /*max size of stack*/
    int size_k;             /*size of consts*/
    int size_UpVal;         /*size of upvals*/
    int size_LocVar;        /*size of local vars*/
    int size_code;
    int size_lineInfo;

    Instruction *code;      /*codes in proto*/
    struct Proto **p;       /*functions defined in*/
    as_Value *k;            /*constants used by the function*/
    LocVar *locVar;         /*local vars*/
    UpValDesc *upVal;       /*upvalues*/

    int *info_line;          /*line info for debug*/

    GCObject *gclist;

}Proto;





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
    Proto *p;
    

}as_AClosure;


typedef union as_Closure {

    as_CClosure c;
    as_AClosure a;

}as_Closure;






/*
** Astro GCObject -- objects that use GC System
 */

struct GCObject {

    GCHeader;
    union {
        as_String s;
        as_Closure cl;
        as_Table t;
    }val;

};




/*Functions for objects*/
void printObject(as_Value *v);

int asO_getHexValue(int c);
size_t asO_str2num(const char *str, as_Value *obj);





#endif















