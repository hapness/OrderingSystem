#include"dbconn.h"
#include "menu.h"
using namespace std;
//�˵�����ϵͳ

int main() {
    int num;
    if (!conn()) {
        printf("���ݿ�����ʧ��\n");
        return 0;
    }
    while (1)
    {
        printf("===========��ӭ������ϵͳ===========\n");
        printf("1.���ϵͳ\n");
        printf("2.����ϵͳ\n");
        printf("3.����ϵͳ\n");
        printf("4.ϵͳ����\n");
        printf("0.�˳�ϵͳ\n");
		printf("��ѡ����Ҫ���еĲ�����0-4����");
        scanf_s("%d", &num);
        switch (num) {
        case 0://�˳�ϵͳ
            printf("�˳��ɹ�����ӭ�´ι��٣�\n");
            return 0;
        case 1://���ϵͳ
            buy();
            break;
        case 2://����ϵͳ
            oding();
            break;
        case 3://�������
            guanli();
            break;
        case 4://ϵͳ����
            system();
            break;
        default:
            printf("�ù�����δ���ţ����������룡");
        }
    }
    
    gb();//�ر����ݿ�����
    return 0;
}
