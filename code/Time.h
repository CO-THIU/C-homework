#pragma once

#include<iostream>

class Time
{
private:
	int hr, min, sec;//时、分、秒等成员变量
public:
	void right();//清扫工作
	//构造函数
	Time(){}
	Time(const Time& t);
	Time(int h, int m, int s);
	void prinTime();//打印时间
	void adv(int inc_h, int inc_m, int inc_s);//增加时间
	void reset() {
		hr = min = sec = 0;
	}//清零
	bool early(Time t);//判断时间是否更早
	int gap(Time t);//计算两个时间点的时间差，以分钟计
	int val();//返回时间与0时0分0秒的时间差，以分钟计
};