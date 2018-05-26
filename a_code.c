
#include "a_code.h"
#include "a_debug.h"

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


static void patchJumpListAux(FuncState *fs, int list, int reg, int target_value, 
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



static void dischargePC_J(FuncState *fs) {

    patchJumpListAux(fs, fs->pc_j, NO_REG, fs->pc, fs->pc);
    fs->pc_j = NO_JUMP;
}

























