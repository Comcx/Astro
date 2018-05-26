

#ifndef A_CODE_H
#define A_CODE_H


#include "a_debug.h"
#include "a_limit.h"
#include "a_object.h"
#include "a_parser.h"
//#include ""


/*===========================================================================

 *part1: Astro OpCodes settings
  
  we have 38 OpCodes right now, settings in detail as below...
  

============================================================================*/


/*___________________________________________________________________________
  We assume that instructions are unsigned numbers.
  All instructions have an opcode in the first 6 bits.
  Instructions can have the following fields:
  'A' : 8 bits
  'B' : 9 bits
  'C' : 9 bits
  'Ax' : 26 bits ('A', 'B', and 'C' together)
  'Bx' : 18 bits ('B' and 'C' together)
  'sBx' : signed Bx

  A signed argument is represented in excess K; that is, the number
  value is the unsigned value minus K. K is exactly the maximum value
  for that argument (so that -max is represented by 0, and +max is
  represented by 2*max), which is half the maximum for the corresponding
  unsigned argument.
_____________________________________________________________________________*/


typedef enum {iABC, iABx, iAsBx, iAx} as_OpMode;  /* basic instruction format */


/*
** size and position of opcode arguments.
*/
#define SIZE_C        9
#define SIZE_B        9
#define SIZE_Bx       (SIZE_C + SIZE_B)
#define SIZE_A        8
#define SIZE_Ax       (SIZE_C + SIZE_B + SIZE_A)

#define SIZE_OP       6

#define POS_OP      0
#define POS_A       (POS_OP + SIZE_OP)
#define POS_C       (POS_A + SIZE_A)
#define POS_B       (POS_C + SIZE_C)
#define POS_Bx      POS_C
#define POS_Ax      POS_A



/*
** limits for opcode arguments.
** we use (signed) int to manipulate most arguments,
** so they must fit in AS_BITSINT-1 bits (-1 for sign)
*/

#if SIZE_Bx < AS_BITSINT - 1
#define MAXARG_Bx        ((1 << SIZE_Bx) - 1)
#define MAXARG_sBx        (MAXARG_Bx >> 1)         /* 'sBx' is signed */
#else
#define MAXARG_Bx        INT_MAX
#define MAXARG_sBx        INT_MAX
#endif

#if SIZE_Ax < AS_BITSINT - 1
#define MAXARG_Ax   ((1 << SIZE_Ax) - 1)
#else
#define MAXARG_Ax   INT_MAX
#endif


#define MAXARG_A        ((1<<SIZE_A)-1)
#define MAXARG_B        ((1<<SIZE_B)-1)
#define MAXARG_C        ((1<<SIZE_C)-1)

#define OFFSET_sBx       MAXARG_sBx

#define NO_REG  MAXARG_A

#define BITRK       (1 << (SIZE_B - 1)) /*this bit 1 means constant*/
#define RKMASK(x)   ((x) | BITRK)   /*code a constant to RK value*/
#define INDEXK(e)   ((int)(e) & ~BITRK) /*get constant index form RK value*/



/* creates a mask with 'n' 1 bits at position 'p' */
#define MASK1(n,p)  ((~((~(Instruction)0)<<(n)))<<(p))

/* creates a mask with 'n' 0 bits at position 'p' */
#define MASK0(n,p)  (~MASK1(n,p))





