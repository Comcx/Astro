

#ifndef A_CODE_H
#define A_CODE_H


#include "a_debug.h"




/*===========================================================================
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
===========================================================================*/


typedef enum {iABC, iABx, iAsBx, iAx} OpMode;  /* basic instruction format */


/*
** size and position of opcode arguments.
*/
#define SIZE_C        9
#define SIZE_B        9
#define SIZE_Bx       (SIZE_C + SIZE_B)
#define SIZE_A        8
#define SIZE_Ax       (SIZE_C + SIZE_B + SIZE_A)

#define SIZE_OP       6




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




} OpCode;


#define getOpCode(instruction) ((instruction) & 0x003f)
#define getArg_A(instruction) (((instruction) & 0x3fc0) >> SIZE_OP)
#define getArg_B(instruction) (((instruction) & 0xff800000) >> (SIZE_OP+SIZE_A+SIZE_C))
#define getArg_C(instruction) (((instruction) & 0x7fc000) >> (SIZE_OP+SIZE_A))
#define getArg_Ax(instruction) (((instruction) & 0xffffffc0) >> SIZE_OP)
#define getArg_Bx(instruction) (((instruction) & 0xffffc000) >> (SIZE_OP+SIZE_A))
#define getArg_sBx(instruction) (((instruction) & 0xffffc000) >> (SIZE_OP+SIZE_A))





#endif




