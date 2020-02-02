#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Position.h"

class BusStop : public Position{//�����̳�Position��
private:
	std::string name;//��¼��վ����
	std::vector<int> lines;//��¼��������·����
public:
	BusStop() {}
	BusStop(std::string s, double inix, double iniy, std::vector<int> ss):Position(inix, iniy) {
		name = s;
		for (int i = 0; i < ss.size(); i++) lines.push_back(ss[i]);
	}//��ֵ���캯��
	~BusStop() {}
	std::string getName() {//��ȡ��վ������
		return name;
	}
	//��Ϣ����
	void changeName(std::string newN) {name = newN;}
	void changePos(double newX,double newY) {
		changeX(newX);//�̳���Position��
		changeY(newY);
	}

	//�����Ϣ
	void printInfo() {
		std::cout << "\n" << name << "��վ��Ϣ" << std::endl;//����
		std::cout << "λ�ã�";
		printPosition();//�̳�Position��
		std::cout << "������·��";
		for (int i = 0; i < lines.size(); i++) {
			std::cout << lines[i] << " ";
		}
	}
};