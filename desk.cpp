#include "dbconn.h"
#include "guanli.h"

void add_desk() {
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));//初始化为0
	char sql[50] = "insert into desk(isok) values(?)";
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	int isok = 0;
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &isok;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("餐桌添加成功！\n");
		}
	}
	see_desk();
}

void del_desk() {
	int i = 0;
	MYSQL_BIND bind[1];//参数数据
	see_desk();
	memset(bind, 0, sizeof(bind));//初始化为0
	char sql[50] = "DELETE from desk where id=?";
	if (!mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		bind[0].buffer_type = MYSQL_TYPE_LONG;//参数数据类型
		bind[0].buffer = &i;

		//see_menu();
		printf("请输入要删除的餐桌id:");
		scanf_s("%d", &i);
		if (!mysql_stmt_bind_param(stmt, bind)) {
			if (!mysql_stmt_execute(stmt)) {
				printf("餐桌删除成功!\n");
			}//执行语句
		}
	}
}

void up_desk() {
	MYSQL_BIND bind[2];
	int id, newid;
	char name[20], remak[50];//名称，描述，价格
	printf("请输入你想修改的餐桌id:");
	cin >> id;
	printf("请输入餐桌新id:");
	cin >> newid;
	memset(bind, 0, sizeof(bind));//初始化为0
	char sql[80] = "UPDATE desk set id=? where id=?";
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &newid;

	bind[1].buffer_type = MYSQL_TYPE_LONG;
	bind[1].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("餐桌id更改成功！\n");
		}
	}
}

//查看餐桌
void see_desk() {
	printf("%-20s%-30s%-30s\n", "序号", "id", "是否可用");
	mysql_query(&mysql, "SELECT * FROM desk");
	res_set = mysql_store_result(&mysql);
	int cnt = 0;
	while ((row = mysql_fetch_row(res_set)) != NULL) {
		cnt++;
		printf("%-20d", cnt);
		printf("%-30s\t", row[0] != NULL ? row[0] : "NULL");
		printf("%-30s\t", row[1] != NULL ? (strcmp(row[1],"1")==0 ? "否" : "是") : "NULL");
		printf("\n");
	}
	return;
}