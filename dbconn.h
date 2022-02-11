#pragma once
#include <iostream>
#include<winsock.h>//注意顺序，要放在mysql.h前
#include<stdio.h>
#include<mysql.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
extern MYSQL mysql;//连接对象
extern MYSQL_RES* res_set;//结果集对象
extern MYSQL_ROW row;//用来保存单行结果
extern MYSQL_STMT* stmt;

int conn();//连接数据库
void gb();//关闭连接，释放结果集

void adddesk();//添加餐桌
void upsk();//修改餐桌子
void redesk(int id);//删除餐桌
void seedesk();//查看餐桌

void pwdup();//更新密码

void dingdan();
int qian();