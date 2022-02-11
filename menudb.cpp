#include "dbconn.h"
#include "guanli.h"

void add_menu() {
	char name[20], remak[100];
	int price;
	MYSQL_BIND bind[3];
	memset(bind, 0, sizeof(bind));//初始化为0
	char sql[60] = "insert into menu(mname,`describe`,price) values(?,?,?)";
	mysql_stmt_prepare(stmt, sql, strlen(sql));
	printf("请输入要添加的菜品名称：");
	cin >> name;
	printf("请输入要添加的菜品描述：");
	cin >> remak;
	printf("请输入要添加的菜品价格：");
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
			printf("菜品添加成功\n");
		}
	}
	see_menu();
}

//删除菜品信息
void del_menu() {
	int i = 0;
	MYSQL_BIND bind[1];//参数数据
	see_menu();
	char sql[50] = "DELETE from menu where id=?";
	memset(bind, 0, sizeof(bind));//初始化为0
	mysql_stmt_prepare(stmt, sql, strlen(sql));

	bind[0].buffer_type = MYSQL_TYPE_LONG;//参数数据类型
	bind[0].buffer = &i;

	//see_menu();
	printf("请输入要删除的菜品id");
	scanf_s("%d", &i);
	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			printf("菜品删除成功!\n");
		}//执行语句
	}
}

//更新菜品信息
void up_menu() {
	MYSQL_BIND bind[4];
	int id, price;
	char name[20], remak[50];//名称，描述，价格
	printf("请输入你想修改的商品id:");
	cin >> id;
	printf("请输入新的菜品名称，描述信息，价格:");
	cin >> name >> remak >> price;
	memset(bind, 0, sizeof(bind));//初始化为0
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
			printf("菜品更新成功！\n");
		}
	}
	see_menu();
}

//查看菜品信息
void see_menu() {
	printf("%-20s%-30s%-30s%-30s%-30s\n", "序号", "id", "菜名", "简介", "价格");
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

	//绑定参数
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
					printf("%s\t\t%d￥\n", name, price);
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