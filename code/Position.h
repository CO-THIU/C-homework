#pragma once

#include<iostream>
#include<cmath>
#include<string>

class Position {//处理空间位置坐标
public:
	Position(){}
	Position(double initX, double initY) {
		x = initX;
		y = initY;
	}//赋值构造函数
	double getX() { return x; }//返回横坐标
	double getY() { return y; }//返回纵坐标
	double distance(Position &p) {//获取当前位置与另一个空间点的直线距离
		double xp = x - p.getX();
		double yp = y - p.getY();
		return sqrt(xp*xp + yp * yp);
	}
	//更改位置坐标
	void changeX(double newX) {
		x = newX;
	}
	void changeY(double newY) {
		y = newY;
	}
	void printPosition() {//打印空间坐标
		std::cout << "(" << x << "," << y << ")" << std::endl;
	}
private:
	double x, y;//分别记录横纵坐标
};
