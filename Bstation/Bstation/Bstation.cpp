// Bstation.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <winsock2.h>  
void ErrorHandling(char * msg);


class  Bstation
{
public:
	void setBstation();                  // ���û�վ����
	void acceptBstation();              //��վ��������
	void inforwardBstation();          //��վ�ڲ�ת������ֶ˿ڣ�
	void showBstation();              //��վ������ʾ��ʵʱͼ��
	void skyshowBstation();          //��վ������ʾ���ǿ�ͼ��
	void saveBstation();            //��վ���ݱ���
	void RmanagementBstation();    //��վԶ�̹���
private:
	SOCKET ServSock, hClntSock;//���÷���˺Ϳͻ��˵��׽���
	int EWorkMode;
	int ErrorCode;
	const char * IP;//����IP
	int iport;//���ת�Ӷ˿�
	int port;//���ݽ���˿�

};
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

void ErrorHandling(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}