#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "BusStop.h"

class Line {
private:
	int id;//��¼��·���
	double total_distance;//��¼��·�ܾ���
	std::vector<double> distances;//��¼���ڳ�վ֮��ľ���
	int index;//����һ����վ����·�ϵ�λ��
public:
	Line() {}
	Line(int Id, std::vector<double> dd, int in = 0);
	double TotalD();//������·�ܳ�
	int TotalS();//������·�漰�Ĺ�����վ����
	int ind() { return index; }//����ĳ��վ����·�ϵı��
	int returnId() { return id; }//������·����
	std::vector<double> returnDiss() { return distances; }
	double D(int in);//����source��վ��ĳһ��վin�ľ���
	void printInfo();//��������Ϣ
};