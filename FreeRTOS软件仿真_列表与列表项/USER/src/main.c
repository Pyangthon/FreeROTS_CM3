
#include "list.h"

// 全局变量
// 定义链表根节点
struct xLIST        List_Test;

// 定义节点
struct xLIST_ITEM   List_Item1;
struct xLIST_ITEM   List_Item2;
struct xLIST_ITEM   List_Item3;



int main(void)
{
    
    // 链表根节点初始化
    vListInitialise( &List_Test);
    
    // 节点1初始化
    vListInitialiseItem( &List_Item1 );
    List_Item1.xItemValve = 1;
    
    // 节点2初始化
    vListInitialiseItem( &List_Item2 );
    List_Item2.xItemValve = 2;
    
    // 节点3初始化
    vListInitialiseItem( &List_Item3 );
    List_Item3.xItemValve = 3;
    
    // 将节点插入链表，按照升序排列
    vListInsert( &List_Test, &List_Item1 );
    
    vListInsert( &List_Test, &List_Item2 );
    
    vListInsert( &List_Test, &List_Item3 );
    
    while(1)
    {
        
    }
}

