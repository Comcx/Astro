
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
























