#include "UserInfo.h"

using namespace std;

string inputPassword() {//��ȡ���������
	string ret;
	char ch;
	ch = _getch();//���������ʾ
	while (ch != '\n' && ch != '\r')
	{
		ret += ch;
		ch = _getch();
	}
	return ret;
}

void trim(string &ret) {
	int index = 0;
	if (!ret.empty())
	{
		while ((index = ret.find('\0', index)) != string::npos)
		{
			ret.erase(index, 1);
		}
	}//��һЩ������
}


string UsrInfo::getPw() {
	return Psword;
}

string UsrInfo::getName() {
	return UsrName;
}

int regest(UsrInfo user) {
	/*
	UsrInfo.txt�ļ��Ĵ洢��ʽ
	������Ϊ�û�����ż����Ϊ����
	*/
	string name = user.getName();
	string pw = user.getPw();
	string temp;
	int flag = 0;
	int i = 0;
	ifstream fin("..\\src\\UsrInfo.txt", ios::in);//�����ļ�
	ofstream fout("..\\src\\UsrInfo.txt", ios::app);//ע��ɹ���д���ļ�
	while (getline(fin, temp))
	{
		i++;
		if (i % 2 == 0) continue;
		if (!strcmp(name.c_str(), temp.c_str())) flag = 1;//�û����Ѵ���
	}
	fin.close();
	if (flag) {
		return 0;
	}
	else {//���ļ�ĩβд�����û���Ϣ
		fout << name << endl;
		fout << pw << endl;
		fout.close();
		return 1;
	}
}

int login(UsrInfo user) {
	string name = user.getName();
	string pw = user.getPw();
	string temp1;
	string temp2;
	int existname = 0;
	int match = 0;
	int i = 0;
	ifstream fin("..\\src\\UsrInfo.txt", ios::in);
	while (getline(fin, temp1))
	{
		getline(fin, temp2);//��ȡ�û���������
		if (!strcmp(name.c_str(), temp1.c_str())) {//ƥ������
			existname = 1;
			if (!strcmp(pw.c_str(), temp2.c_str())) {
				match = 1;//ƥ��ɹ�
				break;
			}
		}
	}
	fin.close();
	if (!existname) {
		return 2;//�û���������
	}
	else {
		if (match) return 1;
		else return 3;//�û��������벻ƥ��
	}
}