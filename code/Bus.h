#pragma once

class Bus {//��¼����������״̬��ͬʱ��¼ʱ��
private:
	//id��¼�������ţ�detime��¼����ʱ�䣬arrtime��¼����ʱ�䣬state��¼������·
	int id = 0, detime = 0, arrtime = 0, state = 0;
	bool can = true;//��¼�����Ƿ��ܹ�����
public:
	Bus(){}

	int returnId() { return id; }//���س�������
	int returnDetime() { return detime; }//���س���ʱ��
	int returnArrtime() { return arrtime; }//���س�������ʱ��
	int returnState() { return state; }//����������·
	bool returnCan() { return can; }//���س����Ƿ��ܹ�����

	void changeId(int i) { id = i; }//���³�������
	void changeDetime(int d) { detime = d; }//���³���ʱ��
	void changeArrtime(int a) { arrtime = a; }//���·���ʱ��
	void changeState(int s) { state = s; }//����������·
};