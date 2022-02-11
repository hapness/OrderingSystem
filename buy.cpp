#include "dbconn.h"
#include "buy.h"
#include "guanli.h"

void neworder(int id, int eat);
//点餐
int dian() {
	int id, eat;
	char isok;
	printf("请选择餐桌:");
	scanf_s("%d", &id);
	see_menu();
	
	while (true) {
		printf("请选择菜品id:");
		scanf_s("%d", &eat);
		neworder(id,eat);
		printf("是否继续点餐（y/n）:\n");

		getchar();
		scanf_s("%c", &isok,2);
		if (isok != 'y') {
			break;
		}
	}
	return id;
}

void neworder(int id,int eat) {
	MYSQL_BIND bind[6];
	MYSQL_BIND b[1];
	MYSQL_BIND rs[1];
	char remak[30];
	int vis = 0,total=0,yesno=0;//表示没有配餐的订单状态
	memset(bind, 0, sizeof(bind));
	memset(rs, 0, sizeof(rs));
	memset(b, 0, sizeof(b));
	//查询菜品价格，并记录到订单中
	char sql[35] = "select price from menu where id=?";
	if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		printf("%s\n", mysql_stmt_error(stmt));
	}
	
	b[0].buffer_type = MYSQL_TYPE_LONG;
	b[0].buffer = &eat;

	if (!mysql_stmt_bind_param(stmt, b)) {
		if (!mysql_stmt_execute(stmt)) {
			rs[0].buffer_type = MYSQL_TYPE_LONG;
			rs[0].buffer = &total;
			if (!mysql_stmt_bind_result(stmt, rs)) {
				if (!mysql_stmt_store_result(stmt)) {
					int t = 0;
					while (!mysql_stmt_fetch(stmt)) {
						t = 1;
						printf("请输入备注信息：");
						scanf_s("%s", remak, 30);
					}
					if (t==0) {
						printf("没有该菜品！\n");
						return;
					}
				}else {
					printf(mysql_stmt_error(stmt));
					printf("\n");
				}
			}
		}else {
			printf("%s\n", mysql_stmt_error(stmt));
		}
	}

	char sql1[45] = "insert into `order` values(0,?,?,?,?,?,?)";
	if (!mysql_stmt_prepare(stmt, sql1, strlen(sql1))) {
		bind[0].buffer_type = MYSQL_TYPE_LONG;
		bind[0].buffer = &eat;

		bind[1].buffer_type = MYSQL_TYPE_LONG;
		bind[1].buffer = &id;

		bind[2].buffer_type = MYSQL_TYPE_LONG;
		bind[2].buffer = &total;

		bind[3].buffer_type = MYSQL_TYPE_STRING;
		bind[3].buffer = &remak;
		bind[3].buffer_length = strlen(remak);

		bind[4].buffer_type = MYSQL_TYPE_LONG;
		bind[4].buffer = &yesno;

		bind[5].buffer_type = MYSQL_TYPE_LONG;
		bind[5].buffer = &vis;

		if (!mysql_stmt_bind_param(stmt, bind)) {
			if (!mysql_stmt_execute(stmt)) {
				printf("下单成功，等待配餐\n");
			}
		}
	}else {
		printf("%s", mysql_stmt_error(stmt));
	}
}
//查询当前餐桌消费情况
void mony(int id) {
	MYSQL_BIND bind[5];
	MYSQL_BIND b[1];
	MYSQL_BIND rs[1];
	int mid,sum=0;
	char name[20];
	memset(bind, 0, sizeof(bind));
	memset(rs, 0, sizeof(rs));
	memset(b, 0, sizeof(b));
	//查询菜品价格，并记录到订单中
	char sql[40] = "select mid from `order` where dsid=?";
	if (!mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		printf("%s\n", mysql_stmt_error(stmt));
	}

	b[0].buffer_type = MYSQL_TYPE_LONG;
	b[0].buffer = &id;

	if (!mysql_stmt_bind_param(stmt, b)) {
		if (!mysql_stmt_execute(stmt)) {
			rs[0].buffer_type = MYSQL_TYPE_LONG;
			rs[0].buffer = &mid;
			if (!mysql_stmt_bind_result(stmt, rs)) {
				if (!mysql_stmt_store_result(stmt)) {
					int t = 0;
					while (!mysql_stmt_fetch(stmt)) {
						if(t==0) printf("序号\t商品名称\t价格\n");
						t++;
						printf("%d\t", t);
						sum+=see_price(mid);
					}
					if (t == 0) {
						printf("暂无消费！\n");
						return;
					}
					else {
						printf("总计\t\t\t%d￥\n", sum);
					}
				}
				else {
					printf(mysql_stmt_error(stmt));
					printf("\n");
				}
			}
		}
		else {
			printf("%s\n", mysql_stmt_error(stmt));
		}
	}
}