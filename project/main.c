#include <stdio.h>
#include "addressBook.h"

int main()
{
    addressBook * book = NULL;

    addressBookInit(&book);

    /* 插入数据 */
    addressBookInsert(book, "张三", "200108192718", "四川省");
    addressBookInsert(book, "李四", "12345678", "四川省");
    addressBookInsert(book, "王五", "20010818719", "河南省");

    addressBookForeach(book);

    printf("\n");


    /* 查询数据 */
    addressBookGetAppointVal(book, "张三", NAME);
    addressBookGetAppointVal(book, "200108192718", PHONE);
    addressBookGetAppointVal(book, "四川省", ADDRESS);
    printf("\n");

    /* 删除数据 */
    // addressBookDelAppointVal(book, "四川省", NAME);


    /* 修改数据 */
    // addressBookModify(book, "张三", "李宁", NAME);
    // addressBookModify(book, "200108192718", "19146650217", PHONE);

    // travelNode = book->head->next;
    // printf("name: %s, phone : %s, address : %s\n", travelNode->name, travelNode->phone, travelNode->address);
    // printf("size: %d\n", book->size);


    return 0;
}