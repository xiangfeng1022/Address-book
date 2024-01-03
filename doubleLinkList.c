#include "doubleLinkList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
    NOT_FIND,
};

static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList * pList, ELEMENTTYPE val, int * pPos);
static DoubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val);

/* 链表初始化 */
int DoubleLinkListInit(DoubleLinkList ** pList)
{
    DoubleLinkList * list = (DoubleLinkList *)malloc(sizeof(DoubleLinkList) * 1);
    if(!list)
    {
        return MALLOC_ERROR;
    }
    /* 清空脏数据 */
    memset(list, 0, sizeof(DoubleLinkList) * 1);

    list->head = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if(!list->head)
    {
        return MALLOC_ERROR;
    }
    memset(list->head, 0, sizeof(DoubleLinkNode) * 1);

    /* 初始化链表的长度和尾指针 */
    list->len = 0;
    list->tail = list->head;

    /* 初始化头节点 */
    list->head->data = 0;
    list->head->next = NULL;
    list->head->prev = NULL;

    *pList = list;

    return ON_SUCCESS;
}

/* 链表头插 */
int DoubleLinkListHeadInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, 0, val);
}

/* 链表尾插 */
int DoubleLinkListTailInsert(DoubleLinkList * pList, ELEMENTTYPE val)
{
    return DoubleLinkListAppointPosInsert(pList, pList->len, val);
}

/* 创建新节点封装成函数 */
static DoubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val)
{
    DoubleLinkNode * newNode = (DoubleLinkNode *)malloc(sizeof(DoubleLinkNode) * 1);
    if(!newNode)
    {
        return NULL;
    }
    memset(newNode, 0, sizeof(DoubleLinkNode) * 1);
    newNode->data = 0;
    newNode->next = NULL;
    newNode->prev = NULL;

    /* 赋值 */
    newNode->data = val;

    return newNode;
}

/* 链表指定位置插入 */
int DoubleLinkListAppointPosInsert(DoubleLinkList * pList,int pos, ELEMENTTYPE val)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 创建新节点封装成函数 */
    DoubleLinkNode * newNode = createDoubleLinkNode(val);
    if(!newNode)
    {
        return MALLOC_ERROR;
    }

    /* 从头结点开始遍历 */
    DoubleLinkNode * travel = pList->head;

    /* 改变尾指针的情况 */
    int flag = 0;
    if(pos == pList->len)
    {
        travel = pList->tail;
        flag = 1;
    }
    else
    {
        while(pos)
        {
            travel = travel->next;
            pos--;
        }
        
        travel->next->prev = newNode;
    }
    /* 执行插入操作 */
    newNode->next = travel->next;
    newNode->prev = travel;
    travel->next = newNode;

    if(flag)
    {
        pList->tail = newNode;
    }

    /* 更新链表数据 */
    pList->len++;

    return ON_SUCCESS;
}

/* 链表头删 */
int DoubleLinkListHeadDel(DoubleLinkList * pList)
{
    return DoubleLinkListAppointPosDel(pList, 1);
}

/* 链表尾删 */
int DoubleLinkListTailDel(DoubleLinkList * pList)
{
    return DoubleLinkListAppointPosDel(pList, pList->len);
}

/* 链表指定位置删除 */
int DoubleLinkListAppointPosDel(DoubleLinkList * pList, int pos)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    if(pos <= 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 从头结点开始遍历 */
    DoubleLinkNode * travel = pList->head;
    DoubleLinkNode * needDelNode = NULL;

    int flag = 0;
    if(pos == pList->len)
    {
        flag = 1;
        travel = pList->tail->prev;
        needDelNode = travel->next;
    }
    else
    {
        while(--pos)
        {
            travel = travel->next;
        }
        needDelNode = travel->next;
        needDelNode->next->prev = travel;
    }

    travel->next = needDelNode->next;
    

    /* 删除了表尾结点的时候需要移动尾指针 */
    if(flag)
    {
        pList->tail = travel;
    }

    /* 释放内存 */
    if(needDelNode)
    {
        free(needDelNode);
        needDelNode = NULL;
    }
    

    /* 更新链表信息 */
    pList->len--;

    return ON_SUCCESS;
}

/* 根据指定元素得到元素在链表中所在位置 */
static int DoubleLinkListAccordAppointValGetPos(DoubleLinkList * pList, ELEMENTTYPE val, int * pPos)
{
    /* 从头结点开始遍历 */
    DoubleLinkNode * travelNode = pList->head;

    int pos = 0;

    while(travelNode->next)
    {
        if(travelNode->next->data == val)
        {
            pos++;
            *pPos = pos;
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }

    *pPos = NOT_FIND;

    return NOT_FIND;
}

/* 链表删除指定元素 */
int DoubleLinkListDelAppointVal(DoubleLinkList * pList, ELEMENTTYPE val)
{
    int pos = 0;
    int size = 0;

    while(pos != NOT_FIND)
    {
        DoubleLinkListAppointPosDel(pList, DoubleLinkListAccordAppointValGetPos(pList, val, &pos));
    }

    return ON_SUCCESS;
}

/* 获取链表长度 */
int DoubleLinkListGetLen(DoubleLinkList * pList, int * pSize)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    if(pSize)
    {
        *pSize = pList->len;
    }

    /* 返回链表长度 */
    return pList->len;
}

/* 销毁链表 */
int DoubleLinkListDestory(DoubleLinkList * pList)
{
    /* 使用头删销毁链表 */
    int size = 0;
    while(DoubleLinkListGetLen(pList, &size))
    {
        DoubleLinkListHeadDel(pList);
    }

    /* 删除头节点，并将头指针和尾指针都置空 */
    if(pList->head)
    {
        free(pList->head);
        pList->head = NULL;
        pList->tail = NULL;
    }

    return ON_SUCCESS;
}

/* 链表的遍历 */
int DoubleLinkListForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE))
{
    if(!pList)
    {
        return NULL_PTR;
    }

    /* 从头结点开始遍历 */
    DoubleLinkNode * travel = pList->head;

    /* 结束条件：下一个结点的指针域为空，即来到了表尾结点 */
    while(travel->next != NULL)
    {
        travel = travel->next;
#if 0
        travel = travel->next;
        printf("trave->data:%d\n", travel->data);
#else
        /* 包装器即回调函数 */
        printFunc(travel->data);
#endif
    }

    return ON_SUCCESS;
}

/* 链表逆序打印 */
int DoubleLinkListReverseForeach(DoubleLinkList * pList, int (*printFunc)(ELEMENTTYPE))
{
    if(!pList)
    {
        return NULL_PTR;
    }

    /* 从尾节点开始遍历 */
    DoubleLinkNode * travel = pList->tail;

    /* 结束条件：头结点的指针域为空，即来到了表尾结点 */
    while(travel->prev)
    {
        /* 包装器即回调函数 */
        printFunc(travel->data);
        travel = travel->prev;

    }

    return ON_SUCCESS;
}

/* 获取链表指定位置的元素 */
int DoubleLinkListGetAppointPosVal(DoubleLinkList * pList, int pos, ELEMENTTYPE * val)
{
    if(!pList)
    {
        return NULL_PTR;
    }

    if(pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }

    /* 从头指针开始遍历 */
    DoubleLinkNode * travelNode = pList->head;
    while(pos--)
    {
        travelNode = travelNode->next;
    }

    *val = travelNode->data;

    return ON_SUCCESS;
}
