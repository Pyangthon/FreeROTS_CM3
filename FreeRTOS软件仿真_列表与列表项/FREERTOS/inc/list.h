
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