typedef enum {

/*Name          args            description               */

OP_MOVE,//      A B             R(A) := R(B)
OP_LOADK,//     A Bx            R(A) := Kst(Bx)
OP_LOADBOOL,//  A B C           R(A) := BOOL(B) IF C
OP_LOADNIL,//   A B             R(A) ~ R(A+B) := NIL

OP_GETUPVAL,//  A B             R(A) := UPVAL[B]
OP_GETGLOBAL,// A Bx            R(A) := Gbl[kST(Bx)]
OP_GETTABLE,//  A B C           R(A) := R(B)[RK(C)]

OP_SETGLOBAL,// A Bx            Gbl[Kst(Bx)] := R(A)
OP_SETUPVAL,//  A B             UPVAL[B] := R(A)
OP_SETTABLE,//  A B C           R(A)[RK(B)] := RK(C)

OP_NEWTABLE,//  A B C           R(A) := {} (size = B, C)

OP_SELF,//      A B C           R(A+1) := R(B); R(A) := R(B)[RK(C)]

OP_ADD,//       A B C           R(A) := RK(B) + RK(C)
OP_SUB,//       A B C           R(A) := RK(B) - RK(C)
OP_MUL,//       A B C           R(A) := RK(B) * RK(C)
OP_DIV,//       A B C           R(A) := RK(B) / RK(C)
OP_MOD,//       A B C           R(A) := RK(B) % RK(C)
OP_POW,//       A B C           R(A) := RK(B) ^ RK(C)
OP_UNM,//       A B             R(A) := -R(B)
OP_NOT,//       A B             R(A) := NOT R(B)

OP_LEN,//       A B             R(A) := length of R(B)
OP_CONCAT,//    A B C           R(A) := R(B).. ... ..R(C)
OP_JMP,//       sBx             pc += sBx
OP_EQ,//        A B C           if ( (RK(B) == RK(C)) ~= A ) then pc++
OP_LT,//        A B C           if ( (RK(B) <  RK(C)) ~= A ) then pc++
OP_LE,//        A B C           if ( (RK(B) <= RK(C)) ~= A ) then pc++
OP_TEST,//      A C             if not (R(A) == C) then pc++
OP_TESTSET,//   A B C           if not (R(A) == C) then R(A) := R(B) else pc++

OP_CALL,//      A B C           R(A), ... ,R(A+C-2) := R(A)(R(A+1), ... ,R(A+B-1))
OP_TAILCALL,//  A B C           return R(A)(R(A+1), ... ,R(A+B-1))

OP_RETURN,//    A B             return R(A), ... ,R(A+B-2)

OP_FORLOOP,//   A sBx           R(A) += R(A+2); if R(A) <= R(A+1) then pc += sBx; R(A+3) = R(A) end
OP_FORPREP,//   A sBx           R(A) -= R(A+2); pc += sBx
OP_TFORLOOP,//  A C             R(A+3), ... ,R(A+2+C) := R(A)(R(A+1), R(A+2)); if R(A+3) ~= NIL then R(A+2) = R(A+3) else pc++

OP_SETLIST,//   A B C           R(A)[(C-1)*FPF+i]:= R(A+i), 1 <= i <= B

OP_CLOSE,//     A               close all variables in the stack up to (>=) R(A)
OP_CLOSEURE,//  A Bx            R(A) := closure(KPROTO[Bx], R(A), ... ,R(A+n))
OP_VARARG//     A B             R(A), ... ,R(A+B-1) = vararg




} as_OpCode;





/*
** masks for instruction properties. The format is:
** bits 0-1: op mode
** bits 2-3: C arg mode
** bits 4-5: B arg mode
** bit 6: instruction set register A
** bit 7: operator is a test (next instruction must be a jump)
*/


enum OpArgMask {    /*Arg masks, to define arg formats*/

    OpArgN, /*argument is not used*/
    OpArgU, /*argument is used*/
    OpArgR, /*argument is register or jump offset*/
    OpArgK  /*argument is constant or register*/
};

const as_Byte asC_OpFormat[NUM_OPCODE];
const char* const asC_OpName[NUM_OPCODE];


#define getOpMode(m) (cast(enum OpArgMask, asC_OpFormat[m] & 3))
#define getModeArg_B(m) (cast(enum OpArgMask, (asC_OpFormat[m] >> 4) & 3))
#define getModeArg_C(m) (cast(enum OpArgMask, (asC_OpFormat[m] >> 2) & 3))
#define testModeArg_A(m) (asC_OpFormat[m] & (1 << 6))
#define testModeT(m) (asC_OpFormat[m] & (1 << 7))



/*Useful marcos for OpCodes*/

