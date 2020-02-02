#include "Line.h"

using namespace std;

Line::Line(int Id, vector<double> dd,int in) {
	id = Id;
	index = in;
	total_distance = 0.0;
	for (int i = 0; i < dd.size(); i++) {
		distances.push_back(dd[i]);
		total_distance += dd[i];//����distances��ʼ��total_distance
	}
}//��ֵ���캯��

void Line::printInfo() {//�����·��Ϣ
	cout << "��·������" << TotalS() << "����վ\n";
	cout << "���ڳ�վ֮��ľ�������Ϊ:\n";
	for (int i = 0; i < distances.size(); i++) {
		cout << distances[i] << " ";
	}
	cout << "\n��·�ܳ�Ϊ" << total_distance << "ǧ��";
}

double Line::TotalD() {//������·�ܳ���
	return total_distance;
}

int Line::TotalS() {//������·�����ĳ�վ����
	return distances.size() + 1;
}

double Line::D(int in) {
	double res = 0.0;
	int max = in < distances.size() ? in : distances.size();
	for (int i = 0; i < in; i++) {
		res += distances[i];
	}
	return res;
}//����Դ�㵽ĳ����վ�ľ���