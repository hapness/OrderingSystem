#include "dbconn.h"
#include "system.h"

void one() {
	system("cls");
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	char pwd[20];
	printf("�������µ�ϵͳ��������:");
	scanf_s("%s", pwd, 20);
	char sql[40] = "update users set pwd=? where power=1";
	
	mysql_stmt_prepare(stmt,sql,strlen(sql));

	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = &pwd;
	bind[0].buffer_length = strlen(pwd);

	mysql_stmt_bind_param(stmt, bind);
	if(!mysql_stmt_execute(stmt)){
		printf("����ϵͳ������³ɹ���\n");
	}
	system("pause");
}

void two() {
	system("cls");
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	char pwd[20];
	printf("�������µ�ϵͳ��������:");
	scanf_s("%s", pwd, 20);
	char sql[40] = "update users set pwd=? where power=2";

	mysql_stmt_prepare(stmt, sql, strlen(sql));

	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = &pwd;
	bind[0].buffer_length = strlen(pwd);

	mysql_stmt_bind_param(stmt, bind);
	if (!mysql_stmt_execute(stmt)) {
		printf("����ϵͳ������³ɹ���\n");
	}
	system("pause");
}

void tree() {
	system("cls");
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	char pwd[20];
	printf("�������µ�ϵͳ��������:");
	scanf_s("%s", pwd, 20);
	char sql[40] = "update users set pwd=? where power=0;";

	mysql_stmt_prepare(stmt, sql, strlen(sql));

	bind[0].buffer_type = MYSQL_TYPE_STRING;
	bind[0].buffer = &pwd;
	bind[0].buffer_length = strlen(pwd);

	mysql_stmt_bind_param(stmt, bind);
	if (!mysql_stmt_execute(stmt)) {
		printf("ϵͳ����������³ɹ���\n");
	}
	system("pause");
}