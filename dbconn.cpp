#include "dbconn.h"
MYSQL mysql;//���Ӷ���
MYSQL_RES* res_set;//���������
MYSQL_ROW row;//�������浥�н��
MYSQL_STMT* stmt = mysql_stmt_init(&mysql);//Ԥ�������
//�������ݿ�
int conn() {
	mysql_init(&mysql);
	//�����ַ���
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	if (!mysql_real_connect(&mysql, "localhost", "root", "123456", "student", 3306, NULL, 0)) {
		printf("���Ӳ��ɹ���");
		return 0;
	}
	return 1;
}

//�ر����ӣ��ͷ��ڴ�
void gb() {
	//�ر�Ԥ�������
	mysql_stmt_close(stmt);
	mysql_free_result(res_set);
	mysql_close(&mysql);
}