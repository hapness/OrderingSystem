#pragma once
#include <iostream>
#include<winsock.h>//ע��˳��Ҫ����mysql.hǰ
#include<stdio.h>
#include<mysql.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
extern MYSQL mysql;//���Ӷ���
extern MYSQL_RES* res_set;//���������
extern MYSQL_ROW row;//�������浥�н��
extern MYSQL_STMT* stmt;

int conn();//�������ݿ�
void gb();//�ر����ӣ��ͷŽ����

void adddesk();//��Ӳ���
void upsk();//�޸Ĳ�����
void redesk(int id);//ɾ������
void seedesk();//�鿴����

void pwdup();//��������

void dingdan();
int qian();