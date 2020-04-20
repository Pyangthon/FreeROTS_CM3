#ifndef __LIST_H_
#define __LIST_H_
#include "portmacro.h"


/*
********************************************************
                    �ṹ�嶨��
********************************************************
*/

/* �ڵ�ṹ�嶨�� */

struct xLIST_ITEM
{
    TickType_t xItemValve;                  // ����ֵ�����ڰ����ڵ���˳������
    struct xLIST_ITEM   * pxNext;           // ָ���������һ���ڵ�
    struct xLIST_ITEM   * pxPrevious;       // ָ�������ǰһ���ڵ�
    void * pvOwner;                         // ָ��ӵ�иýڵ���ں˶���ͨ����TCB(������ƿ�)
    void * pvContainer;                     // ָ��ýڵ����ڵ�����
};
typedef struct xLIST_ITEM           ListItem_t;      // �ڵ����������ض���

/* ������ڵ�ṹ�嶨�� */
struct xMINT_LIST_ITEM
{
    TickType_t xItemValue;                  // ����ֵ�����ڰ����ڵ�����������
    struct xLIST_ITEM   *   pxNext;         // ָ���������һ���ڵ�
    struct xLIST_ITEM   *   pxPrevious;     // ָ�������ǰһ���ڵ�
};
typedef struct xMINT_LIST_ITEM      MiniListItem_t; // ����ڵ����������ض���


/*������ڵ����ݽṹ����*/
typedef struct xLIST
{
    UBaseType_t     uxNumberOfItems;        // ����ڵ������
    ListItem_t  *   pxIndex;                // ����ڵ�����ָ��
    MiniListItem_t   xListEnd;              // �������һ���ڵ�
} List_t;


/** �ڵ����С���� **/

/* ��ʼ���ڵ��ӵ����*/
#define listSET_LIST_ITEM_OWNER( pxListItem, pxOwer ) 	(( pxListItem )->pvOwner == (void *) ( pxOwner ))

/* ��ȡ�ڵ�ӵ���� */
#define listGET_LIST_ITEM_OWNER( pxListItem ) 			(( pxListItem )->pvOwner )

/* ��ʼ���ڵ�������ֵ */
#define listSET_LIST_ITEM_VALUE( pxListItem, xValue ) 	(( pxListItem )->xItemValue = ( xvalue ))

/* ��ȡ�ڵ�����ֵ */
#define listGET_LIST_ITEM_VALUE( pxListItem )			(( pxListItem )->xItemValue )

/* ��ȡ������ڵ�Ľڵ��������ֵ */
#define listGET_ITEM_VALUE_OF_HEAD_ENTRY( pxList )		((( pxList )->xListEnd ).pxNext->xItemValue )

/* ��ȡ�������ڽڵ� */
#define listGET_HEAD_ENTRY( pxList )					((( pxList )->xListEnd ).pxNext)

/* ��ȡ����ĵ�һ���ڵ� */
#define listGET_NEXT( pxListItem )						(( pxList)->pxNext )

/* ��ȡ��������һ���ڵ�  */
#define listGET_END_MARKER( pxList ) 					(( ListItem_t const *) ( &(( pxList )-> xListEnd)))

/* �ж������Ƿ�Ϊ�� */
#define listGET_IS_EMPTY( pxList ) 						(( BaseType_t )(( pxList )->uxNumberOfItems == (UBaseType_t) 0 ))

/* ��ȡ����Ľڵ��� */
#define listCURRENT_LIST_LENGTH( pxList ) 				(( pxList )->uxNumberOfItems)

/* ��ȡ����ڵ��OWNER, ��TCB(������ƿ�) */
#define listGET_OWNER_OF_NEXT_ENTRY( pxTCB, pxList )				\
{																	\
	List_t * const pxConstList = ( pxList );						\
	/* �ڵ�����ָ�������һ���ڵ�����ڵ�����ִ����ָ����һ���ڵ�	
	 �����ǰ������N���ڵ㣬����N�ε��øú���ʱ��pxIndex��ָ���N���ڵ� */ \
	( pxConstList )->pxIndex = ( pxConstList )->pxIndex->pxNext;	
	/* ��ǰ����Ϊ�� */												\
	if(( void * )( pxConstList )->pxIndex == ( void * ) & (( pxConstList )->xListEnd )) \
	{																\
		
	}
}

#endif  /* __LIST_H_ */




