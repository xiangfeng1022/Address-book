#ifndef __ADDRESS_BOOK_H_
#define __ADDRESS_BOOK_H_

#define DEFAULT_SIZE    30


/* 定义通讯录结构体 */
typedef struct contactNode
{
    char name[DEFAULT_SIZE];
    char phone[DEFAULT_SIZE];
    char address[DEFAULT_SIZE];
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

typedef enum OPTION_PARAM
{
    NAME = 1,
    ADDRESS,
    PHONE,
} OPTION_PARAM;

/* 通讯录的初始化 */
int addressBookInit(addressBook ** pTxl);

/* 通讯录中插入数据 */
int addressBookInsert(addressBook *pTxl, char *name, char *phone, char *address);

/* 通讯录中删除数据 */
int addressBookDelAppointVal(addressBook * pTxl, char * string, OPTION_PARAM OPTION_PARAM);

/* 通讯录中查询指定的数据 */
int addressBookGetAppointVal(addressBook * pTxl, char *string, OPTION_PARAM OPTION_PARAM);

/* 通讯录中修改指定的指定数据 */
int addressBookModify(addressBook * pTxl, char *string, char * modifyVal, OPTION_PARAM OPTION_PARAM);

/* 遍历接口 */
int addressBookForeach(addressBook * pTxl);

/* 将数据保存在文件中 */
int saveAddressBook(addressBook * pTxl);

#endif //__ADDRESS_BOOK_H_