#pragma once

#include<iostream>

class Time
{
private:
	int hr, min, sec;//ʱ���֡���ȳ�Ա����
public:
	void right();//��ɨ����
	//���캯��
	Time(){}
	Time(const Time& t);
	Time(int h, int m, int s);
	void prinTime();//��ӡʱ��
	void adv(int inc_h, int inc_m, int inc_s);//����ʱ��
	void reset() {
		hr = min = sec = 0;
	}//����
	bool early(Time t);//�ж�ʱ���Ƿ����
	int gap(Time t);//��������ʱ����ʱ���Է��Ӽ�
	int val();//����ʱ����0ʱ0��0���ʱ���Է��Ӽ�
};