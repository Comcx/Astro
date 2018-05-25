
#include "astro.h"
#include "a_mem.h"
#include "a_state.h"
#include "a_string.h"
#include "a_table.h"
#include "a_code.h"
#include "a_ui.h"
#include "a_io.h"
#include "a_lex.h"
#include "a_debug.h"
#include <stdlib.h>



int main(int argc, char *argv[]) {

    
    //memcpy(getstr(test), "can you?" ,8);
    
    as_State *S = asE_newState();
    //test = asM_malloc(S, sizeof(struct Test));
    
    as_String *str = asS_newString(S, "2333");

    str = asS_freeString(S, str);
    
    
    Instruction order_ABC = create_ABC(OP_MOVE, 7, 8, 9);
    Instruction order_ABx = create_ABx(OP_LOADK, 4, 5);
    Instruction order_Ax = create_Ax(OP_LOADNIL, 1);
    
    printf("ABC: %s %d %d %d\n", asC_OpName[getOpCode(order_ABC)], getArg_A(order_ABC), getArg_B(order_ABC), getArg_C(order_ABC));
    printf("ABx: %s %d %d\n", asC_OpName[getOpCode(order_ABx)], getArg_A(order_ABx), getArg_Bx(order_ABx));
    printf("Ax: %s %d\n", asC_OpName[getOpCode(order_Ax)], getArg_Ax(order_Ax));


    printf("\n--------------------\n");    
    FILE *file;
    file = fopen("test.txt", "r");

    FileLoader fl;
    fl.file = file;
    fl.n = 0;

    as_IO io;
    asI_init(S, &io, asU_read, &fl);

    //int ch = as_getc(&io);
    LexState ls;
    //SemInfo seminfo;
    
    asX_setInput(S, &ls, &io, str, asI_fill(&io));
    
    //const char *buff = asU_read(S, &size, &fl);
    ls.buffer = asM_malloc(S, sizeof(as_Buffer));
    asI_resizeBuffer(S, ls.buffer, 512);

    asX_next(&ls);
    printf("%lf\n", ls.t.semInfo.r);

    asX_next(&ls);
    printf("%d\n", ls.t.semInfo.i);
    
    asX_next(&ls);
    printf("%lf\n", ls.t.semInfo.r);

    asX_next(&ls);
    printf("%s\n", ls.buffer->buffer);
    //printf("%d\n", ls.t.semInfo.i);

    
    int *test = asM_newVector(S, 3, int);
    asM_growVector(S, test, 2, 3, 10, int);
    *test = 1;
    *(test+3) = 2;
    printf("%d\n", test[3]);
    test = asM_free(S, test);

    fclose(file);

    S = asE_closeState(S);
    return 0;
}














