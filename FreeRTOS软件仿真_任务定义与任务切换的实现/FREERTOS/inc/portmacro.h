#ifndef __PORTMACRO_H_
#define __PORTMACRO_H_

#include <stdint.h>
#include <stddef.h>


/*数据类型重定义*/

#define portCHAR        char
#define portFLOAT       float
#define portDOUBLE      double
#define portLONG        long
#define portSHORT       short
#define portSTAK_TYPE   uint32_t
#define portBASR_TYPE   long

typedef portSTAK_TYPE StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;

#if(configUSE_16_BIT_TICK == 1)
typedef uint16_t TickType_t;
#define portMax_DELAY ( TickType_t) 0xfffff
#else
typedef uint32_t TickType_t;
#define portMax_DELAY ( TickType_t) 0xffffffffUL
#endif



#endif /*__PORTMACRO_H_*/


