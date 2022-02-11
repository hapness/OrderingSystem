#include "dbconn.h"
#include "oding.h"

//查看订单
void see_oding(int num) {
	printf("序号\t订单id\t菜品id\t餐桌id\t金额\t备注\t\t已接单\t完成\n");
	char sql[3][50] = {
		{"select * from `order` where yesno=0"},//查看未接收订单
		{"select * from `order` where vis=0 and yesno=1"},//查看未完成配餐的订单
		{"select * from `order`"}//查看所有订单
	};
	//查询语句
	mysql_query(&mysql, sql[num]);
	res_set = mysql_store_result(&mysql);
	int cnt = 0;
	while ((row = mysql_fetch_row(res_set)) != NULL) {
		cnt++;
		printf("%d\t", cnt);
		for (unsigned int i = 0; i < mysql_num_fields(res_set); i++) {
			if(i<=4) printf("%s\t", row[i] != NULL ? row[i] : "NULL");
			else printf("%s\t", row[i] != NULL ? (strcmp(row[i], "0") == 0 ? "否" : "是") : "NULL");
			if (i == 4) printf("\t");
		}
		printf("\n");
	}
}
//完成配餐
void yesoding() {
	int id;
	system("cls");
	see_oding(1);
	printf("请输入要完成配餐的订单id:");
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
				printf("配餐成功！\n");
				return;
			}
		}
	}

	printf("配餐失败，没有该订单！\n");
	return;
}
//取消配餐
void nooding() {
	int id;
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	system("cls");
	see_oding(2);
	printf("请选择要取消配餐的订单id:\n");
	scanf_s("%d", &id);

	char sql[50] = "update `order` set vis=0 where id=? and vis=1";

	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("取消配餐成功！\n");
				return;
			}
		}
	}

	printf("取消配餐失败，没有该订单多订单未配餐！\n");
	return;
}
//修改订单信息
void up_oding() {
	int id;
	char remak[30]="";
	system("cls");
	see_oding(2);
	printf("请输入修改的订单id:");
	scanf_s("%d", &id);
	printf("请输入修改后的订单备注:");
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
				printf("订单信息修改成功！\n");
				return;
			}
		}
	}

	printf("订单信息修改失败！\n");
	return;
}
//删除订单
void del_oding() {
	int id;
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	system("cls");
	see_oding(2);
	printf("请选择要删除的订单id:\n");
	scanf_s("%d", &id);

	char sql[40] = "delete from `order` where id=?";

	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("订单删除成功！\n");
				return;
			}
		}
	}

	printf("订单删除失败，没有该订单！\n");
	return;
}
//接收订单
void agree() {
	int id;
	MYSQL_BIND bind[1];
	memset(bind, 0, sizeof(bind));
	system("cls");
	see_oding(0);
	printf("请选择要接收的订单id:");
	scanf_s("%d", &id);

	char sql[50] = "update `order` set yesno=1 where id=? and yesno=0";

	mysql_stmt_prepare(stmt, sql, strlen(sql));
	bind[0].buffer_type = MYSQL_TYPE_LONG;
	bind[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, bind)) {
		if (!mysql_stmt_execute(stmt)) {
			int cnt = mysql_stmt_affected_rows(stmt);
			if (cnt > 0) {
				printf("接收订单成功！\n");
				return;
			}
		}
	}

	printf("订单接收失败，没有该订单或已接单！\n");
	return;
}
//统计已经完成的订单总金额
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