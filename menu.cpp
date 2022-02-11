#include "dbconn.h"
#include "guanli.h"
#include "menu.h"
#include "system.h"
#include "buy.h"
#include "oding.h"
//int denglu();

int denglu(int num);
//管理系统
void guanli() {
	if (denglu(2)) {
		system("cls");
		printf("=======欢迎来到管理员系统=======\n");
		int num;
		while (true) {
			printf("1.菜单管理\n");
			printf("2.餐桌管理\n");
			printf("3.订单管理\n");
			printf("4.查看营业额\n");
			printf("0.	返回\n ");
			printf("请输入你要进行的操作(0-3):");
			scanf_s("%d", &num);

			switch (num) {
			case 1://菜单管理
				menut();
				break;
			case 2://餐桌管理
				desk();
				break;
			case 3://订单管理
				dingdan();
				break;
			case 4://查看营业额
				printf("你的总营业额为：%d￥\n", qian());
				system("pause");
				break;
			case 0://返回
				return ;
			default:
				printf("输入错误！");
			}
			system("cls");
		}
	}
}

//系统设置
void system(){
	if (denglu(0)) {
		system("cls");
		printf("======系统设置======\n");
		while (1) {
			printf("1.修改备餐系统密码\n");
			printf("2.修改管理系统密码\n");
			printf("3.修改系统设置密码\n");
			printf("0.	返回\n");

			int num;
			printf("请选者你要进行的操作（0-3）：");
			scanf_s("%d", &num);

			switch (num) {
			case 1:
				one();
				break;
			case 2:
				two();
				break;
			case 3:
				tree();
				break;
			case 0:
				return;
			default:
				printf("输入错误！\n");
			}
			system("cls");
		}
	}
}

//备餐系统
void oding(){
	if (denglu(1)) {
		system("cls");
		printf("=======欢迎来到备餐系统=======\n");
		int num;
		while (true) {
			printf("1.接收订单\n");
			printf("2.取消配餐\n");
			printf("3.返回\n");
			printf("请选者你要进行的操作（0-3）：");
			scanf_s("%d", &num);
			switch (num) {
			case 1:
				agree();
				break;
			case 2:
				nooding();
				break;
			case 3:
				yesoding();
				break;
			case 0:
				return;
			default:
				printf("没有该功能，输入错误！");
			}
			system("cls");
		}
	}
}

//点餐系统
void buy() {
	system("cls");
	printf("========欢迎来到点餐系统========\n");

	char isok;
	int id=dian();
	printf("是否查看账单(y/n):");
	getchar();
	scanf_s("%c", &isok,(int)sizeof(char));

	if (isok == 'y') {
		printf("账单如下：\n");
		mony(id);
	}
}

int denglu(int num) {
	my_bool	is_null[4];
	unsigned long length[4];
	MYSQL_BIND bind[3];
	MYSQL_BIND result[4];//保存结果集
	int id=0, power=0;
	char name[20]="", password[20]="";//保存返回的四个参数
	memset(result, 0, sizeof(result));//初始化为0
	memset(bind, 0, sizeof(bind));//初始化为0
	char username[20];
	char pwd[20];
	char sql[71] = "SELECT * FROM users WHERE power=? and name=? and pwd=?";
	printf("请输入你的用户名：");
	scanf_s("%s", username, 20);
	printf("请输入你的密码：");
	scanf_s("%s", pwd, 20);
	if (!mysql_stmt_prepare(stmt, sql, strlen(sql))) {
		bind[0].buffer_type = MYSQL_TYPE_LONG;
		bind[0].buffer = &num;

		bind[1].buffer_type = MYSQL_TYPE_STRING;
		bind[1].buffer = &username;
		bind[1].buffer_length = strlen(username);

		bind[2].buffer_type = MYSQL_TYPE_STRING;
		bind[2].buffer = &pwd;
		bind[2].buffer_length = strlen(pwd);

		if (!mysql_stmt_bind_param(stmt, bind)) {
			if (!mysql_stmt_execute(stmt)) {
				result[0].buffer_type = MYSQL_TYPE_LONG;
				result[0].buffer = &id;
				result[0].is_null = &is_null[0];
				result[0].length = &length[0];

				result[1].buffer_type = MYSQL_TYPE_STRING;
				result[1].buffer = &name;
				result[1].buffer_length = 50;
				result[1].is_null = &is_null[1];
				result[1].length = &length[1];

				result[2].buffer_type = MYSQL_TYPE_STRING;
				result[2].buffer = &password;
				result[2].buffer_length = 50;
				result[2].is_null = &is_null[2];
				result[2].length = &length[2];

				result[3].buffer_type = MYSQL_TYPE_LONG;
				result[3].buffer = &power;
				result[3].is_null = &is_null[3];
				result[3].length = &length[3];

				if (!mysql_stmt_bind_result(stmt, result)) {
					if (!mysql_stmt_store_result(stmt)) {
						while (!mysql_stmt_fetch(stmt)) {
							if (is_null[0] && is_null[1] && is_null[2] && is_null[3]) {
								cout << "null" << endl;
							}
							return 1;
						}
					}
				}

			}
			else {
				cout << mysql_stmt_errno(stmt) << " " << mysql_stmt_error(stmt) << endl;
			}
		}
	}
	else {
		cout << mysql_stmt_errno(stmt)<<" " << mysql_stmt_error(stmt)<<endl;
	}//绑定语句
	printf("账号或密码错误！\n");
	system("pause");
	return 0;
}