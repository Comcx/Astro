
#include "a_code.h"
#include "a_debug.h"
#include "a_vm.h"

#include <math.h>



const char* const asC_OpName[NUM_OPCODE] = {

"MOVE",
"LOADK",
"LOADBOOL",
"LOADNIL",
"GETUPVAL",
"GETGLOBAL",
"GETTABLE",
"SETGLOBAL",
"SETUPVAL",
"SETTABLE",
"NEWTABLE",
"SELF",
"ADD",
"SUB",
"MUL",
"DIV",
"MOD",
"POW",
"UNM",
"NOT",
"LEN",
"CONCAT",
"JMP",
"EQ",
"LT",
"LE",
"TEST",
"TESTSET",
"CALL",
"TAILCALL",
"RETURN", 
"FORLOOP",
"FORPREP",
"TFORLOOP",
"SETLIST",
"CLOSE",
"CLOSURE",
"VARARG",
NULL

};



#define OpFormat(t,a,b,c,m) (((t)<<7) | ((a)<<6) | ((b)<<4) | ((c)<<2) | (m))

const as_Byte asC_OpFormat[NUM_OPCODE] = {

/*       T  A  B       C       mode     instruction*/
OpFormat(0, 1, OpArgR, OpArgN, iABC),   /*OP_MOVE*/
OpFormat(0, 1, OpArgK, OpArgN, iABx),   /*OP_LOADK*/
OpFormat(0, 1, OpArgU, OpArgU, iABC),   /*OP_LOADBOOL*/
OpFormat(0, 1, OpArgU, OpArgN, iABC),   /*OP_LOADNIL*/
OpFormat(0, 1, OpArgU, OpArgN, iABC),   /*OP_GETUPVAL*/
OpFormat(0, 1, OpArgK, OpArgN, iABx),   /*OP_GETGLOBAL*/
OpFormat(0, 1, OpArgR, OpArgK, iABC),   /*OP_GETTABLE*/
OpFormat(0, 1, OpArgK, OpArgU, iABx),   /*OP_SETGLOBAL*/
OpFormat(0, 1, OpArgU, OpArgN, iABC),   /*OP_SETUPVAL*/
OpFormat(0, 1, OpArgK, OpArgK, iABC),   /*OP_SETTABLE*/
OpFormat(0, 1, OpArgU, OpArgU, iABC),   /*OP_NEWTABLE*/
OpFormat(0, 1, OpArgR, OpArgK, iABC),   /*OP_SELF*/
OpFormat(0, 1, OpArgK, OpArgK, iABC),   /*OP_ADD*/
OpFormat(0, 1, OpArgK, OpArgK, iABC),   /*OP_SUB*/
OpFormat(0, 1, OpArgK, OpArgK, iABC),   /*OP_MUL*/
OpFormat(0, 1, OpArgK, OpArgK, iABC),   /*OP_DIV*/
OpFormat(0, 1, OpArgK, OpArgK, iABC),   /*OP_MOD*/
OpFormat(0, 1, OpArgK, OpArgK, iABC),   /*OP_POW*/
OpFormat(0, 1, OpArgR, OpArgN, iABC),   /*OP_UNM*/
OpFormat(0, 1, OpArgR, OpArgN, iABC),   /*OP_NOT*/
OpFormat(0, 1, OpArgR, OpArgN, iABC),   /*OP_LEN*/
OpFormat(0, 1, OpArgR, OpArgR, iABC),   /*OP_CONCAT*/
OpFormat(0, 0, OpArgR, OpArgN, iAsBx),  /*OP_JMP*/
OpFormat(1, 0, OpArgK, OpArgK, iABC),   /*OP_EQ*/
OpFormat(1, 0, OpArgK, OpArgK, iABC),   /*OP_LT*/
OpFormat(1, 0, OpArgK, OpArgK, iABC),   /*OP_LE*/
OpFormat(1, 0, OpArgN, OpArgU, iABC),   /*OP_TEST*/
OpFormat(1, 1, OpArgR, OpArgU, iABC),   /*OP_TESTSET*/
OpFormat(0, 1, OpArgU, OpArgU, iABC),   /*OP_CALL*/
OpFormat(0, 1, OpArgU, OpArgU, iABC),   /*OP_TAILCALL*/
OpFormat(0, 0, OpArgU, OpArgU, iABC),   /*OP_RETURN?*/
OpFormat(0, 1, OpArgR, OpArgN, iAsBx),  /*OP_FORLOOP*/
OpFormat(0, 1, OpArgR, OpArgN, iAsBx),  /*OP_FORPREP*/
OpFormat(0, 1, OpArgR, OpArgN, iAsBx),  /*OP_TFORLOOP*/
OpFormat(0, 0, OpArgU, OpArgU, iABC),   /*OP_SETLIST*/
OpFormat(0, 0, OpArgR, OpArgN, iABC),   /*OP_CLOSE*/
OpFormat(0, 1, OpArgU, OpArgN, iABx),   /*OP_CLOSURE*/
OpFormat(0, 1, OpArgU, OpArgN, iABC)    /*OP_VARARG*/

};




