#include "UserInfo.h"

using namespace std;

string inputPassword() {//获取输入的密码
	string ret;
	char ch;
	ch = _getch();//读入而不显示
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
	}//做一些清理工作
}


string UsrInfo::getPw() {
	return Psword;
}

string UsrInfo::getName() {
	return UsrName;
}

int regest(UsrInfo user) {
	/*
	UsrInfo.txt文件的存储形式
	奇数行为用户名，偶数行为密码
	*/
	string name = user.getName();
	string pw = user.getPw();
	string temp;
	int flag = 0;
	int i = 0;
	ifstream fin("..\\src\\UsrInfo.txt", ios::in);//读入文件
	ofstream fout("..\\src\\UsrInfo.txt", ios::app);//注册成功则写入文件
	while (getline(fin, temp))
	{
		i++;
		if (i % 2 == 0) continue;
		if (!strcmp(name.c_str(), temp.c_str())) flag = 1;//用户名已存在
	}
	fin.close();
	if (flag) {
		return 0;
	}
	else {//在文件末尾写入新用户信息
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
		getline(fin, temp2);//读取用户名和密码
		if (!strcmp(name.c_str(), temp1.c_str())) {//匹配密码
			existname = 1;
			if (!strcmp(pw.c_str(), temp2.c_str())) {
				match = 1;//匹配成功
				break;
			}
		}
	}
	fin.close();
	if (!existname) {
		return 2;//用户名不存在
	}
	else {
		if (match) return 1;
		else return 3;//用户名和密码不匹配
	}
}