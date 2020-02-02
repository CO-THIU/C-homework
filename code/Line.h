#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "BusStop.h"

class Line {
private:
	int id;//记录线路编号
	double total_distance;//记录线路总距离
	std::vector<double> distances;//记录相邻车站之间的距离
	int index;//返回一个车站在线路上的位置
public:
	Line() {}
	Line(int Id, std::vector<double> dd, int in = 0);
	double TotalD();//返回线路总长
	int TotalS();//返回线路涉及的公交车站总数
	int ind() { return index; }//返回某车站在线路上的编号
	int returnId() { return id; }//返回线路代号
	std::vector<double> returnDiss() { return distances; }
	double D(int in);//返回source车站到某一车站in的距离
	void printInfo();//输出相关信息
};