
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astro.h"

struct Test {

    int a;
    int b;

};


#define getstr(t) ((char*)(t) + sizeof(struct Test))

int main(int argc, char *argv[]) {

    
    as_Integer i = 5;
    as_Number n = 6.0;
    char *str = "can you?";

    struct Test *test = (struct Test*)malloc(sizeof(struct Test));
    test = (struct Test*)realloc(test, sizeof(struct Test) + sizeof("can you?"));
    

    memcpy(getstr(test), "can you?" ,9);

    printf("%s", getstr(test));

     
    return 0;
}














