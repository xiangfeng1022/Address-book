#include <stdio.h>
#include "addressBook.h"
#include <string.h>
#include <stdlib.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR,
    NULL_PTR,
    INVALID_ACCESS,
    NOT_FIND,
    EDIT_FAIL,
}; 

/* 判断传入指针是否正确 */
#define CHECK_PTR(ptr)          \
do {                            \
        if (!ptr){              \       
            return NULL_PTR;    \
        }                       \
}while(0)


/* 判断分配空间是否正确 */
#define CHECK_MALLOC(ptr)            \
do {                                 \
        if (!ptr){                   \       
            return MALLOC_ERROR;     \
        }                            \
}while(0)


/* 通讯录的初始化 */
int addressBookInit(addressBook ** pTxl)
{
    addressBook * txl = (addressBook *)malloc(sizeof(addressBook) * 1);
    CHECK_MALLOC(txl);
    memset(txl, 0, sizeof(addressBook) * 1);
    txl->size = 0;
    
    /* 为头结点分配空间 */
    txl->head = (contactNode *)malloc(sizeof(contactNode) * 1);
    CHECK_MALLOC(txl->head);
    memset(txl->head, 0, sizeof(contactNode) * 1);

    txl->tail = txl->head;

    *pTxl = txl;

    return ON_SUCCESS;
}

/* 通讯录中插入数据 */
int addressBookInsert(addressBook ** pTxl)
{

}

/* 通讯录中删除数据 */
int addressBookDelAppointVal(addressBook ** pTxl)
{

}


/* 找到指定name所在的位置 */   
static int addressBookGetAppointNamePos(addressBook *pTxl, char *name, int *pPos)
{
    int pos = 0;
    /* 构建遍历结点 */
    contactNode *travelNode = pTxl->head;

    int cmp = 0;
    /* 从头遍历找到指定的name */
    while(travelNode)
    {
        cmp = strcmp(name, travelNode->name);
        if(cmp == 0)
        {
            /* 解引用 */
            *pPos = pos;
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }
    /* 解引用 */  
    *pPos = -1;
    return NOT_FIND;
}

/* 找到指定phone所在的位置 */
static int addressBookGetAppointPhonePos(addressBook *pTxl, char *phone, int *pPos)
{
    int pos = 0;
    /* 构建遍历结点 */
    contactNode *travelNode = pTxl->head;

    int cmp = 0;
    /* 从头遍历找到指定的name */
    while(travelNode)
    {
        cmp = strcmp(phone, travelNode->phone);
        if(cmp == 0)
        {
            /* 解引用 */
            *pPos = pos;
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }
    /* 解引用 */  
    *pPos = -1;
    return NOT_FIND;
}

/* 找到指定address所在的位置 */
static int addressBookGetAppointAddressPos(addressBook *pTxl, char *address, int *pPos)
{
    int pos = 0;
    /* 构建遍历结点 */
    contactNode *travelNode = pTxl->head;

    int cmp = 0;
    /* 从头遍历找到指定的name */
    while(travelNode)
    {
        cmp = strcmp(address, travelNode->address);
        if(cmp == 0)
        {
            /* 解引用 */
            *pPos = pos;
            return pos;
        }
        travelNode = travelNode->next;
        pos++;
    }
    /* 解引用 */  
    *pPos = -1;
    return NOT_FIND;
}

/* 通讯录中查询指定的数据 */
int addressBookGetAppointVal(addressBook * pTxl, char *name, char *phone, char *address)
{
    int pos = 0;
    if(name)
    {
        contactNode *travelNode = pTxl->head;
        addressBookGetAppointNamePos(pTxl, name, pos);
    }
    else if(phone)
    {
        contactNode *travelNode = pTxl->head;
        addressBookGetAppointNamePos(pTxl, phone, pos);
    }
    else if(address)
    {
        contactNode *travelNode = pTxl->head;
        addressBookGetAppointNamePos(pTxl, address, pos);
    }
    else
    {
        printf("没有找到\n");
        return EDIT_FAIL;
    }
    return ON_SUCCESS;
}



/* 通讯录中修改指定的指定数据 */
int addressBookModify(addressBook ** pTxl)
{

}