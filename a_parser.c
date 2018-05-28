

#include "a_parser.h"
#include "a_debug.h"
#include "a_func.h"
#include "a_string.h"
#include "a_code.h"



typedef struct Block {

    struct Block *prev;
    int firstLabel;
    int firstGoto;
    as_Byte num_actVar;
    as_Byte hasUpVal;
    as_Byte isLoop;

} Block;



static void parseError(FuncState *fs, const char *msg, int info) {

    printf("Parser error with %d, %s", info, msg);
    exit(-1);
} 


void asY_debugParser(FuncState *fs) {

    printf("\n------------------debug parser----------------\n");
    printf("pc:\t%d\n", fs->pc);
    printf("lastTarget:\t%d\n", fs->lastTarget);
    printf("pc_j:\t%d\n", fs->pc_j);
    printf("num_k:\t%d\nnum_p:\t%d\n", fs->num_k, fs->num_p);
    printf("num_absLineInfo:\t%d\n", fs->num_absLineInfo);
    printf("firstLocal:\t%d\n", fs->firstLocal);
    printf("num_LocVar:\t%d\n", fs->num_LocVar);
    printf("num_actVar:\t%d\n", fs->num_actVar);
    printf("num_UpVal:\t%d\n", fs->num_UpVal);
    printf("freeReg:;\t%d\n", fs->freeReg);
    //printf("");
    printf("-----------------------end---------------------\n");
}


static int check(LexState *ls, int ch) {

    if (ls->t.token != ch) {
        parseError(ls->fs, "token not matched!", ls->t.token);
    }
}


static int testNext(LexState *ls, int ch) {

    if (ls->t.token == ch) {

        asX_next(ls);
        return 1;
    }
    
    else return 0;
}


static as_String *checkName(LexState *ls) {

    as_String *s;
    check(ls, TK_NAME);
    
    asX_next(ls);
    return ls->t.semInfo.str;
}


static void initExp(ExpDesc *e, as_ExpKind k, int info) {

    e->list_t = e->list_f = NO_JUMP;
    e->kind = k;
    e->u.info = info;
}


static int newUpVal(FuncState *fs, as_String *name, ExpDesc *e) {

    Proto *f = fs->f;
    int size_old = f->size_UpVal;
    
    /*unfinished!*/
    return fs->num_UpVal++;
}


static int registerLocVar(LexState *ls, as_String *name) {

    FuncState *fs = ls->fs;
    Proto *f = fs->f;
    int size_old = f->size_LocVar;

    asM_growVector(ls->S, f->locVar, fs->num_LocVar, f->size_LocVar, SHRT_MAX, LocVar);

    while (size_old < f->size_LocVar) {
        
        f->locVar[size_old++].name = NULL;
    }
    f->locVar[fs->num_LocVar].name = name;

    return fs->num_LocVar++;
}


static void newLocVar(LexState *ls, as_String *name) {

    FuncState *fs = ls->fs;
    DynData *dyd = ls->dyd;
   
    int reg = registerLocVar(ls, name);
    asM_growVector(ls->S, dyd->actVar.index, dyd->actVar.n+1, dyd->actVar.size, INT_MAX, short);
    dyd->actVar.index[dyd->actVar.n++] = cast(short, reg);
}


static LocVar *getLocVar(FuncState *fs, int i) {

    int index = fs->ls->dyd->actVar.index[fs->firstLocal + i];
    as_assert(index < fs->num_LocVar);

    return &fs->f->locVar[index];
}


static void adjustLocVar(LexState *ls, int num_var) {

    FuncState *fs = ls->fs;
    fs->num_actVar = cast(as_Byte, fs->num_actVar + num_var);
    for (; num_var; num_var--) {

        getLocVar(fs, fs->num_LocVar - num_var)->p_start = fs->pc;
    }
}



static void enterBlock(FuncState *fs, Block *bl, as_Byte isLoop) {

    bl->isLoop = isLoop;
    bl->num_actVar = fs->num_actVar;
    bl->firstLabel = 0; /*unfinished!*/
    bl->hasUpVal = 0;
    bl->prev = fs->bl;
    fs->bl = bl;
    as_assert(fs->freeReg == bl->num_actVar);
}



static void openFunc(LexState *ls, FuncState *fs, Block *bl) {

    Proto *f = fs->f;
    fs->prev = ls->fs;
    ls->fs = fs;
    fs->ls = ls;
    fs->pc = 0;
    fs->lastTarget = 0;
    fs->pc_j = NO_JUMP;
    fs->freeReg = 0;
    fs->num_k = 0;
    fs->num_p = 0;
    fs->num_UpVal = 0;
    fs->num_LocVar = 0;
    fs->num_actVar = 0;
    fs->firstLocal = 0; /*this is unfinished!*/
    fs->bl = NULL;
    f->source = ls->source;
    f->size_maxStack = 2;
    
    enterBlock(fs, bl, 0);
}



static void closeFunc(LexState *ls) {



}


 



/*==============================================================================
*
* Grammar rules
*
*
*==============================================================================*/




