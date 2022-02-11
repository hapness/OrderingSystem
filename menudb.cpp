#include "dbconn.h"
#include "guanli.h"

void add_menu() {
	char name[20], remak[100];
	int price;
	MYSQL_BIND bind[3];
	memset(bind, 0, sizeof(bind));//��ʼ��Ϊ0
	char sql[60] = "insert into menu(mname,`describe`,price) values(?,?,?)";
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	printf("������Ҫ��ӵĲ�Ʒ���ƣ�");
	cin >> name;
	printf("������Ҫ��ӵĲ�Ʒ������");
	cin >> remak;
	printf("������Ҫ��ӵĲ�Ʒ�۸�");
	cin >> price;

	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = &name;
	bind[0].buffer_length = strlen(name);

	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer = &remak;
	bind[1].buffer_length = strlen(remak);

	bind[2].buffer_type = MYSQL_TYPE_LONG;
	bind[2].buffer = &price;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("��Ʒ��ӳɹ�\n");
		}
	}
	see_menu();
}

//ɾ����Ʒ��Ϣ
void del_menu() {
	int i = 0;
	MYSQL_BIND bind[1];//��������
	see_menu();
	char sql[50] = "DELETE from menu where id=?";
	memset(bind, 0, sizeof(bind));//��ʼ��Ϊ0
	mysql_stmt_prepare(stmt, sql, strlen(sql));

	bind[0].buffer_type = MYSQL_TYPE_LONG;//������������
	bind[0].buffer = &i;

	//see_menu();
	printf("������Ҫɾ���Ĳ�Ʒid");
	scanf_s("%d", &i);
	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("��Ʒɾ���ɹ�!\n");
		}//ִ�����
	}
}

//���²�Ʒ��Ϣ
void up_menu() {
	MYSQL_BIND bind[4];
	int id, price;
	char name[20], remak[50];//���ƣ��������۸�
	printf("�����������޸ĵ���Ʒid:");
	cin >> id;
	printf("�������µĲ�Ʒ���ƣ�������Ϣ���۸�:");
	cin >> name >> remak >> price;
	memset(bind, 0, sizeof(bind));//��ʼ��Ϊ0
	char sql[80] = "UPDATE menu set mname=?,`describe`=? ,price =? where id=?";
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = &name;
	bind[0].buffer_length = strlen(name);

	bind[1].buffer_type = MYSQL_TYPE_STRING;
	bind[1].buffer = &remak;
	bind[1].buffer_length = strlen(remak);

	bind[2].buffer_type = MYSQL_TYPE_LONG;
	bind[2].buffer = &price;

	bind[3].buffer_type = MYSQL_TYPE_LONG;
	bind[3].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("��Ʒ���³ɹ���\n");
		}
	}
	see_menu();
}

//�鿴��Ʒ��Ϣ
void see_menu() {
	printf("%-20s%-30s%-30s%-30s%-30s\n", "���", "id", "����", "���", "�۸�");
	mysql_query(&mysql, "SELECT * FROM menu");
	res_set = mysql_store_result(&mysql);
	int cnt = 0;
	while ((row = mysql_fetch_row(res_set)) != NULL) {
		cnt++;
		printf("%-20d", cnt);
		for (unsigned int i = 0; i < mysql_num_fields(res_set); i++) {
			printf("%-25s\t", row[i] != NULL ? row[i] : "NULL");
		}
		printf("\n");
	}
	system("pause");
	return;
}

int see_price(int mid) {
	MYSQL_STMT* st = mysql_stmt_init(&mysql);
	MYSQL_BIND bind[1];
	MYSQL_BIND result[2];

	memset(bind, 0, sizeof(bind));
	memset(result, 0, sizeof(result));
	char name[20] = "";
	int price = 0;
	char sql[40] = "select mname,price from menu where id=?";
	mysql_stmt_prepare(st, sql, strlen(sql));

	//�󶨲���
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &mid;

	if (!mysql_stmt_bind_param(st, bind)) {
		if (!mysql_stmt_execute(st)) {
			result[0].buffer_type = MYSQL_TYPE_STRING;
			result[0].buffer = &name;
			result[0].buffer_length = 20;

			result[1].buffer_type = MYSQL_TYPE_LONG;
			result[1].buffer = &price;
			
			mysql_stmt_bind_result(st, result);
			
			if (!mysql_stmt_store_result(st)) {
				while (!mysql_stmt_fetch(st)) {
					printf("%s\t\t%d��\n", name, price);
					return price;
				}
				printf("%s\n", mysql_stmt_error(st));
			}
			else printf("%s\n", mysql_stmt_error(st));
		}
	}
	else {
		printf("%s", mysql_stmt_error(st));
	}
	mysql_stmt_close(st);
	return 0;
}