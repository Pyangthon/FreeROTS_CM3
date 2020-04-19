
#include "list.h"


//*****************************************************************************/
//*函数名 :void vListInitialiseItem( ListItem_t * const pxItem)
//*说明   :链表节点初始化
//*参数   :ListItem_t * const pxItem  需要初始化的链表节点结构体
//*返回值 :无
//*作者   :
//*****************************************************************************/
void vListInitialiseItem( ListItem_t * const pxItem)
{
    pxItem->pvContainer = NULL; 
}


//*****************************************************************************/
//*函数名 :void vListInitialise( List_t * const pxList)
//*说明   :链表根节点初始化
//*参数   :
//*返回值 :
//*作者   :
//*****************************************************************************/
void vListInitialise( List_t * const pxList)
{
    pxList->pxIndex = (ListItem_t *) &(pxList->xListEnd);       // 将链表索引指针指向最后一个字节
    
    pxList->xListEnd.xItemValue = portMax_DELAY;                // 将链表最后一个节点的辅助培训的值设置为最大，确保该节点就是链表的最后节点
    
    pxList->xListEnd.pxNext     = ( ListItem_t *) & (pxList->xListEnd);     // 将最后一个节点的pxNext和pxPrevious指针均指向节点自身，表示链表为空
    
    pxList->xListEnd.pxPrevious = ( ListItem_t *) & (pxList->xListEnd);
    
    pxList->uxNumberOfItems     = (UBaseType_t) 0U;             // 初始化链表节点计数器的值为0，表示链表为空
}    


//*****************************************************************************/
//*函数名 :void VlistInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
//*说明   : List_t * const pxList 列表     ListItem_t * const pxNewListItem   列表项
//*参数   :
//*返回值 :
//*作者   :
//*****************************************************************************/
void VlistInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t * const pxIndex  = pxList->pxIndex;      // 取出链表索引值
        
    pxNewListItem->pxNext       = pxIndex;              // 将列表中的索引值放在列表项中      
    
    pxNewListItem->pxPrevious   = pxIndex->pxPrevious;  // 将列表中的前一项放在列表项中
    
    pxIndex->pxPrevious->pxNext = pxNewListItem;
    
    pxIndex->pxPrevious         = pxNewListItem;
    
    pxNewListItem->pvContainer  = (void *) pxList;      // 记住该节点所在的链表
    
    (pxList->uxNumberOfItems)++;                        // 链表节点计数器自增
}

