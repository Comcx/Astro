
#include "a_code.h"



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
"FORREP",
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


};
























