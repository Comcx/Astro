
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astro.h"
#include "a_mem.h"
#include "a_state.h"

struct Test {

    int a;
    int b;

};


#define getstr(t) ((char*)(t) + sizeof(struct Test))

int main(int argc, char *argv[]) {

    
    as_Integer i = 5;
    as_Number n = 6.0;
    char *str = "can you?";

    struct Test *test;
    test = (struct Test*)asM_alloc(test, sizeof(struct Test), sizeof("can you?"), 1);
    //test = (struct Test*)realloc(test, sizeof(struct Test) + sizeof("can you?"));
    

    memcpy(getstr(test), "can you?" ,9);

    printf("%s", getstr(test));
    
    test = asM_alloc((void*)test, 0, 0, 0);
    
    //printf("%d\n", test->a);    
    as_State *S = asE_newState();
    //test = asM_malloc(S, sizeof(struct Test));
    //test->a = 7;

    //printf("%d\n", test->a);

    int *arr = asM_newVector(S, 3, int);
    arr[2] = 2;
    arr = asM_free(S, arr);
    printf("\n\n%d", arr[2]);



    return 0;
}














