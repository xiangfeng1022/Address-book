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
};

/* 判断传入指针是否正确 */
#define CHECK_PTR(ptr)       \
    do                       \
    {                        \
        if (!ptr)            \
        {                    \
            \       
            return NULL_PTR; \
        }                    \
    } while (0)

/* 判断分配空间是否正确 */
#define CHECK_MALLOC(ptr)        \
    do                           \
    {                            \
        if (!ptr)                \
        {                        \
            \       
            return MALLOC_ERROR; \
        }                        \
    } while (0)

/* 通讯录的初始化 */
int addressBookInit(addressBook **pTxl)
{
    addressBook *txl = (addressBook *)malloc(sizeof(addressBook) * 1);
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
int addressBookInsert(addressBook *pTxl, char *name, char *phone, char *address)
{
    CHECK_PTR(pTxl);
    contactNode *newNode = (contactNode *)malloc(sizeof(contactNode) * 1);
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    memset(newNode, 0, sizeof(contactNode) * 1);

    strncpy(newNode->name, name, DEFAULT_NAME - 1);
    newNode->name[DEFAULT_NAME - 1] = '\0';

    strncpy(newNode->phone, phone, DEFAULT_PHONE - 1);
    newNode->name[DEFAULT_PHONE - 1] = '\0';

    strncpy(newNode->address, address, DEFAULT_ADDRESS - 1);
    newNode->name[DEFAULT_ADDRESS - 1] = '\0';
    
    pTxl->tail->next = newNode;
    pTxl->tail = newNode;
    
    (pTxl->size)++;
    
}

/* 通讯录中删除数据 */
int addressBookDelAppointVal(addressBook *pTxl)
{
}

/* 通讯录中查询指定的数据 */
int addressBookGetAppointVal(addressBook *pTxl)
{
}

/* 通讯录中修改指定的指定数据 */
int addressBookModify(addressBook *pTxl)
{
}