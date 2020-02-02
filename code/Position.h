#pragma once

#include<iostream>
#include<cmath>
#include<string>

class Position {//����ռ�λ������
public:
	Position(){}
	Position(double initX, double initY) {
		x = initX;
		y = initY;
	}//��ֵ���캯��
	double getX() { return x; }//���غ�����
	double getY() { return y; }//����������
	double distance(Position &p) {//��ȡ��ǰλ������һ���ռ���ֱ�߾���
		double xp = x - p.getX();
		double yp = y - p.getY();
		return sqrt(xp*xp + yp * yp);
	}
	//����λ������
	void changeX(double newX) {
		x = newX;
	}
	void changeY(double newY) {
		y = newY;
	}
	void printPosition() {//��ӡ�ռ�����
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
private:
	double x, y;//�ֱ��¼��������
};
