#include <stdio.h>
#include "addressBook.h"
#include <string.h>
#include <stdlib.h>

/* 状态码 */
enum STATUS_CODE
{
    ON_SUCCESS,
    MALLOC_ERROR = -5,
    NULL_PTR,
    INVALID_ACCESS,
    EDIT_FAIL,
    NOT_FIND,
}; 



/* 判断传入指针是否正确 */
#define CHECK_PTR(ptr)          \
do {                            \
        if (!ptr)               \
        {                       \
            return NULL_PTR;    \
        }                       \
}while(0)


/* 判断分配空间是否正确 */
#define CHECK_MALLOC(ptr)    \
do                           \
{                            \
    if (!ptr)                \
    {                        \
        return MALLOC_ERROR; \
    }                        \
} while (0)

/* 静态函数前置声明 */
/* 删除指定位置的结点 */
static int delNodeAppointPos(addressBook * pTxl, int pos);
/* 根据指定的名字获取位置 */
static int addressBookGetPosAppointVal(addressBook * pTxl, char * pVal, int * pPos);
/* 找到指定phone所在的位置 */
static int addressBookGetAppointPhonePos(addressBook *pTxl, char *phone, int *pPos);
/* 找到指定address所在的位置 */
static int addressBookGetAppointAddressPos(addressBook *pTxl, char *address, int *pPos);

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

/* 根据指定的名字获取位置 */
int addressBookGetPosAppointVal(addressBook * pTxl, char * pVal, int * pPos)
{
    int val = *pVal;

    /* 从第一个结点开始遍历 */
    contactNode * travelNode = pTxl->head->next;
    int pos = 0;

    while (travelNode)
    {
        if (!strcmp(pVal, travelNode->name))
        {
            *pPos = pos + 1;
            return pos + 1;
        }
        travelNode = travelNode->next;
        pos++;
    }
    
    *pPos = -1;
    return NOT_FIND;
}

/* 删除指定位置的结点 */
static int delNodeAppointPos(addressBook * pTxl, int pos)
{
    if (pos <= 0 || pos > pTxl->size)
    {
        return INVALID_ACCESS;
    }

    contactNode * preNode = pTxl->head;

    /* 找到删除结点的前驱 */
    while (--pos)
    {
        preNode = preNode->next;
    }

    /* 删除结点是尾结点 */
    if (pos == pTxl->size)
    {
        pTxl->tail = preNode;
    }

    preNode->next = preNode->next->next;

    return ON_SUCCESS;
}

/* 通讯录中删除数据 */
int addressBookDelAppointVal(addressBook * pTxl, char * pVal)
{
    CHECK_PTR(pTxl);

    int pos = 0;

    return delNodeAppointPos(pTxl, addressBookGetPosAppointVal(pTxl, pVal, &pos));
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
/* 参数使用可选参数，达到选择输入的字符串是结构体中的那个信息，来达到选择查找的目的 */
int addressBookGetAppointVal(addressBook * pTxl, char *string, OPTION_PARAM OPTION_PARAM)
{
    int pos = 0;

    if(NAME)
    {
        char * name = string;
        contactNode *travelNode = pTxl->head;
        addressBookGetPosAppointVal(pTxl, name, &pos);

        if (pos <= 0)
        {
            printf("未找到您查询的联系人，请正确输入信息\n");
            return EDIT_FAIL;
        }

        while(pos--)
        {
            travelNode = travelNode->next;
        }
        printf("%s的address是: %s, phone是: %s\n", string, travelNode->address, travelNode->phone);
    }
    else if(PHONE)
    {
        char * phone = string;
        contactNode *travelNode = pTxl->head;
        addressBookGetAppointPhonePos(pTxl, phone, &pos);

        if (pos <= 0)
        {
            printf("未找到您查询的联系人，请正确输入信息\n");
            return EDIT_FAIL;
        }

        while(pos--)
        {
            travelNode = travelNode->next;
        }
        printf("%s的name是: %s, address是: %s\n", string, travelNode->name, travelNode->address);
    }
    else if(ADDRESS)
    {
        char * address = string;
        contactNode *travelNode = pTxl->head;
        addressBookGetAppointAddressPos(pTxl, address, &pos);

        /* 判断是否找到联系人 */
        if (pos <= 0)
        {
            printf("未找到您查询的联系人，请正确输入信息\n");
            return EDIT_FAIL;
        }

        while(pos--)
        {
            travelNode = travelNode->next;
        }
        printf("%s的name是: %s, phone是: %s\n", string, travelNode->name, travelNode->phone);
    }
    else
    {
        printf("没有找到\n");
        return EDIT_FAIL;
    }

    return ON_SUCCESS;
}



/* 通讯录中修改指定的指定数据 */
// int addressBookModify(addressBook * pTxl, char *name, char *phone, char *address)
// {
//     int pos = 0;
//     if(name)
//     {
//         contactNode *travelNode = pTxl->head;
//         addressBookGetPosAppointVal(pTxl, name, &pos);
//         while(--pos)
//         {
//             travelNode = travelNode->next;
//         }
//         strncpy(travelNode->name, name, strlen(name));
//     }
//     else if(phone)
//     {
//         contactNode *travelNode = pTxl->head;
//         addressBookGetAppointPhonePos(pTxl, phone, &pos);
//         while(--pos)
//         {
//             travelNode = travelNode->next;
//         }
//         strncpy(travelNode->phone, phone, strlen(phone));
//     }
//     else if(address)
//     {
//         contactNode *travelNode = pTxl->head;
//         addressBookGetAppointAddressPos(pTxl, address, &pos);
//         while(--pos)
//         {
//             travelNode = travelNode->next;
//         }
//         strncpy(travelNode->address, address, strlen(address));
//     }
//     else
//     {
//         printf("未填写有效的修改信息\n");
//         return EDIT_FAIL;
//     }
//     return ON_SUCCESS;
// }