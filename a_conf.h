

/****Astro configuration****/

#ifndef A_CONF_H
#define A_CONF_H


#include <limits.h>



/*======================================================
 * whether 32 bits or 64 bits
 *=======================================================*/

//if appointed then

//#define AS_32BITS
//#define AS_64BITS

//else use system configuration
/*
#if sizeof(void*) > 4
    #define AS_64BITS
#else
    #define AS_32BITS
#endif*/

/*==========================================================
 * Ensure OS system configuration
 ==========================================================*/

#if defined(AS_USE_WINDOWS)

#endif

#if defined(AS_USE_LINUX)

#endif

#if defined(AS_USE_MAC)

#endif



/*=========================================================
 * Minimum number of bits of type "int"
 *========================================================*/

#if ((INT_MAX >> 15) >> 15) >= 1
    #define AS_BITSINT 32
#else
    #define AS_BITSINT 16
#endif



/*========================================================
 * options for ASTRO_TYPE
 *========================================================*/

#define AS_INT_INT 0
#define AS_INT_LONG 1
#define AS_INT_LONGLONG 3

#define AS_FLOAT_FLOAT 0
#define AS_FLOAT_DOUBLE 1
#define AS_FLOAT_LONGDOUBLE 3

#if defined(ASTRO_BITSINT)

#if AS_BITSINT >= 32
    #define AS_INT_TYPE AS_INT_INT
#else
    #define AS_INT_TYPE AS_INT_LONG
#endif

#endif

#define AS_FLOAT_TYPE AS_FLOAT_FLOAT


/*
** astro basic types: number, integer
 */

#if AS_FLOAT_TYPE == AS_FLOAT_FLOAT

    #define AS_NUMBER float


#elif AS_FLOAT_TYPE == AS_FLOAT_DOUBLE

    #define AS_NUMBER double

#elif AS_FLOAT_TYPE == AS_FLOAT_LONGDOUBLE

    #define AS_NUMBER long double


#endif


#if AS_INT_TYPE == AS_INT_INT

    #define AS_INTEGER int

#elif AS_INT_TYPE == AS_INT_LONG

    #define AS_INTEGER long

#elif AS_INT_TYPE == AS_INT_LONGLONG

    #define AS_INTEGER long long

#endif


#define AS_UNSIGNED unsigned AS_INTEGER
#define AS_BYTE unsigned char



/*==========================================================
 * ASTRO_PATH configurations
 *==========================================================*/

#if defined(AS_USE_WINDOWS)

    #define AS_DIRSEP "\\"
#else
    #define AS_DIRSEP ""/

#endif


/*==========================================================
 * Language variations
 *==========================================================*/

#if AS_BITSINT >= 32

    #define AS_MAXSTACK 1000000
#else
    #define AS_MAXSTACK 15000

#endif





/**/
/**/





#endif























