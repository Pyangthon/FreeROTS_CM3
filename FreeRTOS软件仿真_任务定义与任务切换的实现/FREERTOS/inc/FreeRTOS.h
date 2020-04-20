#ifndef __FREERTOS_H_
#define __FREERTOS_H_

#include "list.h"
#include "FreeRTOSConfig.h"

// 任务控制块类型声明
typedef struct takTaskControlBlock
{
    volatile StackType_t    *pxTopOfStack;      // 栈顶
    
    ListItem_t              xStateListItem;     // 任务节点
    
    StackType_t             *pxStack;           // 任务栈起始地址
    
    char                    pcTaskName[configMax_TASK_NAME_LEN];    
}tskTCB;
typedef tskTCB TCB_T;



#endif /*__FREERTOS_H_*/

