
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
    
    
    Instruction order = (4 << 23) | (3 << 14) | (2 << 6) | 1;
    printf("order: %x\n", order);
    as_OpCode code = OP_MOVE;
    printf("OpCode: %d\n", code == getOpCode(order));
    printf("Regs:\n%d\n%d\n%d\n", getArg_A(order), getArg_B(order), getArg_C(order));
    
    setArg_B(order, 7);
    printf("OpCode_new: %d\n", getArg_A(order));

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


    fclose(file);

    S = asE_closeState(S);
    return 0;
}














