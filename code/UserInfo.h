#pragma once

#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

std::string inputPassword();//��ȡ��������벢����

void trim(std::string &ret);

class UsrInfo//�����û������˻���������Ϣ
{
private:
	std::string UsrName;//�û���
	std::string Psword;//����
public:
	UsrInfo(){}
	UsrInfo(std::string name, std::string pw) {
		UsrName = name;
		Psword = pw;
	}//��ֵ���캯��
	std::string getName();//�����û���
	std::string getPw();//��������
};


int regest(UsrInfo user);//ע��

int login(UsrInfo user);//��¼