#define getOpCode(instruction) ((instruction) & 0x003f)
#define getArg_A(instruction) (((instruction) & 0x3fc0) >> SIZE_OP)
#define getArg_B(instruction) (((instruction) & 0xff800000) >> (SIZE_OP+SIZE_A+SIZE_C))
#define getArg_C(instruction) (((instruction) & 0x7fc000) >> (SIZE_OP+SIZE_A))
#define getArg_Ax(instruction) (((instruction) & 0xffffffc0) >> SIZE_OP)
#define getArg_Bx(instruction) (((instruction) & 0xffffc000) >> (SIZE_OP+SIZE_A))
#define getArg_sBx(instruction) ((((instruction) & 0xffffc000) >> (SIZE_OP+SIZE_A)) - OFFSET_sBx)


#define setOpCode(i, o) ((i) = ( ((i) & MASK0(SIZE_OP, POS_OP)) | \
                                ((cast(Instruction, (o))<<POS_OP) & MASK1(SIZE_OP, POS_OP))) )
#define setArg(i, v, pos, size) ( (i) = (((i) & MASK0(size, pos)) | \
                                    ((cast(Instruction, v)<<pos) & MASK1(size, pos))) )
#define setArg_A(i ,v) setArg(i, v, POS_A, SIZE_A)
#define setArg_B(i, v) setArg(i, v, POS_B, SIZE_B)
#define setArg_C(i, v) setArg(i, v, POS_C, SIZE_C)
#define setArg_Ax(i, v) setArg(i, v, POS_Ax, SIZE_Ax)
#define setArg_Bx(i, v) setArg(i, v, POS_Bx, SIZE_Bx)
#define setArg_sBx(i, v) setArg_Bx((i), cast(unsigned int, (v)+OFFSET_sBx))

#define create_ABC(op, a, b, c) ( (cast(Instruction, op) << POS_OP) \
                            | (cast(Instruction, a) << POS_A) \
                            | (cast(Instruction, b) << POS_B) \
                            | (cast(Instruction, c) << POS_C) )
#define create_ABx(op, a, bc) ( (cast(Instruction, op) << POS_OP) \
                            | (cast(Instruction, a) << POS_A) \
                            | (cast(Instruction, bc) << POS_Bx) )
#define create_Ax(op, a) ( (cast(Instruction, op) << POS_OP) \
                            | (cast(Instruction, a) << POS_Ax) )





/*==============================================================================
  
  *part2: Astro (Byte)Code Generator
  (you can call it bytecode or whatever you like, it's a virtual code set)

===============================================================================*/


#define NO_JUMP (-1)


typedef enum BinOpr {

    OPR_ADD, OPR_SUB, OPR_MUL, OPR_MOD, OPR_POW,    /*+ - * % ^ div*/
    OPR_DIV,
    OPR_IDIV,
    OPR_BAND, OPR_BOR, OPR_BXOR,    /*&, |, ^*/
    OPR_SHL, OPR_SHR,   /*<< >>*/
    OPR_CONCAT, /*..*/
    OPR_EQ, OPR_LT, OPR_LE, /*==, <. <=*/
    OPR_NE, OPR_GT, OPR_GE, /*~=, >, >=*/
    OPR_AND, OPR_OR,    /*and, or*/
    OPR_NOBINOPR    /*none*/


} BinOpr;


typedef enum UnOpr { OPR_MINUS, OPR_BNOT, OPR_NOT, OPR_LEN, OPR_NOUNOPR } UnOpr;    /*-, ~, not, len, none*/


int asC_codeABC(FuncState *fs, as_OpCode o, int a, int b, int c);
int asC_codeABx(FuncState *fs, as_OpCode o, int a, unsigned int bx);

#define asC_codeAsBx(fs, o, a, sbx) asC_codeABx(fs, o, a, sbx+OFFSET_sBx)   /*here we plus offset to ensure sbx
                                                                                can be stored >0*/

void asC_LOADNIL(FuncState *fs, int front, int n);
void asC_concatJumpList(FuncState *fs, int *l1, int l2);
int asC_JMP(FuncState *fs);
void asC_RETURN(FuncState *fs, int first, int num_ret);
void asC_patchToHere(FuncState *fs, int list);
void asC_patchJumpList(FuncState *fs, int list, int target);
void asC_patchClose(FuncState *fs, int list, int level);
int asC_LOADK(FuncState *fs, int reg, int k);
void asC_checkStack(FuncState *fs, int n);
void asC_reserveReg(FuncState *fs, int n);




#endif




