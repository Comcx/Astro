

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



static int check(LexState *ls, int ch) {

    if (ls->t.token != ch) {
        parseError(ls->fs, "token not matched!", ch);
    }
}


static int testNext(LexState *ls, int ch) {

    if (ls->current == ch) {
        asX_next(ls);
        return 1;
    }
    
    else return 0;
}


static as_String *checkName(LexState *ls) {

    as_String *s;
    check(ls, TK_NAME);

    //printf("%s\n\n", getstr(ls->t.semInfo.str));

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
    //printf("dsgdsgsdg\n\n");
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





static void localstat(LexState *ls) {

    /* stat -> LOCAL NAME {',' NAME} ['=' explist] */
    int num_var = 0;
    int num_exp = 0;

    ExpDesc e;
    /*read local vars*/
    do {
        newLocVar(ls, checkName(ls));
        num_var++;

    } while (testNext(ls, ','));

    if (testNext(ls, '=')) {
        
    } else {
    
    }

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
            
            printf("if\n");
            break;
        }
        case TK_WHILE: {
            
            printf("while\n");
            break;
        }
        case TK_DO: {
            
            printf("do\n");
            break;
        }
        case TK_FOR: {
            
            printf("for\n");
            break;
        }
        case TK_REPEAT: {
            
            printf("repeat\n");
            break;
        }
        case TK_FUNCTION: {
            
            printf("function");
            break;
        }
        case TK_LOCAL: {
            asX_next(ls);   /*skip 'local'*/
            localstat(ls);
            printf("local\n..");
            break;
        }
        case TK_DBCOLON: {
            
            printf("dbcolon");
            break;
        }
        case TK_RETURN: {
            
            printf("return");
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

    statlist(ls);
    //as_assert(ls->t.token == TK_EOS);
    closeFunc(ls);
}



as_AClosure *asY_parser(as_State *S, as_IO *io, as_Buffer *buffer, 
                        const char *name, int firstChar) {

    LexState lexState;
    FuncState funcState;
    DynData dyd;
    dyd.actVar.index = asM_malloc(S, sizeof(short));
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
    dyd.actVar.index = asM_free(S, dyd.actVar.index);

    return cl;
}





















