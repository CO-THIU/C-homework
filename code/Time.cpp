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
}//���ֳ�Ա�����������������ʱ���ʽ

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
}//���ƹ��캯��

void Time::prinTime() {
	if (hr < 10) cout << "0";//��֤��ʽͳһ
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
	right();//��֤��ʽ
}

bool Time::early(Time t) {//�Ƚ�ʱ����������
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
	res = res > 0 ? res : -res;//��֤���ص���������������
	return res;
}

int Time::val() {
	return hr * 60 + min;
}