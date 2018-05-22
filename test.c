
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




int main(int argc, char *argv[]) {

    
    //memcpy(getstr(test), "can you?" ,8);
    
    as_State *S = asE_newState();
    //test = asM_malloc(S, sizeof(struct Test));
    
    as_String *str = asS_newString(S, "2333");

    as_Value v;
    setString(S, &v, str);
    
    as_Table *t = asT_newArray(S, 10);
    t->array[0] = v;
    debug_Table(t);

    //str = asS_freeString(S, str);
    
    /*
    int order = (4 << 23) | (3 << 14) | (2 << 6) | 1;
    printf("%x\n", order);
    as_OpCode code = OP_MOVE;
    printf("%d\n", code == getOpCode(order));
    printf("%d\n%d\n%d\n", getArg_A(order), getArg_B(order), getArg_C(order));
    
    int x = OP_LOADK;
    printf("%d\n", x);*/

    
    FILE *file;
    file = fopen("test.txt", "r");

    FileLoader fl;
    fl.file = file;
    fl.n = 0;

    //char buff[50];
    //fread(buff, 1, 5, file);

    as_IO io;
    asI_init(S, &io, asU_read, &fl);

    //int ch = as_getc(&io);
    LexState ls;
    
    asX_setInput(S, &ls, &io, str, asI_fill(&io));
    
    //const char *buff = asU_read(S, &size, &fl);
    printf("%c\n", cast(char, ls.current));
    printf("%s", io.p);
    

    as_Value obj;
    const char *str_num = "0x10a";

    asO_str2num(str_num, &obj);
    printf("%d", getValue(&obj).i);


    fclose(file);

    S = asE_closeState(S);
    return 0;
}