/*====================================================================
**
** Astro (Byte)Code Generator functions
**
**
=====================================================================*/



/*
** General code generator
 */


#define MAXREGS 255
#define hasJump(e) ((e->t != (e)->f))


static void parseError(FuncState *fs, const char *msg, int info) {

    printf("Parser error! %s; %d\n", msg, info);
    exit(-1);

}


static void dischargePC_J(FuncState *fs);


static int asC_code(FuncState *fs, Instruction i) {

    Proto *f = fs->f;
    dischargePC_J(fs);
    /*put new instruction in code array*/
    asM_growVector(fs->ls->S, f->code, fs->pc, f->size_code, INT_MAX, Instruction);
    f->code[fs->pc] = i;
    
    /*put line info into proto f*/
    asM_growVector(fs->ls->S, f->info_line, fs->pc, f->size_lineInfo, INT_MAX, int);
    f->info_line[fs->pc] = fs->ls->lastLine;
    
    return fs->pc++;
}


int asC_codeABC(FuncState *fs, as_OpCode o, int a, int b, int c) {

    as_assert(getOpMode(o) == iABC);
    as_assert(getModeArg_B(o) != OpArgN || b == 0);
    as_assert(getModeArg_C(o) != OpArgN || c == 0);
    as_assert(a <= MAXARG_A && b <= MAXARG_B && c <= MAXARG_C);

    return asC_code(fs, create_ABC(o, a, b, c));
}


int asC_codeABx(FuncState *fs, as_OpCode o, int a, unsigned int bx) {

    as_assert(getOpMode(o) == iABx || getOpMode(o) == iAsBx);
    as_assert(getModeArg_C(o) == OpArgN);
    as_assert(a <= MAXARG_A && bx <= MAXARG_Bx);

    return asC_code(fs, create_ABx(o, a, bx));
}



/*LOADNIL Instruction, front is the first register, n is the number of registers*/
void asC_LOADNIL(FuncState *fs, int from, int n) {

    Instruction *i_prev;
    int last = from + n - 1;
    if (fs->pc > fs->lastTarget) {  /*avoid jump instruction*/
        i_prev = &(fs->f->code[fs->pc-1]);
        if (getOpCode(*i_prev) == OP_LOADNIL) {
            int from_ = getArg_A(*i_prev);
            int last_ = getArg_B(*i_prev);

            if ( (from_ <= from && from <= last_ + 1) ||
                 (from <= from_ && last_ <= last + 1)) {    /*if can be concated*/
                 if (from_ < from) from = from_;
                 if (last_ > last) last = last_;
                 setArg_A(*i_prev, from);
                 setArg_B(*i_prev, last);
                 return;
            }
        }
    }/*can not be optimized...*/
    asC_codeABC(fs, OP_LOADNIL, from, n-1, 0);
}



/*
** Jump tool functions
 */

