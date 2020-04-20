#ifndef __FREERTOS_H_
#define __FREERTOS_H_

#include "list.h"
#include "FreeRTOSConfig.h"

// ������ƿ���������
typedef struct takTaskControlBlock
{
    volatile StackType_t    *pxTopOfStack;      // ջ��
    
    ListItem_t              xStateListItem;     // ����ڵ�
    
    StackType_t             *pxStack;           // ����ջ��ʼ��ַ
    
    char                    pcTaskName[configMax_TASK_NAME_LEN];    
}tskTCB;
typedef tskTCB TCB_T;



#endif /*__FREERTOS_H_*/

