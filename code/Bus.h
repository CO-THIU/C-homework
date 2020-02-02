#pragma once

class Bus {//记录车辆的运行状态，同时记录时间
private:
	//id记录车辆代号，detime记录出发时间，arrtime记录返回时间，state记录运行线路
	int id = 0, detime = 0, arrtime = 0, state = 0;
	bool can = true;//记录车辆是否能够运行
public:
	Bus(){}

	int returnId() { return id; }//返回车辆代号
	int returnDetime() { return detime; }//返回出发时间
	int returnArrtime() { return arrtime; }//返回车辆返回时间
	int returnState() { return state; }//返回运行线路
	bool returnCan() { return can; }//返回车辆是否能够运行

	void changeId(int i) { id = i; }//更新车辆代号
	void changeDetime(int d) { detime = d; }//更新出发时间
	void changeArrtime(int a) { arrtime = a; }//更新返回时间
	void changeState(int s) { state = s; }//更新运行线路
};