/*to get destination from jump instruction*/
static int getJumpDest(FuncState *fs, int pc) {

    int offset = getArg_sBx(fs->f->code[pc]);
    if (offset == NO_JUMP) {
        return NO_JUMP;
    }
    else return pc + 1 +offset;
}

/*to set destination to jump instruction*/
static void setJumpDest(FuncState *fs, int pc, int dest) {

    Instruction *jump = &fs->f->code[pc];
    int offset = dest - pc + 1;
    as_assert(dest != NO_JUMP);

    if (abs(offset) > MAXARG_sBx)
        parseError(fs, "Jump control dest too long?", 0);
    setArg_sBx(*jump, offset);
}


/*to concat jump list*/
void asC_concatJumpList(FuncState *fs, int *l1, int l2) {

    if (l2 == NO_JUMP) return;  /*nothing to concat?*/
    else if (*l1 == NO_JUMP)
        *l1 = l2;
    else {
        int list = *l1;
        int next;
        while ((next = getJumpDest(fs, list)) != NO_JUMP) {
            list = next;
        }
        setJumpDest(fs, list, l2);
    }

}


/*Create JMP instruction, here jump destination can be fixed later*/
int asC_JMP(FuncState *fs) {

    int pc_j = fs->pc_j;
    int j;
    fs->pc_j = NO_JUMP;
    j = asC_codeAsBx(fs, OP_JMP, 0, NO_JUMP);
    asC_concatJumpList(fs, &j, pc_j);
    return j;
}


/*Create RETURN Instruction*/
void asC_RETURN(FuncState *fs, int first, int num_ret) {

    asC_codeABC(fs, OP_RETURN, first, num_ret+1, 0);

}


/*Code a conditional jump*/
static int condJump(FuncState *fs, as_OpCode op, int a, int b, int c) {

    asC_codeABC(fs, op, a, b, c);
    return asC_JMP(fs);
}


/*return current pc and mark it as last jump target*/
int asC_getLabel(FuncState *fs) {

    fs->lastTarget = fs->pc;
    return fs->pc;
}



/*Return the position of the control of jump instruction
  or the jump itself if it's unconditional*/
static Instruction *getJumpControl(FuncState *fs, int pc) {

    Instruction *i = &fs->f->code[pc];
    if (pc >= 1 && testModeT(getOpCode(*(i-1)))) {
        return i - 1;
    } else return i;
}




/*
** Patch destination register for a TESTSET instruction.
** If instruction in position 'node' is not a TESTSET, return 0 ("fails").
** Otherwise, if 'reg' is not 'NO_REG', set it as the destination
** register. Otherwise, change instruction to a simple 'TEST' (produces
** no register value)
*/

static int patchTestReg(FuncState *fs, int pc, int reg) {

    Instruction *i = getJumpControl(fs, pc);
    if (getOpCode(*i) != OP_TESTSET)
        return 0;
    if (reg != NO_REG && reg != getArg_B(*i)) {
        setArg_A(*i, reg);
    } else {
        /*No register to put value or the register has been put*/
        /*Change instruction to simple TEST*/
        *i = create_ABC(OP_TEST, getArg_B(*i), 0, getArg_C(*i));
    }
    return 1;
}


/*Traverse list of TESTSET to TEST to ensure no value produced*/
static void removeTestValue(FuncState *fs, int list) {

    for (; list != NO_JUMP; list = getJumpDest(fs, list)) {
        patchTestReg(fs, list, NO_REG);
    }
}


static void patchList(FuncState *fs, int list, int reg, int target_value, 
                                                    int target_default) {

    while (list != NO_JUMP) {
    
        int next = getJumpDest(fs, list);
        if (patchTestReg(fs, list, reg)) {
            setJumpDest(fs, list, target_value);
        } else {
            setJumpDest(fs, list, target_default);
        }

        list = next;
    }

}


