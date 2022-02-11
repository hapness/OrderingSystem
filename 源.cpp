#include"dbconn.h"
#include "menu.h"
using namespace std;
//菜单管理系统

int main() {
    int num;
    if (!conn()) {
        printf("数据库连接失败\n");
        return 0;
    }
    while (1)
    {
        printf("===========欢迎进入点餐系统===========\n");
        printf("1.点餐系统\n");
        printf("2.备餐系统\n");
        printf("3.管理系统\n");
        printf("4.系统设置\n");
        printf("0.退出系统\n");
		printf("请选者你要进行的操作（0-4）：");
        scanf_s("%d", &num);
        switch (num) {
        case 0://退出系统
            printf("退出成功，欢迎下次光临！\n");
            return 0;
        case 1://点餐系统
            buy();
            break;
        case 2://备餐系统
            oding();
            break;
        case 3://管理界面
            guanli();
            break;
        case 4://系统设置
            system();
            break;
        default:
            printf("该功能暂未开放，请重新输入！");
        }
    }
    
    gb();//关闭数据库连接
    return 0;
}
