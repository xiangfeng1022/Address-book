#include <stdio.h>
#include "addressBook.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define READ_BUFFER300  300
#define READ_SCANF30    30

/* 功能选择 */
enum USER_CHOICE
{
    INSERTE = 1,
    QUERY,
    MODIFY,
    DELETE
};

/* 查询的两种类型 */
enum USER_QUERY
{
    QUERY_ALL = 1,
    QUERY_APPOINT,
};

/* 查询依据 */
enum USER_QUERYBASIS
{
    QUERY_NAME = 1,
    QUERY_ADDRESS,
    QUERY_PHONE,
};

/* 修改的内容 */
enum MODIFY_BASIS
{
    M_NAME = 1,
    M_PHONE,
    M_ADDRESS,
};

int main()
{
    addressBook * book = NULL;

    addressBookInit(&book);

    /* 打开首页菜单 */
    int fd = open("./splashScreens", O_RDONLY);
    char buffer[READ_BUFFER300];
    memset(buffer, 0, sizeof(buffer));
    read(fd, buffer, sizeof(buffer) - 1);

    /* 打开选择页面 */
    int queryFd = open("./queryFunction", O_RDONLY);
    char queryBuffer[READ_BUFFER300];
    memset(queryBuffer, 0, sizeof(queryBuffer));
    read(queryFd, queryBuffer, sizeof(queryBuffer) - 1);

    /* 打开选择依据页面 */
    int basisFd = open("./queryBasis", O_RDONLY);
    char basisBuffer[READ_BUFFER300];
    memset(basisBuffer, 0, sizeof(basisBuffer));
    read(basisFd, basisBuffer, sizeof(basisBuffer) - 1);

    /* 打开修改信息页面 */
    int modifyFd = open("./modifyFunction", O_RDONLY);
    char modifyBuffer[READ_BUFFER300];
    memset(modifyBuffer, 0, sizeof(modifyBuffer));
    ssize_t bytes = read(modifyFd, modifyBuffer, sizeof(modifyBuffer) - 1);
    printf("bytes: %ld\n", bytes);

    /* 打开删除信息页面 */


    int choice = 0;
    int query = 0;
    int basis = 0;
    int modify = 0;
    char c = '0';
    char name[READ_SCANF30];
    memset(name, 0, sizeof(name));
    char phone[READ_SCANF30];
    memset(phone, 0, sizeof(phone));
    char address[READ_SCANF30];
    memset(address, 0, sizeof(address));
    char M_name[READ_SCANF30];
    memset(M_name, 0, sizeof(M_name));
    char M_phone[READ_SCANF30];
    memset(M_phone, 0, sizeof(M_phone));
    char M_address[READ_SCANF30];
    memset(M_address, 0, sizeof(M_address));

    while (1)
    {
        printf("%s\n", buffer);
        printf("请输入你需要的功能:\n");
        scanf("%d", &choice);
        while ((c = getchar()) != EOF && c != '\n');
        

        switch (choice)
        {
        /* 插入数据 */
        case INSERTE:
            printf("请输入要插入联系人的姓名：\n");
            scanf("%s", name);
            while ((c = getchar()) != EOF && c != '\n');
            printf("请输入要插入联系人的电话：\n");
            scanf("%s", phone);
            while ((c = getchar()) != EOF && c != '\n');
            printf("请输入要插入联系人的地址：\n");
            scanf("%s", address);
            while ((c = getchar()) != EOF && c != '\n');

            addressBookInsert(book, name, phone, address);
            break;
        
        /* 查询数据 */
        case QUERY:
            while (1)
            {
                printf("%s\n", queryBuffer);
                printf("请输入你需要查询的功能：\n");
                scanf("%d", &query);
                while ((c = getchar()) != EOF && c != '\n');

                /* 选择查询的方式:全部查询和单独查询 */
                switch (query)
                {
                /* 查找所有联系人 */
                case QUERY_ALL:
                    addressBookForeach(book);
                    break;
                
                case QUERY_APPOINT:
                    printf("%s\n", basisBuffer);
                    printf("请输入你想根据什么查询联系人:\n");
                    scanf("%d", &basis);
                    while ((c = getchar()) != EOF && c != '\n');
                    
                    /* 根据指定信息查找联系人 */
                    switch (basis)
                    {
                    case QUERY_NAME:
                        printf("请输入你想要查询的联系人姓名：\n");
                        scanf("%s", name);
                        while ((c = getchar()) != EOF && c != '\n');
                        addressBookGetAppointVal(book, name, NAME);  
                        break;

                    case QUERY_ADDRESS:
                        printf("请输入你想要查询的联系人的地址：\n");
                        scanf("%s", address);
                        while ((c = getchar()) != EOF && c != '\n');
                        addressBookGetAppointVal(book, address, ADDRESS);
                        break;
                    
                    case QUERY_PHONE:
                        printf("请输入你想要查询的联系人的电话号码：\n");
                        scanf("%s", phone);
                        while ((c = getchar()) != EOF && c != '\n');
                        addressBookGetAppointVal(book, phone, PHONE);
                        break;

                    default:
                        break;

                    }
                    break;

                default:
                    break;
                
                }
                if (query == 3)
                {
                    break;
                }
            }
            break;

        /* 选择修改功能 */
        case MODIFY:
            printf("%s\n",modifyBuffer);
            printf("请输入你想要修改的信息：\n");
            scanf("%d", &modify);
            while ((c = getchar()) != EOF && c != '\n');

            switch (modify)
            {
            case M_NAME:
                printf("请输入你想要修改的联系人原本姓名：\n");
                scanf("%s", name);
                while ((c = getchar()) != EOF && c != '\n');
                printf("请输入你想要修改的联系人姓名为：\n");
                scanf("%s", M_name);
                while ((c = getchar()) != EOF && c != '\n');
                addressBookModify(book, name, M_name, NAME);
                printf("修改成功！\n");
                break;

            case M_PHONE:
                printf("请输入你想要修改的联系人原本电话号码：\n");
                scanf("%s", phone);
                while ((c = getchar()) != EOF && c != '\n');
                printf("请输入你想要修改的联系人电话号码为：\n");
                scanf("%s", M_phone);
                while ((c = getchar()) != EOF && c != '\n');
                addressBookModify(book, phone, M_phone, PHONE);
                printf("修改成功！\n");
                break;

            case M_ADDRESS:
                printf("请输入你想要修改的联系人原本地址：\n");
                scanf("%s", address);
                while ((c = getchar()) != EOF && c != '\n');
                printf("请输入你想要修改的联系人地址为：\n");
                scanf("%s", M_address);
                while ((c = getchar()) != EOF && c != '\n');
                addressBookModify(book, address, M_address, ADDRESS);
                printf("修改成功！\n");
                break;
            
            default:
                break;
            }
            break;
            
        
        /* 选择删除功能 */
        case DELETE:
            printf("请输入你想要删除的联系人的姓名：\n");
            scanf("%s", name);
            while ((c = getchar()) != EOF && c != '\n');
            addressBookDelAppointVal(book, name, NAME);
            break;

        default:
            break;
        }

        /* 退出通讯录 */
        if (choice == 5)
        {
            break;
        }
    }

    close(fd);
    close(queryFd);
    close(basisFd);
    close(modifyFd);

    return 0;
}