#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Position.h"

class BusStop : public Position{//公共继承Position类
private:
	std::string name;//记录车站名称
	std::vector<int> lines;//记录经过的线路代号
public:
	BusStop() {}
	BusStop(std::string s, double inix, double iniy, std::vector<int> ss):Position(inix, iniy) {
		name = s;
		for (int i = 0; i < ss.size(); i++) lines.push_back(ss[i]);
	}//赋值构造函数
	~BusStop() {}
	std::string getName() {//获取车站的名称
		return name;
	}
	//信息更改
	void changeName(std::string newN) {name = newN;}
	void changePos(double newX,double newY) {
		changeX(newX);//继承自Position类
		changeY(newY);
	}

	//输出信息
	void printInfo() {
		std::cout << "\n" << name << "车站信息" << std::endl;//名称
		std::cout << "位置：";
		printPosition();//继承Position类
		std::cout << "经过线路：";
		for (int i = 0; i < lines.size(); i++) {
			std::cout << lines[i] << " ";
		}
	}
};