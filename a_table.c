

#include "a_table.h"
#include "a_mem.h"
#include "a_object.h"
#include "a_string.h"
#include "a_debug.h"


#define hashPow2(t, n) (getNode(t, hashMod(n, size_node(t))))
#define hashInt(t, i) hashPow2(t, i)
#define hashNumber(t, n) (getNode(t, ((n) % ((size_node(t)-1) | 1))))
#define hashString(t, s) hashPow2(t, s)
#define hashBool(t, b) hashPow2(t, b)
#define hashPointer(t, p) hashNumber(t, cast(unsigned int, p))



as_Table *asT_new(as_State *S, int flag_array, int flag_dict, int size_array, int size_dict) {
    
    as_Table *t = (as_Table*)asM_malloc(S, sizeof(as_Table));

    t->flag_array = flag_array;
    t->flag_dict = flag_dict;
    t->size_array = size_array;
    t->size_dict = size_dict;

    if (flag_array && flag_dict) {

        t->array = asM_newVector(S, size_array, as_Value);
        t->node = asM_newVector(S, size_dict, as_Node);
    } else if (flag_array) {

        t->array = asM_newVector(S, size_array, as_Value);
    } else if (flag_dict) {

        t->node = asM_newVector(S, size_dict, as_Node);
    } else {
        as_assert(0);
    }


    return t;
}






static as_Node *getBarrel(const as_Table *t, const as_Value *key) {

    switch (getTypeWithVar(key)) {
    
        case AS_TNUMINT:
            return hashInt(t, intValue(key));
        case AS_TNUMFLT:
            return hashNumber(t, (int)fltValue(key));
        case AS_TSHTSTR:
            return hashString(t, ELFhash(strValue(key)));
        case AS_TLNGSTR:
            printf("long str function of getBarrel not finished!");
            exit(-1);
            break;  /*unfinsihed!*/
        case AS_TBOOLEAN:
            return hashBool(t, boolValue(key));
        case AS_TACF:
            return hashPointer(t, cfValue(key));
        default: {
            
            return hashPointer(t, gcValue(key));
        }
    }

}



const as_Value *asT_getInt(as_Table *t, as_Integer key) {

    if (t->flag_array && cast(as_Unsigned, key) < t->size_array) {
    
        return &t->array[key];  /*found in array part*/
    } else {    /*element is in dict?*/
    
        if (!t->flag_dict)  /*no dict?*/
            return as_Nil;
        /*search in node(dict)*/

    }

}


const as_Value *asT_getShortStr(as_Table *t, const char *key) {



}


const as_Value *asT_getGeneric(as_Table *t, as_Value *key) {



}


const as_Value *asT_get(as_Table *t, as_Value *key) {

    switch (getTypeWithVar(key)) {
    
        case AS_TNUMINT: return asT_getInt(t, intValue(key));
        case AS_TNUMFLT: {
            printf("Table index can not be float!\n");
            exit(-1);
        }
        case AS_TSHTSTR: return asT_getShortStr(t, strValue(key));
        case AS_TLNGSTR: return as_Nil; /*unfinished!*/
        case AS_TNIL:   return as_Nil;
        default: {
            return asT_getGeneric(t, key);
        }
    }

}



as_Value *asT_set(as_State *S, as_Table *t, as_Value *key) {

    const as_Value *ans = asT_get(t, key);
    if (ans != as_Nil ) {
        return cast(as_Value*, ans);
    }
    else return cast(as_Value*, as_Nil);
}



void debug_Table(as_Table *t) {

    if (t->flag_array && t->flag_dict) {
    
        printf("\n-> array part:\n");
        int i = 0;
        for (; i < t->size_array; i++) {

            printObject(t->array + i);
            printf("\n");
        }

        printf("\n-> dict part:\n");
        for (i = 0; i < t->size_dict; i++) {

            printf("under working...");
        }


    } else if (t->flag_array) {

        printf("\n-> array:\n");
        int i = 0;
        for (; i < t->size_array; i++) {

            printObject(t->array + i);
            printf("\n");
        }
    
    } else if (t->flag_dict) {

        
    }


}





















