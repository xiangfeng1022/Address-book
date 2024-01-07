#ifndef __ADDRESS_BOOK_H_
#define __ADDRESS_BOOK_H_

#define DEFAULT_NAME    20
#define DEFAULT_PHONE   12
#define DEFAULT_ADDRESS 30

/* 定义通讯录结构体 */
typedef struct contactNode
{
    char name[DEFAULT_NAME];
    char phone[DEFAULT_PHONE];
    char address[DEFAULT_ADDRESS];
    struct contactNode * next;
} contactNode;

typedef struct addressBook
{
    /* 头指针 */
    contactNode * head;
    /* 尾指针 */
    contactNode * tail;
    /* 通讯录大小 */
    int size;
} addressBook;


/* 通讯录的初始化 */
int addressBookInit(addressBook ** pTxl);

/* 通讯录中插入数据 */
int addressBookInsert(addressBook *pTxl, char *name, char *phone, char *address);

/* 通讯录中删除数据 */
<<<<<<< HEAD
int addressBookDelAppointVal(addressBook * pTxl, char * pVal);


/* 通讯录中查询指定的数据 */
int addressBookGetAppointVal(addressBook * pTxl, char *name, char *phone, char *address);
=======
int addressBookDelAppointVal(addressBook *pTxl);

/* 通讯录中查询指定的数据 */
int addressBookGetAppointVal(addressBook *pTxl);
>>>>>>> xf

/* 通讯录中修改指定的指定数据 */
int addressBookModify(addressBook *pTxl);

#endif //__ADDRESS_BOOK_H_