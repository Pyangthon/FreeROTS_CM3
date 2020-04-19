
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
//*������ :void VlistInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
//*˵��   : List_t * const pxList �б�     ListItem_t * const pxNewListItem   �б���
//*����   :
//*����ֵ :
//*����   :
//*****************************************************************************/
void VlistInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem)
{
    ListItem_t * const pxIndex  = pxList->pxIndex;      // ȡ����������ֵ
        
    pxNewListItem->pxNext       = pxIndex;              // ���б��е�����ֵ�����б�����      
    
    pxNewListItem->pxPrevious   = pxIndex->pxPrevious;  // ���б��е�ǰһ������б�����
    
    pxIndex->pxPrevious->pxNext = pxNewListItem;
    
    pxIndex->pxPrevious         = pxNewListItem;
    
    pxNewListItem->pvContainer  = (void *) pxList;      // ��ס�ýڵ����ڵ�����
    
    (pxList->uxNumberOfItems)++;                        // ����ڵ����������
}

