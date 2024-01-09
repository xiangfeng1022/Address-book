#include <stdio.h>
#include "addressBook.h"

int main()
{
    addressBook * book = NULL;

    addressBookInit(&book);

    /* 插入数据 */
    addressBookInsert(book, "zhangsan", "200108192718", "sichuansheng");
    addressBookInsert(book, "lisi", "12345678", "sichuansheng");
    addressBookInsert(book, "wangwu", "20010818719", "henan");

    contactNode * travelNode = book->head->next;
    printf("name: %s, phone : %s, address : %s\n", travelNode->name, travelNode->phone, travelNode->address);
    travelNode = travelNode->next;
    printf("name: %s, phone : %s, address : %s\n", travelNode->name, travelNode->phone, travelNode->address);
    travelNode = travelNode->next;

    printf("name: %s, phone : %s, address : %s\n", travelNode->name, travelNode->phone, travelNode->address);

    printf("\n");


    /* 查询数据 */
    addressBookGetAppointVal(book, "zhangsan", NAME);
    addressBookGetAppointVal(book, "200108192718", PHONE);

    return 0;
}