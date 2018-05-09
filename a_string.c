


#include "a_string.h"
#include "a_mem.h"
#include <stdio.h>


unsigned int ELFhash(char *str) {

    unsigned int hash = 0;
    unsigned int x = 0;
    while (*str) {

        hash = (hash << 4) + *str;
        if (x = hash & 0xf0000000 != 0) {

            hash ^= (x >> 24);
            hash &= ~x;
        }
        str++;
    }
    
    return (hash & 0x7fffffff);
}


unsigned int asS_hash(as_State *S, char *str) {

    printf(">>>%d\n", ELFhash(str));
    return ELFhash(str) % G(S)->strt.size;

}



int asS_equal(as_String *a, char *str) {


    return 0;
}



as_String *asS_newString(as_State *S, char *str) {
    
    /*first we search global string table, if already exits, just return ptr*/
    unsigned int hash = asS_hash(S, str);//get hash
    //printf("%d", hash);

    Table_String *strt = &(G(S)->strt);

    as_String *node = strt->hash[hash];
    as_String *p = strt->hash[hash];
    while (p) {

        if (asS_equal(p, str)) {

            return p;
        } else {

            p = p->hnext;    
        }
    }


    /*not found*/
    as_String *ans = (as_String*)asM_malloc(S, sizeof(as_String));
    ans->hnext = node;
    strt->hash[hash] = ans;
    
    ans->reserved = 0;
    ans->hash = hash;
    //ans->hnext = NULL;
    ans->len = -1;
    
    return ans;
}


as_String *asS_freeString(as_State *S, as_String *str) {

    str = asM_free(S, str);

    return str;
}




void debug_String(as_State *S, as_String *str) {

    printf("reserved: %d\nhash: %d\nhnext: %d\nlen: %d\n", str->reserved, str->hash, str->hnext, str->len);

}
















