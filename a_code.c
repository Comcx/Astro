
#include "a_code.h"



#define OpFormat(t,a,b,c,m) (((t)<<7) | ((a)<<6) | ((b)<<4) | ((c)<<2) | (m))

const as_Byte OpFormat[NUM_OPCODE] = {

OpFormat(0, 1, 2, 3, iABC),     /*OP_MOVE*/



};
























