
#include <math.h>
#include "a_table.h"
#include "a_mem.h"
#include "a_object.h"
#include "a_string.h"
#include "a_vm.h"
#include "a_debug.h"





#define hashPow2(t, n) (getNode(t, hashMod(n, size_node(t))))
#define hashInt(t, i) hashPow2(t, i)
#define hashNumber(t, n) (getNode(t, ((n) % ((size_node(t)-1) | 1))))
#define hashString(t, s) hashPow2(t, s)
#define hashBool(t, b) hashPow2(t, b)
#define hashPointer(t, p) hashNumber(t, pointer2uint(p))


static void tableError(as_State *S, as_Table *t, const char *msg) {

    printf("table error! %s\n", msg);
    exit(-1);
}




as_Table *asT_new(as_State *S, int flag_array, int flag_dict, int size_array, int size_dict) {
    
    as_Table *t = (as_Table*)asM_malloc(S, sizeof(as_Table));

    t->flag_array = flag_array;
    t->flag_dict = flag_dict;
    t->size_array = size_array;
    t->size_dict = size_dict;

    if (flag_array) {

        t->array = asM_newVector(S, size_array, as_Value);
    } 
    if (flag_dict) {

        t->node = asM_newVector(S, pow2(size_dict), as_Node);
        int i = 0;
        for (; i < size_dict; i++) {
            setNodeKey(S, &(t->node[i].key), as_Nil);
            t->node[i].key.next = 0;
        }
    }

    t->lastFree = size_dict > 0 ? t->node + pow2(size_dict) - 1 : NULL;
//printf("sixe: %x\n", t->lastFree);
    return t;
}



as_Table *asT_free(as_State *S, as_Table *t) {

    if (t != NULL) {
        
        if (t->size_array) asM_free(S, t->array);
        if (t->flag_dict) asM_free(S, t->node);
    }
    
    return asM_free(S, t);
}



/*
** get main position(barrel) of node in dict
*/

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



static as_Node *getFreeBarrel(as_Table *t) {

    if (t->lastFree != NULL) {

        while (t->lastFree > t->node) {
            t->lastFree--;
            //printf("\nlastFree change: %x\n", t->lastFree);
            if (typeIsNil(getKey(t->lastFree)))
                return t->lastFree;
        }
    }
    
    return NULL;
}




/*
** inserts a new key into a hash table; first, check whether key's main
** position is free. If not, check whether colliding node is in its main
** position or not: if it is not, move colliding node to an empty place and
** put new key in its main position; otherwise (colliding node is in its main
** position), new key goes to an empty position.
*/
as_Value *asT_newKey(as_State *S, as_Table *t, const as_Value *key) {

    if (typeIsNil(key)) tableError(S, t, "table index can not be nil.");
    else if (typeIsNumber(key)) {
        tableError(S, t, "table index can not be float.");
        /*unfinsihed!*/
    }

//printf("\nsii: %d\n", hashMod(ELFhash(key), size_node(t)));
    as_Node *n = getBarrel(t, key);
    if (!typeIsNil(getKey(n))) {    /*found node is not free*/
    
        as_Node *n_free = getFreeBarrel(t);
        if (n_free == NULL) {   /*node is full, need to grow table*/
            
            tableError(S, t, "table rehash function can not be used!");
            /*unfinished!*/
            n = getBarrel(t, key);
            n_free = getFreeBarrel(t);
        }
        as_Node *n_other = getBarrel(t, getKey(n));
        if (n_other != n) { /*colliding node is not in its barrel*/
        
            while (n_other + getNodeNext(n_other) != n) {   /*find pre-node*/
                n_other += getNodeNext(n_other);
            }
            getNodeNext(n_other) = cast(int, n_free - n_other);
            *n_free = *n;   /*copy that*/
            if (getNodeNext(n) != 0) {

                getNodeNext(n_free) += cast(int, n - n_free);
                getNodeNext(n) = 0; /*n is free now*/
            }
            setNil(getNodeValue(n));

        } else {    /*colliding node is in its barrel, move node to free spaces*/
            
            if (getNodeNext(n) != 0) {
                getNodeNext(n_free) = cast(int, (n+getNodeNext(n)) - n_free);
            }
            getNodeNext(n) = cast(int, n_free - n);
            n = n_free;
        }

    }
    
    /*found node is free now*/
    //n->key.val = *key;exit(-1);
    setNodeKey(S, &n->key, key);
    return getNodeValue(n);
}








/*
** search function for integers
*/
const as_Value *asT_getInt(as_Table *t, as_Integer key) {

    if (t->flag_array && cast(as_Unsigned, key) < t->size_array) {
    
        return &t->array[key];  /*found in array part*/
    } else {    /*element is in dict?*/
    
        if (!t->flag_dict)  /*no dict?*/
            return as_Nil;
        /*search in node(dict)*/
        as_Node *node = hashInt(t, key);
        for (;;) {  /*check if in somewhere in the chain*/
            if (typeIsInteger(getKey(node)) && intValue(getKey(node)) == key) {
                return getNodeValue(node);
            }
            int offset_next = getNodeNext(node);
            if (offset_next == 0) break;
            node += offset_next;
        }
    }
    
    return as_Nil;
}


/*
** search function for short strings
*/
const as_Value *asT_getShortStr(as_Table *t, const char *key) {
//printf("testt %d\n", t->size_dict); exit(-1);
    as_Node *n = hashString(t, ELFhash(key));
    for (;;) {
        
        const as_Value *k = getKey(n);
        if (typeIsString(k) && asS_equal(cast(as_String*, getValue(k).gc), key)) {
            return getNodeValue(n);
        }
        int offset = getNodeNext(n);
        if (offset == 0) break;
        n += offset;
    }
    
    return as_Nil;
}



/*
** "Generic" get version. (Not that generic: not valid for integers,
** which may be in array part, nor for floats with integral values.)
*/
const as_Value *asT_getGeneric(as_Table *t, as_Value *key) {

    as_Node *n = getBarrel(t, key);
    for (;;) {    /*search in chain*/
    
        if (asV_objectEqual(getKey(n), key)) {
            return getNodeValue(n);
        }
        int offset = getNodeNext(n);
        if (offset == 0) break;
        n += offset;
    }
    
    return as_Nil;
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
    if (ans != as_Nil ) {   /*already exit*/
        return cast(as_Value*, ans);
    }
    else return asT_newKey(S, t, key);
}



void debug_Table(as_Table *t) {

    if (t->flag_array) {
    
        printf("\n-> array part:\n");
        int i = 0;
        for (; i < t->size_array; i++) {

            printObject(t->array + i);
            printf("\n");
        }
    
    }

    if (t->flag_dict) {
        
        int i;
        printf("\n-> dict part:\n");
        //printf("lastFree: %x\n", t->lastFree);
        for (i = 0; i < pow2(t->size_dict); i++) {

            printObject(&t->node[i].val);
            printf("\n");
        }
    }

}





















