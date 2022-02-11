#include "dbconn.h"
MYSQL mysql;//连接对象
MYSQL_RES* res_set;//结果集对象
MYSQL_ROW row;//用来保存单行结果
MYSQL_STMT* stmt = mysql_stmt_init(&mysql);//预处理语句
//连接数据库
int conn() {
	mysql_init(&mysql);
	//设置字符集
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	if (!mysql_real_connect(&mysql, "localhost", "root", "123456", "student", 3306, NULL, 0)) {
		printf("连接不成功！");
		return 0;
	}
	return 1;
}

//关闭连接，释放内存
void gb() {
	//关闭预处理语句
	mysql_stmt_close(stmt);
	mysql_free_result(res_set);
	mysql_close(&mysql);
}