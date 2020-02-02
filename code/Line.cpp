#include "Line.h"

using namespace std;

Line::Line(int Id, vector<double> dd,int in) {
	id = Id;
	index = in;
	total_distance = 0.0;
	for (int i = 0; i < dd.size(); i++) {
		distances.push_back(dd[i]);
		total_distance += dd[i];//利用distances初始化total_distance
	}
}//赋值构造函数

void Line::printInfo() {//输出线路信息
	cout << "线路共包含" << TotalS() << "个车站\n";
	cout << "相邻车站之间的距离依次为:\n";
	for (int i = 0; i < distances.size(); i++) {
		cout << distances[i] << " ";
	}
	cout << "\n线路总长为" << total_distance << "千米";
}

double Line::TotalD() {//返回线路总长度
	return total_distance;
}

int Line::TotalS() {//返回线路包含的车站数量
	return distances.size() + 1;
}

double Line::D(int in) {
	double res = 0.0;
	int max = in < distances.size() ? in : distances.size();
	for (int i = 0; i < in; i++) {
		res += distances[i];
	}
	return res;
}//返回源点到某个车站的距离