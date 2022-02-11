#include "dbconn.h"
#include "guanli.h"
#include "oding.h"
void menut() {
	while (true) {
		system("cls");
		printf("1.添加菜单\n");
		printf("2.删除菜单\n");
		printf("3.修改菜单\n");
		printf("4.查看菜单\n");
		printf("0.返回\n");
		int num;
		printf("请输入你要进行的操作（1-4:）");
		scanf_s("%d", &num);

		switch (num) {
		case 1:
			add_menu();
			break;
		case 2:
			del_menu();
			break;
		case 3:
			up_menu();
			break;
		case 4:
			see_menu();
			break;
		case 0:
			return;
		default:
			printf("没有该功能！\n");
		}
		system("pause");
		system("cls");
	}
}


void desk() {
	while (true) {
		printf("1.添加餐桌\n");
		printf("2.修改餐桌\n");
		printf("3.删除餐桌\n");
		printf("4.查看餐桌\n");
		printf("0.返回\n");
		int num;
		printf("请输入你要进行的操作（1-4:）");
		scanf_s("%d", &num);
		switch (num) {
		case 1:
			add_desk();
			break;
		case 2:
			up_desk();
			break;
		case 3:
			del_desk();
			break;
		case 4:
			see_desk();
			break;
		case 0:
			return;
		default:
			printf("没有该功能！\n");
		}
		system("pause");
		system("cls");
	}
}
//订单管理
void dingdan() {
	while (true) {
		printf("1.取消订单\n");
		printf("2.修改订单\n");
		printf("3.查看订单\n");
		printf("0.返回\n");
		int num;
		printf("请输入你要进行的操作（0-3:）");
		scanf_s("%d", &num);

		switch (num) {
		case 1:
			del_oding();
			break;
		case 2:
			up_oding();
			break;
		case 3:
			see_oding(2);
			break;
		case 0:
			return;
		default:
			printf("没有该功能！\n");
		}
		system("pause");
		system("cls");
	}
	
}