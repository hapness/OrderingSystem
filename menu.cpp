#include "dbconn.h"
#include "guanli.h"
#include "menu.h"
#include "system.h"
#include "buy.h"
#include "oding.h"
//int denglu();

int denglu(int num);
//����ϵͳ
void guanli() {
	if (denglu(2)) {
		system("cls");
		printf("=======��ӭ��������Աϵͳ=======\n");
		int num;
		while (true) {
			printf("1.�˵�����\n");
			printf("2.��������\n");
			printf("3.��������\n");
			printf("4.�鿴Ӫҵ��\n");
			printf("0.	����\n ");
			printf("��������Ҫ���еĲ���(0-3):");
			scanf_s("%d", &num);

			switch (num) {
			case 1://�˵�����
				menut();
				break;
			case 2://��������
				desk();
				break;
			case 3://��������
				dingdan();
				break;
			case 4://�鿴Ӫҵ��
				printf("�����Ӫҵ��Ϊ��%d��\n", qian());
				system("pause");
				break;
			case 0://����
				return ;
			default:
				printf("�������");
			}
			system("cls");
		}
	}
}

//ϵͳ����
void system(){
	if (denglu(0)) {
		system("cls");
		printf("======ϵͳ����======\n");
		while (1) {
			printf("1.�޸ı���ϵͳ����\n");
			printf("2.�޸Ĺ���ϵͳ����\n");
			printf("3.�޸�ϵͳ��������\n");
			printf("0.	����\n");

			int num;
			printf("��ѡ����Ҫ���еĲ�����0-3����");
			scanf_s("%d", &num);

			switch (num) {
			case 1:
				one();
				break;
			case 2:
				two();
				break;
			case 3:
				tree();
				break;
			case 0:
				return;
			default:
				printf("�������\n");
			}
			system("cls");
		}
	}
}

//����ϵͳ
void oding(){
	if (denglu(1)) {
		system("cls");
		printf("=======��ӭ��������ϵͳ=======\n");
		int num;
		while (true) {
			printf("1.���ն���\n");
			printf("2.ȡ�����\n");
			printf("3.����\n");
			printf("��ѡ����Ҫ���еĲ�����0-3����");
			scanf_s("%d", &num);
			switch (num) {
			case 1:
				agree();
				break;
			case 2:
				nooding();
				break;
			case 3:
				yesoding();
				break;
			case 0:
				return;
			default:
				printf("û�иù��ܣ��������");
			}
			system("cls");
		}
	}
}

//���ϵͳ
void buy() {
	system("cls");
	printf("========��ӭ�������ϵͳ========\n");

	char isok;
	int id=dian();
	printf("�Ƿ�鿴�˵�(y/n):");
	getchar();
	scanf_s("%c", &isok,(int)sizeof(char));

	if (isok == 'y') {
		printf("�˵����£�\n");
		mony(id);
	}
}

int denglu(int num) {
	my_bool	is_null[4];
	unsigned long length[4];
	MYSQL_BIND bind[3];
	MYSQL_BIND result[4];//��������
	int id=0, power=0;
	char name[20]="", password[20]="";//���淵�ص��ĸ�����
	memset(result, 0, sizeof(result));//��ʼ��Ϊ0
	memset(bind, 0, sizeof(bind));//��ʼ��Ϊ0
	char username[20];
	char pwd[20];
	char sql[71] = "SELECT * FROM users WHERE power=? and name=? and pwd=?";
	printf("����������û�����");
	scanf_s("%s", username, 20);
	printf("������������룺");
	scanf_s("%s", pwd, 20);
	if (!mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		bind[0].buffer_type = MYSQL_TYPE_LONG;
		bind[0].buffer = &num;

		bind[1].buffer_type = MYSQL_TYPE_STRING;
		bind[1].buffer = &username;
		bind[1].buffer_length = strlen(username);

		bind[2].buffer_type = MYSQL_TYPE_STRING;
		bind[2].buffer = &pwd;
		bind[2].buffer_length = strlen(pwd);

		if (!mysql_stmt_bind_param(stmt, bind)) {
			if (!mysql_stmt_execute(stmt)) {
				result[0].buffer_type = MYSQL_TYPE_LONG;
				result[0].buffer = &id;
				result[0].is_null = &is_null[0];
				result[0].length = &length[0];

				result[1].buffer_type = MYSQL_TYPE_STRING;
				result[1].buffer = &name;
				result[1].buffer_length = 50;
				result[1].is_null = &is_null[1];
				result[1].length = &length[1];

				result[2].buffer_type = MYSQL_TYPE_STRING;
				result[2].buffer = &password;
				result[2].buffer_length = 50;
				result[2].is_null = &is_null[2];
				result[2].length = &length[2];

				result[3].buffer_type = MYSQL_TYPE_LONG;
				result[3].buffer = &power;
				result[3].is_null = &is_null[3];
				result[3].length = &length[3];

				if (!mysql_stmt_bind_result(stmt, result)) {
					if (!mysql_stmt_store_result(stmt)) {
						while (!mysql_stmt_fetch(stmt)) {
							if (is_null[0] && is_null[1] && is_null[2] && is_null[3]) {
								cout << "null" << endl;
							}
							return 1;
						}
					}
				}

			}
			else {
				cout << mysql_stmt_errno(stmt) << " " << mysql_stmt_error(stmt) << endl;
			}
		}
	}
	else {
		cout << mysql_stmt_errno(stmt)<<" " << mysql_stmt_error(stmt)<<endl;
	}//�����
	printf("�˺Ż��������\n");
	system("pause");
	return 0;
}