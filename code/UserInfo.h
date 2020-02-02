#pragma once

#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

std::string inputPassword();//获取输入的密码并返回

void trim(std::string &ret);

class UsrInfo//处理用户名的账户和密码信息
{
private:
	std::string UsrName;//用户名
	std::string Psword;//密码
public:
	UsrInfo(){}
	UsrInfo(std::string name, std::string pw) {
		UsrName = name;
		Psword = pw;
	}//赋值构造函数
	std::string getName();//返回用户名
	std::string getPw();//返回密码
};


int regest(UsrInfo user);//注册

int login(UsrInfo user);//登录