
#include "list.h"


//*****************************************************************************/
//*������ :void vListInitialiseItem( ListItem_t * const pxItem)
//*˵��   :����ڵ��ʼ��
//*����   :ListItem_t * const pxItem  ��Ҫ��ʼ��������ڵ�ṹ��
//*����ֵ :��
//*����   :
//*****************************************************************************/
void vListInitialiseItem( ListItem_t * const pxItem)
{
    pxItem->pvContainer = NULL; 
}


//*****************************************************************************/
//*������ :void vListInitialise( List_t * const pxList)
//*˵��   :������ڵ��ʼ��
//*����   :
//*����ֵ :
//*����   :
//*****************************************************************************/
void vListInitialise( List_t * const pxList)
{
    pxList->pxIndex = (ListItem_t *) &(pxList->xListEnd);       // ����������ָ��ָ�����һ���ֽ�
    
    pxList->xListEnd.xItemValue = portMax_DELAY;                // ���������һ���ڵ�ĸ�����ѵ��ֵ����Ϊ���ȷ���ýڵ������������ڵ�
    
    pxList->xListEnd.pxNext     = ( ListItem_t *) & (pxList->xListEnd);     // �����һ���ڵ��pxNext��pxPreviousָ���ָ��ڵ�������ʾ����Ϊ��
    
    pxList->xListEnd.pxPrevious = ( ListItem_t *) & (pxList->xListEnd);
    
    pxList->uxNumberOfItems     = (UBaseType_t) 0U;             // ��ʼ������ڵ��������ֵΪ0����ʾ����Ϊ��
}    


//*****************************************************************************/
//*������ :void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
//*˵��   : ���ڵ���뵽����β��,�����뵽���һ���ڵ��ǰ�棬�䵱���ڵ�
//*����   : List_t * const pxList �б�     ListItem_t * const pxNewListItem   �б���
//*����ֵ :
//*����   :
//*****************************************************************************/
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t * const pxIndex  = pxList->pxIndex;      // �ҳ������β�ڵ㣬�����������
        
    pxNewListItem->pxNext       = pxIndex;              // ���б��е�����ֵ�����б�����      
    
    pxNewListItem->pxPrevious   = pxIndex->pxPrevious;  // ���б��е�ǰһ������б�����
    
    pxIndex->pxPrevious->pxNext = pxNewListItem;
    
    pxIndex->pxPrevious         = pxNewListItem;
    
    pxNewListItem->pvContainer  = (void *) pxList;      // ���ڵ����������
    
    (pxList->uxNumberOfItems)++;                        // ����ڵ����������
}


//*****************************************************************************/
//*������ :void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem)
//*˵��   :���ڵ㰴���������в�������
//*����   :List_t * const pxList  ��Ҫ����Ľڵ�  ListItem_t * const pxNewListItem  �����������
//*����ֵ :��
//*����   :
//*****************************************************************************/
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem)
{
	ListItem_t 		* pxIterator;						// ����һ���б���
	
	const TickType_t xValveOfInsertion = pxNewListItem->xItemValve;		// ��ȡ�ڵ��������ֵ
	/* Ѱ�ҽڵ�Ҫ�����λ�� */
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
			// �����κ��£����ϵ���ֻΪ���ҵ��ڵ�Ҫ�����λ��
		}
	}
	
	/* �������򽫽ڵ���� */
	pxNewListItem->pxNext 				= pxIterator->pxNext;
	
	pxNewListItem->pxNext->pxPrevious 	= pxNewListItem;
	
	pxNewListItem->pxPrevious			= pxIterator;
	
	pxIterator->pxNext					= pxNewListItem;
	
	pxNewListItem->pvContainer 			= (void *)pxList;		// ��ס�ýڵ����ڵ�����
	
	(pxList->uxNumberOfItems)++;		// ����ڵ�������Լ�
}


//*****************************************************************************/
//*������ :UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove)
//*˵��   :�ӽڵ��н�����ɾ��
//*����   :ListItem_t * const pxItemToRemove    ��Ҫ��ɾ���Ľڵ�
//*����ֵ :pxList->uxNumberOfItems		������ʣ��ڵ���
//*����   :
//*****************************************************************************/
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove)
{
	List_t * const pxList  = ( List_t *) pxItemToRemove->pvContainer;	// ��ȡ�ڵ����ڵ�����
	
	/* ��ָ���Ľڵ��������ɾ�� */
	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;	// ����Ҫɾ���Ľڵ��ָ��ָ��ǰһ���ڵ�
	
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;		// ����Ҫɾ���Ľڵ��ָ��ָ����һ���ڵ�
	/* ��������Ľڵ�����ָ�� */
	if(pxList->pxIndex == pxItemToRemove)
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;	// ���б����е�����ֵ��������ǰ�ڵ��ǰһ���ڵ�
	}
	
	pxItemToRemove->pvContainer = NULL;					// ��ʼ���ýڵ����ڵ�����Ϊ�أ���ʾ�ڵ㻹û�в����κ�����
	
	(pxList->uxNumberOfItems)--;		// ����ڵ�������Լ�1
	
	return pxList->uxNumberOfItems;		// ����������ʣ��ڵ����
}



