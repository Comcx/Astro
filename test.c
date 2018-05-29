
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
#include "a_gc.h"
#include "a_func.h"
#include "a_parser.h"
#include "a_vm.h"
#include <stdlib.h>



int main(int argc, char *argv[]) {

    
    //memcpy(getstr(test), "can you?" ,8);
    
    as_State *S = asE_newState();
    //test = asM_malloc(S, sizeof(struct Test));
    
    as_String *str = asS_newString(S, "ENV");

    str = asS_freeString(S, str);
    
    
    FILE *file;
    file = fopen("test.as", "r");

    FileLoader fl;
    fl.file = file;
    fl.n = 0;

    as_IO io;
    asI_init(S, &io, asU_read, &fl);

    as_Buffer *buffer = asM_malloc(S, sizeof(as_Buffer));
    asI_resizeBuffer(S, buffer, 512);

    //as_AClosure *cl = asY_parser(S, &io, buffer, "ENV", asI_fill(&io));
    

    //cl = asM_free(S, cl);





    fclose(file);

    S = asE_closeState(S);
    return 0;
}