static const struct {

    as_Byte left;  /* left priority for each binary operator */
    as_Byte right; /* right priority */

} priority[] = {  /* ORDER OPR */

    {10, 10}, {10, 10},           /* '+' '-' */
    {11, 11}, {11, 11},           /* '*' '%' */
    {14, 13},                  /* '^' (right associative) */
    {11, 11}, {11, 11},           /* '/' '//' */
    {6, 6}, {4, 4}, {5, 5},   /* '&' '|' '~' */
    {7, 7}, {7, 7},           /* '<<' '>>' */
    {9, 8},                   /* '..' (right associative) */
    {3, 3}, {3, 3}, {3, 3},   /* ==, <, <= */
    {3, 3}, {3, 3}, {3, 3},   /* ~=, >, >= */
    {2, 2}, {1, 1}            /* and, or */
};

#define UNARY_PRIORITY    12  /* priority for unary operators */







static BinOpr subexpr(LexState *ls, ExpDesc *e, int limit) {
    
    BinOpr op;
    UnOpr uop;


    return 0;
}



static void expr(LexState *ls, ExpDesc *e) {

    subexpr(ls, e, 0);
}



static int explist(LexState *ls, ExpDesc *e) {

    /* explist -> expr { ',' expr } */
    int n = 1;  /*at least 1 expression*/


    return 0;
}



static void localstat(LexState *ls) {

    /* stat -> LOCAL NAME {',' NAME} ['=' explist] */
    int num_var = 0;
    int num_exp = 0;

    ExpDesc e;
    /*read local vars*/
    do {
        //printf("local test %d\n", ls->t.token);
        newLocVar(ls, checkName(ls));
        num_var++;

    } while (testNext(ls, ','));

    if (testNext(ls, '=')) {
        
    } else {
    
    }
    

    adjustLocVar(ls, num_var);
    asY_debugParser(ls->fs);
}                                                      


static int blockFollow(LexState *ls, int withUntil) {

    switch (ls->t.token) {
    
        case TK_ELSE: case TK_ELSEIF:
        case TK_END: case TK_EOS:
            return 1;
        case TK_UNTIL:
            return withUntil;
        default:
            return 0;
    }
}



static void statement(LexState *ls) {

    int line = ls->num_line;
    //enterLevel(ls);
    switch (ls->t.token) {
    
        case ';': {
            asX_next(ls);
            break;
        }
        case TK_IF: {
            
            printf("ifstat\n");
            break;
        }
        case TK_WHILE: {
            
            printf("whilestate\n");
            break;
        }
        case TK_DO: {
            
            printf("dostat\n");
            break;
        }
        case TK_FOR: {
            
            printf("forstat\n");
            break;
        }
        case TK_REPEAT: {
            
            printf("repeatstat\n");
            break;
        }
        case TK_FUNCTION: {
            
            printf("funcstat\n");
            break;
        }
        case TK_LOCAL: {
            asX_next(ls);   /*skip 'local'*/
            localstat(ls);
            printf("localstat\n");
            break;
        }
        case TK_DBCOLON: {
            
            printf("dbcolon");
            break;
        }
        case TK_RETURN: {
            
            printf("retstat");
            break;
        }
        case TK_BREAK: {
            
            break;
        }
        case TK_GOTO: {
            
            break;
        }
        default: {
            
            break;
        }
    }

    asX_next(ls);
}




static void statlist(LexState *ls) {

    /* statlist -> { stat [';'] } */
    while (!blockFollow(ls, 1)) {
    
        if (ls->t.token == TK_RETURN) {
            statement(ls);
            return;
        }
        statement(ls);
    }

}















static void mainFunc(LexState *ls, FuncState *fs) {

    Block bl;
    ExpDesc e;
    openFunc(ls, fs, &bl);
    fs->f->isVararg = 1;
    initExp(&e, EX_LOCAL, 0);
    newUpVal(fs, ls->env, &e);
    int test = asX_next(ls);

    printf("%s: %d\n", ls->buffer->buffer, test);
    asY_debugParser(fs);
    statlist(ls);
    //as_assert(ls->t.token == TK_EOS);
    closeFunc(ls);
}



as_AClosure *asY_parser(as_State *S, as_IO *io, as_Buffer *buffer, 
                        const char *name, int firstChar) {

    LexState lexState;
    FuncState funcState;
    DynData dyd;
    //dyd.actVar.index = asM_malloc(S, sizeof(short));
    as_AClosure *cl = asF_newAClosure(S, 1);
    funcState.f = asF_newProto(S);
    funcState.f->source = asS_newString(S, name);
    lexState.buffer = buffer;
    lexState.dyd = &dyd;
    dyd.actVar.n = 0; 

    asX_setInput(S, &lexState, io, funcState.f->source, firstChar);

    /*TEST AREA, should be removed later*/
   
    /*
    asX_next(&lexState);
    printf("%d\n", lexState.t.semInfo.i);

    asX_next(&lexState);
    printf("%lf\n", lexState.t.semInfo.r);

    asX_next(&lexState);
    printf("%s\n", lexState.buffer->buffer);*/

    mainFunc(&lexState, &funcState);


    
    /*Since we haven't make use of GC system, we free spaces by hand*/
    funcState.f->source = asS_freeString(S, funcState.f->source);
    funcState.f = asM_free(S, funcState.f);
    //dyd.actVar.index = asM_free(S, dyd.actVar.index);

    return cl;
}





















