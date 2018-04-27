
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astro.h"
#include "a_mem.h"

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
    test = (struct Test*)asM_alloc(test, sizeof(struct Test), sizeof("can you?"));
    //test = (struct Test*)realloc(test, sizeof(struct Test) + sizeof("can you?"));
    

    memcpy(getstr(test), "can you?" ,9);
    test->a = 5;

    printf("%s", getstr(test));
    
    test = asM_alloc((void*)test, 0, 0);
    printf("%s", getstr(test));
     
    return 0;
}














