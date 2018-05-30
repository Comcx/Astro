
/**=======================================================================================
 * astro.h
 * Comcx
 *
 **======================================================================================*/

#ifndef ASTRO_H
#define ASTRO_H


#include "a_conf.h"
#include <stddef.h>


#define AS_VERSION_MAJOR "0"
#define AS_VERSION_MINOR "1"
#define AS_VERSION_RELEASE "1"

#define AS_VERSION AS_VERSION_MAJOR "." AS_VERSION_MINOR
#define AS_RELEASE AS_VERSION_MAJOR "." AS_VERSION_RELEASE
#define AS_COPYRIGHT AS_RELEASE "Copyright (C) 2017-2018 Comcx"
#define AS_AUTHORS "Comcx" "Veurnasm" "Dr.Code"


/*
** Astro thread status
 */

#define AS_OK 0
#define AS_YIELD 1
#define AS_RETURN 2
#define AS_ERROR 3
#define AS_RETURNMEM 4


typedef struct as_State as_State;


#define MIN_STACK 20



/*
** Astro basic used types
 */

#define AS_TNONE       (-1)

#define AS_TNIL         0           //nil
#define AS_TBOOLEAN     1           //bool
#define AS_UNDEF        2           //undef
#define AS_TNUMBER      3           //number
#define AS_TSTRING      4           //string
#define AS_TTABLE       5           //table
#define AS_TFUNCTION    6           //function
#define AS_TUSERDATA    7           //userdata
#define AS_TTHREAD      8           //thread

#define AS_NUMTAGS      9





typedef AS_NUMBER   as_Number;
typedef AS_INTEGER  as_Integer;
typedef AS_UNSIGNED as_Unsigned;
typedef AS_BYTE     as_Byte;


typedef int (*as_CFunction) (as_State *S);


//void *as_Alloc(void *ptr, size_t size_object, size_t size_new, size_t num);


typedef void *(*as_Alloc)(void *ptr, size_t size_object, size_t size_new, size_t num);
typedef const char* (*as_Reader)(as_State *S, size_t *sz, void *ud);
//typedef int (*as_Writer)()








/*
** Cast tools
 */

#define cast(t, o) ((t)(o))
#define cast_uchar(o) ((unsigned char)(o))















#endif


















