#ifndef __ADDRESS_BOOK_H_
#define __ADDRESS_BOOK_H_

#define DEFAULT_NAME    20
#define DEFAULT_PHONE   12
#define DEFAULT_ADDRESS 30
#define DEFAULT_CONTANT 30

/* 定义通讯录结构体 */
typedef struct contact
{
    char name[DEFAULT_NAME];
    char phone[DEFAULT_PHONE];
    char address[DEFAULT_ADDRESS];
} contact;

typedef struct addressBook
{
    contact contacts[DEFAULT_CONTANT];
    int size;
} addressBook;


/* 通讯录的初始化 */
int addressBookInit(addressBook ** pTxl);

/* 通讯录中插入数据 */
int addressBookInsert(addressBook ** pTxl);

/* 通讯录中删除数据 */
int addressBookDelAppointVal(addressBook ** pTxl);

/* 通讯录中查询指定的数据 */
int addressBookGetAppointVal(addressBook ** pTxl);

/* 通讯录中修改指定的指定数据 */
int addressBookModify(addressBook ** pTxl);

#endif //__ADDRESS_BOOK_H_