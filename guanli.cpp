#include "dbconn.h"
#include "guanli.h"
#include "oding.h"
void menut() {
	while (true) {
		system("cls");
		printf("1.��Ӳ˵�\n");
		printf("2.ɾ���˵�\n");
		printf("3.�޸Ĳ˵�\n");
		printf("4.�鿴�˵�\n");
		printf("0.����\n");
		int num;
		printf("��������Ҫ���еĲ�����1-4:��");
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
			printf("û�иù��ܣ�\n");
		}
		system("pause");
		system("cls");
	}
}


void desk() {
	while (true) {
		printf("1.��Ӳ���\n");
		printf("2.�޸Ĳ���\n");
		printf("3.ɾ������\n");
		printf("4.�鿴����\n");
		printf("0.����\n");
		int num;
		printf("��������Ҫ���еĲ�����1-4:��");
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
			printf("û�иù��ܣ�\n");
		}
		system("pause");
		system("cls");
	}
}
//��������
void dingdan() {
	while (true) {
		printf("1.ȡ������\n");
		printf("2.�޸Ķ���\n");
		printf("3.�鿴����\n");
		printf("0.����\n");
		int num;
		printf("��������Ҫ���еĲ�����0-3:��");
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
			printf("û�иù��ܣ�\n");
		}
		system("pause");
		system("cls");
	}
	
}