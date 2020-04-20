
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
//*函数名 :void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
//*说明   : 将节点插入到链表尾部,即插入到最后一个节点的前面，充当最后节点
//*参数   : List_t * const pxList 列表     ListItem_t * const pxNewListItem   列表项
//*返回值 :
//*作者   :
//*****************************************************************************/
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t * const pxIndex  = pxList->pxIndex;      // 找出链表的尾节点，即链表的索引
        
    pxNewListItem->pxNext       = pxIndex;              // 将列表中的索引值放在列表项中      
    
    pxNewListItem->pxPrevious   = pxIndex->pxPrevious;  // 将列表中的前一项放在列表项中
    
    pxIndex->pxPrevious->pxNext = pxNewListItem;
    
    pxIndex->pxPrevious         = pxNewListItem;
    
    pxNewListItem->pvContainer  = (void *) pxList;      // 将节点归入链表中
    
    (pxList->uxNumberOfItems)++;                        // 链表节点计数器自增
}


//*****************************************************************************/
//*函数名 :void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem)
//*说明   :将节点按照升序排列插入链表
//*参数   :List_t * const pxList  需要插入的节点  ListItem_t * const pxNewListItem  被插入的链表
//*返回值 :无
//*作者   :
//*****************************************************************************/
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem)
{
	ListItem_t 		* pxIterator;						// 定义一个列表项
	
	const TickType_t xValveOfInsertion = pxNewListItem->xItemValve;		// 获取节点的排序辅助值
	/* 寻找节点要插入的位置 */
	if( xValveOfInsertion == portMax_DELAY)
	{	
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		for( pxIterator = (ListItem_t *) & (pxList->xListEnd);
				pxIterator->pxNext->xItemValve <= xValveOfInsertion;
				pxIterator = pxIterator->pxNext)
		{
			// 不做任何事，不断迭代只为了找到节点要插入的位置
		}
	}
	
	/* 根据升序将节点插入 */
	pxNewListItem->pxNext 				= pxIterator->pxNext;
	
	pxNewListItem->pxNext->pxPrevious 	= pxNewListItem;
	
	pxNewListItem->pxPrevious			= pxIterator;
	
	pxIterator->pxNext					= pxNewListItem;
	
	pxNewListItem->pvContainer 			= (void *)pxList;		// 记住该节点所在的链表
	
	(pxList->uxNumberOfItems)++;		// 链表节点计数器自加
}


//*****************************************************************************/
//*函数名 :UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove)
//*说明   :从节点中将链表删除
//*参数   :ListItem_t * const pxItemToRemove    需要被删除的节点
//*返回值 :pxList->uxNumberOfItems		链表中剩余节点数
//*作者   :
//*****************************************************************************/
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove)
{
	List_t * const pxList  = ( List_t *) pxItemToRemove->pvContainer;	// 获取节点所在的链表
	
	/* 将指定的节点从链表中删除 */
	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;	// 将需要删除的节点的指针指向前一个节点
	
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;		// 将需要删除的节点的指针指向下一个节点
	/* 调整链表的节点索引指针 */
	if(pxList->pxIndex == pxItemToRemove)
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;	// 将列表项中的索引值调整到当前节点的前一个节点
	}
	
	pxItemToRemove->pvContainer = NULL;					// 初始化该节点所在的链表为控，表示节点还没有插入任何链表
	
	(pxList->uxNumberOfItems)--;		// 链表节点计数器自减1
	
	return pxList->uxNumberOfItems;		// 返回链表中剩余节点个数
}