/*Make sure all pending jumps are fixed at current position*/
static void dischargePC_J(FuncState *fs) {

    patchList(fs, fs->pc_j, NO_REG, fs->pc, fs->pc);
    fs->pc_j = NO_JUMP;
}


/*add jump list to here*/
void asC_patchToHere(FuncState *fs, int list) {

    asC_getLabel(fs);
    asC_concatJumpList(fs, &fs->pc_j, list);
}



/*Patch jump list; if destination is current forward, error!*/
void asC_patchJumpList(FuncState *fs, int list, int target) {

    if (target == fs->pc) {
        asC_patchToHere(fs, list);  /*target is current position*/
    } else {
        as_assert(target < fs->pc);
        patchList(fs, list, NO_REG, target, target);
    }
}


void asC_patchClose(FuncState *fs, int list, int level) {

    /*unfinished!*/
}





/*
** Create LOADK instruction, i.e. OP_LOADK
 */

int asC_LOADK(FuncState *fs, int reg, int k) {

    if (k <= MAXARG_Bx) {
        return asC_codeABx(fs, OP_LOADK, reg, k);
    } else {    /*we haven't add extra argument instruction..., so as the same*/
        return asC_codeABx(fs, OP_LOADK, reg, k);
    }

}


/*Check whether stack is big enough*/
void asC_checkStack(FuncState *fs, int n) {

    int newStack = fs->freeReg + n;
    if (newStack > fs->f->size_maxStack) {
        if (newStack > MAXREGS) {
            parseError(fs, "function or expression need too many registers", 0);
        }
        fs->f->size_maxStack = cast(as_Byte, newStack);
    }
}


/*Reserve register in stack*/
void asC_reserveReg(FuncState *fs, int n) {

    asC_checkStack(fs, n);
    fs->freeReg += n;
}


/* Free register 'reg', if it is neither a constant index nor
** a local variable
*/

static void freeReg(FuncState *fs, int reg) {

    if (!ISK(reg) && reg >= fs->num_actVar) {
        fs->freeReg--;
        as_assert(fs->freeReg == reg);
    }
}


/*Free register used by expression 'e' (if any)*/
static void freeExp(FuncState *fs, ExpDesc *e) {

    if (e->kind == EX_FIXED) {
        freeReg(fs, e->u.info);
    }    
}






/*
** Add constant 'v' to prototype's list of constants (field 'k').
** Use scanner's table to cache position of constants in constant list
** and try to reuse constants. Because some values should not be used
** as keys (nil cannot be a key, integer keys can collapse with float
** keys), the caller must provide a useful 'key' for indexing the cache.
*/


static int add2k(FuncState *fs, as_Value *key, as_Value *v) {

    as_State *S = fs->ls->S;
    Proto *f = fs->f;

    as_Value *index = asT_set(S, fs->ls->table, key);
    int index_k, size_old;
    if (typeIsInteger(index)) {
        index_k = cast(int, intValue(index));
        /*check index_k is correct index of k*/
        if (index_k < fs->num_k && 
            getTypeWithVar(&f->k[index_k]) == getTypeWithVar(v) && 
            asV_objectEqual(&f->k[index_k], v)) {
        
            return index_k; /*reuse index*/
        }
    }

    /*constant not found*/
    size_old = fs->size_k;
    index_k = fs->num_k;

    /*set value to cache table*/
    setInteger(index, index_k);
    asM_growVector(S, f->k, fs->num_k, fs->size_k, MAXARG_Bx, as_Value);
    while (size_old < fs->size_k) setNil(&f->k[size_old++]);
    setObj(S, &f->k[index_k], v);
    fs->num_k++;

    return index_k;
}



/*
** Add a string to list of constants and return its index.
*/
int asC_string2k(FuncState *fs, as_String *s) {

    as_Value o;
    setString(fs->ls->S, &o, s);
    return add2k(fs, &o, &o);
}


/*
** Add an integer to list of constants and return its index.
** Integers use userdata as keys to avoid collision with floats with
** same value; conversion to 'void*' is used only for hashing, so there
** are no "precision" problems.
*/






























