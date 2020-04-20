#include "task.h"


#if ( configSUPPORT_STATIC_ALLOCATION == 1)

//*****************************************************************************/
//*函数名 :TaskHandle_t xTaskCreateStatic( TaskFunction_t pxTaskCode,
//                              const char * const pcName,
//                              const uint32_t ulStackDepth,
//                              void * const pvParameters,
//                              StackType_t * const puxStackBuffer,
//                              TCB_T * const pxTaskBuffer )
//*说明   :创建任务函数
//*参数   :
//*返回值 :当前创建任务的指针
//*作者   :
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
        
        // 创建新任务
        prvInitIaliseNewTask ( pxTaskCode,      // 任务入口
                               pcName,          // 任务名称，字符串形式
                               ulStackDepth,    // 任务栈大小，单位为字
                               pvParameters,    // 任务形参
                               &xReturn,        // 任务句柄
                               pxNewTCB );      // 任务栈起始地址
    }
    else
    {
        xReturn = NULL;
    }
    
    // 返回任务句柄，如果任务创建成功，此时xReturn应该指向任务控制块
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
    
    pxTopOfStack = pxNewTCB->pxStack + ( ulStackDepth - ( uint32_t ) 1);  // 获取栈顶地址
    // 向下做8字节对齐
    pxTopOfStack = ( StackType_t * )((( uint32_t ) pxTopOfStack ) & ( ~ (( uint32_t ) 0x0007 )));
    
    // 将任务的名字存储到TCB中
    for( x = ( UBaseType_t ) 0; x < (UBaseType_t ) configMax_TASK_NAME_LEN; x++)
    {
        pxNewTCB->pcTaskName[ x ] = pcName[ x ];
        if( pcName[ x ] == 0x00 )
        {
            break;
        }
    }
    
    // 任务名字的长度不能超过configMax_TASK_NAME_LEN
    pxNewTCB->pcTaskName[ configMax_TASK_NAME_LEN - 1] = '\0';
    
    // 初始化TCB中的xStateLisrItem节点
    vListInitialiseItem( &( pxNewTCB->xStateListItem ));
    
    // 设置 xStateListItem节点的拥有者
    listSET_LIST_ITEM_OWNER( &( pxNewTCB->xStateListItem ), pxNewTCB);
    
    // 初始化任务栈
    pxNewTCB->pxTopOfStack = pxPortInitialiseStack( pxTopOfStack,     
                                                    pxTaskCode,      
                                                    pvParameters );
    // 让惹怒我句柄指向任务控制块
    if(( void *) pxCreatedTask != NULL)
    {
        *pxCreatedTask = ( TaskFunction_t ) pxNewTCB;
    }
                                                       
    
}                                      

#endif /* configSUPPORT_STATIC_ALLOCATION */


