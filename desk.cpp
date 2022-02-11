#include "dbconn.h"
#include "guanli.h"

void add_desk() {
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));//��ʼ��Ϊ0
	char sql[50] = "insert into desk(isok) values(?)";
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	int isok = 0;
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &isok;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("������ӳɹ���\n");
		}
	}
	see_desk();
}

void del_desk() {
	int i = 0;
	MYSQL_BIND bind[1];//��������
	see_desk();
	memset(bind, 0, sizeof(bind));//��ʼ��Ϊ0
	char sql[50] = "DELETE from desk where id=?";
	if (!mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		bind[0].buffer_type = MYSQL_TYPE_LONG;//������������
		bind[0].buffer = &i;

		//see_menu();
		printf("������Ҫɾ���Ĳ���id:");
		scanf_s("%d", &i);
		if (!mysql_stmt_bind_param(stmt, bind)) {
			if (!mysql_stmt_execute(stmt)) {
				printf("����ɾ���ɹ�!\n");
			}//ִ�����
		}
	}
}

void up_desk() {
	MYSQL_BIND bind[2];
	int id, newid;
	char name[20], remak[50];//���ƣ��������۸�
	printf("�����������޸ĵĲ���id:");
	cin >> id;
	printf("�����������id:");
	cin >> newid;
	memset(bind, 0, sizeof(bind));//��ʼ��Ϊ0
	char sql[80] = "UPDATE desk set id=? where id=?";
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &newid;

	bind[1].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("����id���ĳɹ���\n");
		}
	}
}

//�鿴����
void see_desk() {
	printf("%-20s%-30s%-30s\n", "���", "id", "�Ƿ����");
	mysql_query(&mysql, "SELECT * FROM desk");
	res_set = mysql_store_result(&mysql);
	int cnt = 0;
	while ((row = mysql_fetch_row(res_set)) != NULL) {
		cnt++;
		printf("%-20d", cnt);
		printf("%-30s\t", row[0] != NULL ? row[0] : "NULL");
		printf("%-30s\t", row[1] != NULL ? (strcmp(row[1],"1")==0 ? "��" : "��") : "NULL");
		printf("\n");
	}
	return;
}