#include "dbconn.h"
#include "oding.h"

//�鿴����
void see_oding(int num) {
	printf("���\t����id\t��Ʒid\t����id\t���\t��ע\t\t�ѽӵ�\t���\n");
	char sql[3][50] = {
		{"select * from `order` where yesno=0"},//�鿴δ���ն���
		{"select * from `order` where vis=0 and yesno=1"},//�鿴δ�����͵Ķ���
		{"select * from `order`"}//�鿴���ж���
	};
	//��ѯ���
	mysql_query(&mysql, sql[num]);
	res_set = mysql_store_result(&mysql);
	int cnt = 0;
	while ((row = mysql_fetch_row(res_set)) != NULL) {
		cnt++;
		printf("%d\t", cnt);
		for (unsigned int i = 0; i < mysql_num_fields(res_set); i++) {
			if(i<=4) printf("%s\t", row[i] != NULL ? row[i] : "NULL");
			else printf("%s\t", row[i] != NULL ? (strcmp(row[i], "0") == 0 ? "��" : "��") : "NULL");
			if (i == 4) printf("\t");
		}
		printf("\n");
	}
}
//������
void yesoding() {
	int id;
	system("cls");
	see_oding(1);
	printf("������Ҫ�����͵Ķ���id:");
	scanf_s("%d", &id);

	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	char sql[60] = "update `order` set vis=1 where id=? and vis=0 and yesno=1";
	mysql_stmt_prepare(stmt, sql, strlen(sql));

	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("��ͳɹ���\n");
				return;
			}
		}
	}

	printf("���ʧ�ܣ�û�иö�����\n");
	return;
}
//ȡ�����
void nooding() {
	int id;
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	system("cls");
	see_oding(2);
	printf("��ѡ��Ҫȡ����͵Ķ���id:\n");
	scanf_s("%d", &id);

	char sql[50] = "update `order` set vis=0 where id=? and vis=1";

	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("ȡ����ͳɹ���\n");
				return;
			}
		}
	}

	printf("ȡ�����ʧ�ܣ�û�иö����ඩ��δ��ͣ�\n");
	return;
}
//�޸Ķ�����Ϣ
void up_oding() {
	int id;
	char remak[30]="";
	system("cls");
	see_oding(2);
	printf("�������޸ĵĶ���id:");
	scanf_s("%d", &id);
	printf("�������޸ĺ�Ķ�����ע:");
	scanf_s("%s", remak,30);

	MYSQL_BIND bind[2];
	memset(bind, 0, sizeof(bind));
	char sql[60] = "update `order` set remak=? where id=?";
	mysql_stmt_prepare(stmt, sql, strlen(sql));

	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = &remak;
	bind[0].buffer_length = strlen(remak);

	bind[1].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("������Ϣ�޸ĳɹ���\n");
				return;
			}
		}
	}

	printf("������Ϣ�޸�ʧ�ܣ�\n");
	return;
}
//ɾ������
void del_oding() {
	int id;
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	system("cls");
	see_oding(2);
	printf("��ѡ��Ҫɾ���Ķ���id:\n");
	scanf_s("%d", &id);

	char sql[40] = "delete from `order` where id=?";

	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("����ɾ���ɹ���\n");
				return;
			}
		}
	}

	printf("����ɾ��ʧ�ܣ�û�иö�����\n");
	return;
}
//���ն���
void agree() {
	int id;
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	system("cls");
	see_oding(0);
	printf("��ѡ��Ҫ���յĶ���id:");
	scanf_s("%d", &id);

	char sql[50] = "update `order` set yesno=1 where id=? and yesno=0";

	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("���ն����ɹ���\n");
				return;
			}
		}
	}

	printf("��������ʧ�ܣ�û�иö������ѽӵ���\n");
	return;
}
//ͳ���Ѿ���ɵĶ����ܽ��
int qian() {
	int sum = 0;
	char sql[50] = "select total from `order` where vis=1";
	mysql_query(&mysql, sql);
	res_set = mysql_store_result(&mysql);

	while ((row = mysql_fetch_row(res_set)) != NULL) {
		sum += atoi(row[0]);
	}
	return sum;
}