// bstration.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <winsock2.h>  
#include <string>
void ErrorHandling(char*message);

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
	SOCKET hServSock, hClntSock;          //���ÿͻ����׽��ֺͷ�����׽���
	int EWorkMode;
	int ErrorCode;
	/*string ip;*/
	const char * IP;//����IP��ַ
	int iport;//���ת�Ӷ˿�
	int port;//���ݽ���˿�
};
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

void ErrorHandling(char*message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
