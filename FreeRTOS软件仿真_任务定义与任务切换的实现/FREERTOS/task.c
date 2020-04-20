#include "task.h"


#if ( configSUPPORT_STATIC_ALLOCATION == 1)

//*****************************************************************************/
//*������ :TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
//                              const char * const pcName,
//                              const uint32_t ulStackDepth,
//                              void * const pvParameters,
//                              StackType_t * const puxStackBuffer,
//                              TCB_T * const pxTaskBuffer )
//*˵��   :����������
//*����   :
//*����ֵ :��ǰ���������ָ��
//*����   :
//*****************************************************************************/
TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
                                const char * const pcName,
                                const uint32_t ulStackDepth,
                                void * const pvParameters,
                                StackType_t * const puxStackBuffer,
                                TCB_T * const pxTaskBuffer )                                
{
    TCB_T *pxNewTCB;
    
    TaskHandle_t xReturn;
    
    if(( pxTaskBuffer != NULL ) && ( *puxStackBuffer != NULL ))
    {
        pxNewTCB        = (TCB_T *) puxStackBuffer;
        
        pxNewTCB->pxStack = ( StackType_t *) puxStackBuffer;
        
        // ����������
        prvInitIaliseNewTask ( pxTaskCode,      // �������
                               pcName,          // �������ƣ��ַ�����ʽ
                               ulStackDepth,    // ����ջ��С����λΪ��
                               pvParameters,    // �����β�
                               &xReturn,        // ������
                               pxNewTCB );      // ����ջ��ʼ��ַ
    }
    else
    {
        xReturn = NULL;
    }
    
    // ������������������񴴽��ɹ�����ʱxReturnӦ��ָ��������ƿ�
    return xReturn;
}


static void prvInitIaliseNewTask( TaskFunction_t      pxTaskCode,
                                  const char * const  pcName,
                                  const uint32_t      ulStackDepth,
                                  void * const        pvParameters,
                                  TaskFunction_t * const pxCreatedTask,
                                  TCB_T *             pxNewTCB )
{
    StackType_t *pxTopOfStack;
    UBaseType_t x;
    
    pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1);  // ��ȡջ����ַ
    // ������8�ֽڶ���
    pxTopOfStack = ( StackType_t * )((( uint32_t ) pxTopOfStack ) & ( ~ (( uint32_t ) 0x0007 )));
    
    // ����������ִ洢��TCB��
    for( x = ( UBaseType_t ) 0; x < (UBaseType_t ) configMax_TASK_NAME_LEN; x++)
    {
        pxNewTCB->pcTaskName[ x ] = pcName[ x ];
        if( pcName[ x ] == 0x00 )
        {
            break;
        }
    }
    
    // �������ֵĳ��Ȳ��ܳ���configMax_TASK_NAME_LEN
    pxNewTCB->pcTaskName[ configMax_TASK_NAME_LEN - 1] = '\0';
    
    // ��ʼ��TCB�е�xStateLisrItem�ڵ�
    vListInitialiseItem( &( pxNewTCB->xStateListItem ));
    
    // ���� xStateListItem�ڵ��ӵ����
    listSET_LIST_ITEM_OWNER( &( pxNewTCB->xStateListItem ), pxNewTCB);
    
    // ��ʼ������ջ
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack,     
                                                    pxTaskCode,      
                                                    pvParameters );
    // ����ŭ�Ҿ��ָ��������ƿ�
    if(( void *) pxCreatedTask != NULL)
    {
        *pxCreatedTask = ( TaskFunction_t ) pxNewTCB;
    }
                                                       
    
}                                      

#endif /* configSUPPORT_STATIC_ALLOCATION */


