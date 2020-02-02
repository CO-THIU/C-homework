#include "Time.h"

using namespace std;

void Time::right() {
	int is = sec, im = min, ih = hr;
	int adm = 0, adh = 0;
	while (is < 0) {
		is += 60;
		adm--;
	}
	while (is >= 60) {
		is -= 60;
		adm++;
	}
	im += adm;
	while (im < 0) {
		im += 60;
		adh--;
	}
	while (im >= 60) {
		im -= 60;
		adh++;
	}
	ih += adh;
	while (ih < 0) {
		ih += 24;
	}
	while (ih >= 24) {
		ih -= 24;
	}
	hr = ih;
	min = im;
	sec = is;
}//保持成员变量的组合是正常的时间格式

Time::Time(int h, int m, int s) {
	hr = h;
	min = m;
	sec = s;
	right();
}

Time::Time(const Time& t) {
	hr = t.hr;
	min = t.min;
	sec = t.sec;
}//复制构造函数

void Time::prinTime() {
	if (hr < 10) cout << "0";//保证格式统一
	cout << hr << ":";
	if (min < 10) cout << "0";
	cout << min << ":";
	if (sec < 10) cout << "0";
	cout << sec << endl;
}

void Time::adv(int inc_h, int inc_m, int inc_s) {
	hr += inc_h;
	min += inc_m;
	sec += inc_s;
	right();//保证格式
}

bool Time::early(Time t) {//比较时间的早晚情况
	if (hr > t.hr) return false;
	else if (hr == t.hr) {
		if (min > t.min) return false;
		else if (min == t.min) {
			if (sec > t.sec) return false;
		}
	}
	return true;
}

int Time::gap(Time t) {
	int val1 = hr * 60 + min;
	int val2 = t.hr * 60 + t.min;
	int res = val1 - val2;
	res = res > 0 ? res : -res;//保证返回的是正数，有意义
	return res;
}

int Time::val() {
	return hr * 60 + min;
}