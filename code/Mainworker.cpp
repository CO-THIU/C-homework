#include "Mainworker.h"
#include "BusStop.h"
#include "Line.h"
#include "Time.h"
#include "Bus.h"

using namespace std;
using std::cout;


//定义一系列主要的操作函数
void op1();
void op2(string s);
void op3(string s);
string op4_guest(Position p);
void op6_guest(string st, string dest);
void trip_generate();
void op4_admin();
void op5(int id);
void op6(string id);
void op7();

void mainworker_admin() {
	cout << "您可以选择执行以下操作\n";
	cout << "--------------------------------------------------------------------------------\n"
	        "1  查询线路网络概况\n";
	cout << "2  查询公交车站的基本信息\n";
	cout << "3  查询公交车站的运行时刻表\n";
	cout << "4  查询公交车的整体运行状况\n";
	cout << "5  查询单个公交车的运行状况\n";
	cout << "6  删除公交线路\n"; 
	cout << "7  新增公交线路\n";
	cout << "8  退出程序\n";
	cout << "--------------------------------------------------------------------------------\n\n";
step1:
	cout << "\n请选择接下来的操作(输入操作之前的数字即可)：";
	int op;
	cin >> op;
	string stop_name;
	string line_id;
	string flag;
	trip_generate();
	switch (op) {//根据输入的操作名称执行相应的操作
	case 1:
		op1();
		goto step1;
		break;
	case 2:
		cout << "请输入要查询的车站名称：";
		cin >> stop_name;
		op2(stop_name);
		goto step1;
		break;
	case 3:
		cout << "请输入要查询时刻表的车站名称：";
		cin >> stop_name;
		op3(stop_name);
		goto step1;
		break;
	case 4:
		op4_admin();
		goto step1;
		break;
	case 5:
		cout << "请输入您要查询的公交车代号：";
		int id;
		cin >> id;
		op5(id);
		goto step1;
		break;
	case 6:
		cout << "请输入您要删除的线路代号：";
		cin >> line_id;
		op6(line_id);
		goto step1;
		break;
	case 7:
		cout << "请确认你已在LineInfo_new.txt文件中完善新增线路的信息?<Y/N>：";
		cin >> flag;
		if (flag == "Y" || flag == "y") op7();
		else cout << "您已取消该操作\n";
		goto step1;
		break;
	case 8:
		break;
	default:
		break;
	}
}

void mainworker_guest(){
	cout << "您可以选择执行以下操作\n";
	cout << "--------------------------------------------------------------------------------\n";
	cout << "1  查询线路网络概况\n";
	cout << "2  查询公交车站的基本信息\n";
	cout << "3  查询公交车站的运行时刻表\n";
	cout << "4  获取距离自己所在地最近的公交车站名称\n";
	cout << "5  获取距离自己目的地最近的公交车站名称\n";
	cout << "6  提供出行规划意见\n";
	cout << "7  退出程序\n";
	cout << "--------------------------------------------------------------------------------\n\n";
step1:
	cout << "\n请选择接下来的操作(输入操作之前的数字即可)：";
	int op;
	cin >> op;
	string stop_name, self, dest;
	srand(time(NULL));
	//随机生成位置坐标
	double x1 = (rand() % 600) / 100.0 - 3.0;
	double y1 = (rand() % 600) / 100.0 - 3.0;
	double x2 = (rand() % 600) / 100.0 - 3.0;
	double y2 = (rand() % 600) / 100.0 - 3.0;
	Position p_self = Position(x1, y1);//随机所在位置
	Position p_des = Position(x2, y2);//随机的目的地位置
	switch (op) {//根据输入的操作名称执行相应的操作
	case 1:
		op1();
		goto step1;
		break;
	case 2:
		cout << "请输入要查询的车站名称：";
		cin >> stop_name;
		op2(stop_name);
		goto step1;
		break;
	case 3:
		cout << "请输入要查询时刻表的车站名称：";
		cin >> stop_name;
		op3(stop_name);
		goto step1;
		break;
	case 4:
		cout << "您现在所在的位置为";
		p_self.printPosition();
		self = op4_guest(p_self);
		cout << "距离您现在所在位置最近的车站为" << self << endl;
		goto step1;
		break;
	case 5:
		cout << "您的目的地所在的具体位置为";
		p_des.printPosition();
		dest = op4_guest(p_des);
		cout << "距离您的目的地所在位置最近的车站为" << dest << endl;
		goto step1;
		break;
	case 6:
		self = op4_guest(p_self);
		dest = op4_guest(p_des);
		op6_guest(self, dest);
		goto step1;
		break;
	case 7:
		break;
	default:
		break;
	}
}


vector<string> split(const string& str, const string& delim) {//以delim为分隔符，将string转换成vector
	vector<string> res;
	if ("" == str) return res;
	//先将要切割的字符串从string类型转换为char*类型
	char * strs = new char[str.length() + 1];
	strcpy_s(strs, str.length() + 1, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy_s(d, delim.length() + 1, delim.c_str());
	char *pTmp = NULL;
	char *p = strtok_s(strs, d, &pTmp);
	while (p) {
		string s = p; //分割得到的字符串转换为string类型
		res.push_back(s); //存入结果数组
		p = strtok_s(NULL, d, &pTmp);
	}
	return res;
}

Time getNowTime(){//获取当前系统时间
	time_t t = time(nullptr);
	struct tm nowTime;
	localtime_s(&nowTime, &t);
	Time time = Time(nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
	return time;
}

void op1() {//读取LineInfo.txt，输出线路网络的基本信息
	/*
	LineInfo.txt文件组织形式
	第一行是线路网络的总线路条数，接下来每三行分为一个板块，分别为线路的id，历经的车站，各车站之间的距离
	*/
	ifstream finLine("..\\src\\LineInfo.txt", ios::in);//读入文件
	string line_id, bus_stops, distances;//分别记录线路名称，历经车站和各车站之间的距离
	string nums;
	getline(finLine, nums);
	cout << "\n线路网络共包含有" << nums << "条线路，各条线路的大致信息如下\n\n";
	while (getline(finLine, line_id))
	{
		getline(finLine, bus_stops);//读取车站
		vector<string> BusStop = split(bus_stops, " ");
		getline(finLine, distances);//读取距离
		vector<string> Dist = split(distances, " ");
		//输出大致信息
		cout << "线路代号:" << line_id << endl;
		cout << "历经车站分别为:\n";
		for (int i = 0; i < BusStop.size(); i++) {
			cout << BusStop[i] << " ";
		}
		cout << endl;
		vector<double> dist;
		for (int i = 0; i < Dist.size(); i++) dist.push_back(atof(Dist[i].c_str()));
		Line line = Line(atoi(line_id.c_str()), dist, 0);
		line.printInfo();
		cout << endl << endl;
	}
	finLine.close();
}

void op2(string s) {//读取BustopInfo.txt文件，输出特定的公交车站信息
	/*
	BustopInfo.txt文件组织形式
	每四行分为一个板块，分别为公交车站的名称，横坐标，纵坐标，经过的各条线路
	*/
	ifstream finBus("..\\src\\BustopInfo.txt", ios::in);
	string stop_name, loc_x, loc_y, lines;
	bool flag = true;//退出条件
	while (getline(finBus, stop_name) && flag)
	{
		//从文件中读取相关信息
		getline(finBus, loc_x);
		getline(finBus, loc_y);
		getline(finBus, lines);
		//判断是否满足输入要求
		if (!strcmp(s.c_str(), stop_name.c_str())) {
			flag = false;
			double x = atof(loc_x.c_str());
			double y = atof(loc_y.c_str());
			vector<string> Lines = split(lines, " ");
			vector<int> s;
			for (int i = 0; i < Lines.size(); i++) s.push_back(atoi(Lines[i].c_str()));
			BusStop stop = BusStop(stop_name, x, y, s);
			stop.printInfo();
		}
	}
	if (flag) cout << "不存在名为" << s << "的车站";//遍历后发现不存在这样的车站
	cout << endl << endl;
	finBus.close();
}

vector<string> getLinethrBus(string s) {//获取通过特定公交车站的所有线路
	vector<string> Lines;
	ifstream finBus("..\\src\\BustopInfo.txt", ios::in);
	string stop_name, loc_x, loc_y, lines;
	bool flag = true;//退出条件
	while (getline(finBus, stop_name) && flag)
	{
		//从文件中读取相关信息
		getline(finBus, loc_x);
		getline(finBus, loc_y);
		getline(finBus, lines);
		//判断是否满足输入要求
		if (!strcmp(s.c_str(), stop_name.c_str())) {
			flag = false;
			Lines = split(lines, " ");
		}
	}
	finBus.close();
	return Lines;
}

Line returnLine(string line,string s) {//获取经过车站s的线路line的具体信息，返回Line类型
	ifstream finLine("..\\src\\LineInfo.txt", ios::in);//读入文件
	string line_id, bus_stops, distances;//分别记录线路名称，历经车站和各车站之间的距离
	string nums;//记录线路总条数
	int index = 0;//标定车站在线路上的具体位置
	Line lin;
	getline(finLine, nums);
	while (getline(finLine, line_id))
	{
		getline(finLine, bus_stops);//读取车站
		getline(finLine, distances);//读取距离
		if (!strcmp(line.c_str(), line_id.c_str())) {//判断是否找到
			vector<string> BusStop = split(bus_stops, " ");
			vector<string> Dist = split(distances, " ");
			
			for (int i = 0; i < BusStop.size(); i++) {
				if (!strcmp(s.c_str(), BusStop[i].c_str())) break;
				index++;//更新index
			}
			vector<double> dist;
			for (int i = 0; i < Dist.size(); i++) dist.push_back(atof(Dist[i].c_str()));
			lin = Line(atoi(line.c_str()), dist, index);//初始化Line对象
		}
	}
	finLine.close();
	return lin;
}

void op3(string s) {
	//读取config文件中的所有内容
	ifstream config("..\\src\\config.txt", ios::in);
	string speed, headway, start_time, end_time;//读取车辆行驶速度，车头时距，开始时间，终止时间
	getline(config, speed);
	double vec = atof(speed.c_str());
	getline(config, headway);
	double h = atof(headway.c_str());
	int head = static_cast<int>(h * 60);//以分钟计，保持分钟精度
	getline(config, start_time);
	vector<string> starts = split(start_time, " ");
	int st[3];
	for (int i = 0; i < starts.size(); i++) st[i] = atoi(starts[i].c_str());
	getline(config, end_time);
	vector<string> ends = split(end_time, " ");
	int e[3];
	for (int i = 0; i < ends.size(); i++) e[i] = atoi(ends[i].c_str());
	Time start = Time(st[0], st[1], st[2]);
	Time end = Time(e[0], e[1], e[2]);
	Time t = start;
	config.close();//关闭文件

	vector<string> Lines = getLinethrBus(s);//获取经过公交车站的所有线路名称
	int max = Lines.size();
	cout << "该公共车站有" << max << "条线路通过\n";
	double Dist, tD;
	int gap1, gap2;//定义最先到达公交车站公交车的时间信息
	for (int i = 0; i < max; i++) {
		cout << "\n线路" << Lines[i] << "在" << s << "车站的运行时刻表\n";
		Line lin = returnLine(Lines[i], s);
		Dist = lin.D(lin.ind());
		gap1 = static_cast<int>(Dist / vec * 60) + lin.ind();
		tD = lin.TotalD();
		gap2 = static_cast<int>(2 * tD / vec * 60) + 2 * lin.TotalS() - gap1;
		cout << "\n从source到终点站的时刻表如下：\n";
		t.adv(0, gap1, 0);
		while (t.early(end)) {
			t.prinTime();
			t.adv(0, head, 0);//以车头时距递增
		}
		t = start;
		cout << "\n从终点站到source的时刻表如下：\n";
		t.adv(0, gap2, 0);
		while (t.early(end)) {
			t.prinTime();
			t.adv(0, head, 0);//以车头时距递增
		}
		t = start;
	}
}

string op4_guest(Position p) {
	ifstream finBus("..\\src\\BustopInfo.txt", ios::in);
	string stop_name, loc_x, loc_y, lines;//读取公交汽车名称，横坐标、纵坐标、经过线路名称
	double min = 1000000.0;
	string min_stop = "source";
	double te;
	while (getline(finBus, stop_name))
	{
		//从文件中读取相关信息
		getline(finBus, loc_x);
		getline(finBus, loc_y);
		getline(finBus, lines);
		//获取公交车站位置
		double x = atof(loc_x.c_str());
		double y = atof(loc_y.c_str());
		Position temp = Position(x, y);
		te = p.distance(temp);
		if (te < min) {
			min = te;
			min_stop = stop_name;
		}//更新距离最短的公交车站信息
	}
	finBus.close();
	return min_stop;
}

void op6_guest(string st, string dest) {//出行规划
	if (st == dest) {
		cout << "步行距离更短，请选择步行\n";
	}//出发地和目的地距离足够近，步行更好
	else {
		vector<string> LinesofSt = getLinethrBus(st);
		vector<string> LinesofDest = getLinethrBus(dest);
		string sameLine = " ";//查找两个公交车站是否在同一条线路上
		for (int i = 0; i < LinesofSt.size(); i++) {
			for (int j = 0; j < LinesofDest.size(); j++) {
				if (LinesofDest[j] == LinesofSt[i]) sameLine = LinesofDest[j];
			}
		}
		if (sameLine != " ") {//在同一条线路上不需要换乘
			int step0;
			Line line1 = returnLine(sameLine, st);
			Line line2 = returnLine(sameLine, dest);
			step0 = line1.ind() - line2.ind();
			step0 = step0 > 0 ? step0 : -step0;
			cout << "在" << st << "车站上车，乘" << sameLine << "号线到达" << dest << "车站，途径" << step0 << "个车站" << endl;
		}
		else {//以source车站为中转站换乘
			Line line1 = returnLine(LinesofSt[0], st);
			Line line2 = returnLine(LinesofDest[0], dest);
			int step1, step2;
			step2 = line2.TotalS() - line2.ind();
			step1 = line1.ind();
			cout << "在" << st << "车站上车，乘" << line1.returnId() << "号线到达source车站，途径" << step1 << "个车站" << endl;
			cout << "在source车站转乘" << line2.returnId() << "号线到达" << dest << "车站，途径" << step2 << "个车站" << endl;
		}
	}
	
}

void trip_generate() {//采用First-In-Fisrt-Out策略，根据配置文件信息和线路网络信息安排公交车的出行
	/*
	config.txt文件的存储内容
	第一行为车辆运行速度，第二行为车头时距，第三行为系统开始运行时间，第四行为系统终止运行时间
	*/
	std::ifstream config("..\\src\\config.txt", ios::in);
	string speed, headway, start_time, end_time;//读取车辆行驶速度，车头时距，开始时间，终止时间
	getline(config, speed);
	double vec = atof(speed.c_str());
	getline(config, headway);
	double h = atof(headway.c_str());
	int head = static_cast<int>(h * 60);
	getline(config, start_time);
	vector<string> starts = split(start_time, " ");
	int st[3];
	for (int i = 0; i < starts.size(); i++) st[i] = atoi(starts[i].c_str());
	getline(config, end_time);
	vector<string> ends = split(end_time, " ");
	int e[3];
	for (int i = 0; i < ends.size(); i++) e[i] = atoi(ends[i].c_str());
	Time start = Time(st[0], st[1], st[2]);
	Time end = Time(e[0], e[1], e[2]);
	config.close();

	string nums;
	std::ifstream finLine("..\\src\\LineInfo.txt", ios::in);//读入文件
	getline(finLine, nums);
	int n = atoi(nums.c_str());//获取线路网络包含的线路条数
	int *dur = new int[n];//记录每条线路运转一个
	std::stack<Bus> w;
	std::queue<Bus> *r = new std::queue<Bus>[n];//利用队列实现FIFO
	int index = 0;
	string line_id, bus_stops, distances;//分别记录线路名称，历经车站和各车站之间的距离
	Line lin;
	while (getline(finLine, line_id))
	{
		getline(finLine, bus_stops);//读取车站
		getline(finLine, distances);//读取距离
		vector<string> Dist = split(distances, " ");
		vector<double> dist;
		for (int i = 0; i < Dist.size(); i++) dist.push_back(atof(Dist[i].c_str()));
		lin = Line(atoi(line_id.c_str()), dist, 0);
		//计算每条线路的运行时间，假定每个公交车站上下车耗时一分钟
		dur[index] = 2 * static_cast<int>(lin.TotalD() / vec * 60) + 2 * lin.TotalS();
		index++;
	}
	finLine.close();

	int maxdur = dur[0];//确定整个系统的结束时间
	for (int i = 0; i < n; i++) {
		if (maxdur < dur[i]) maxdur = dur[i];
	}
	static int m = 100;

	for (int i = m; i >= 1; i--) {
		Bus tem;//初始化，以便后续使用
		tem.changeId(i);
		tem.changeState(n + 1);
		w.push(tem);
	}

	int *num = new int[m];//记录每辆车的运行次数
	for (int i = 0; i < m; i++) num[i] = 0;

	int *nextde = new int[n];
	for (int i = 0; i < n; i++) nextde[i] = 0;
	int gap = start.gap(end);//系统的总共运行时间，以分钟计

	vector<Bus> res;//记录每次运行
	for (int ct = 0; ct <= gap + maxdur; ct++) {
		for (int i = 0; i < n; i++) {
			if (r[i].empty() == false) {
				Bus temp = r[i].front();
				if (temp.returnArrtime() == ct) {
					res.push_back(temp);
					//cout << temp.state + 1 << " " << temp.detime << " " << temp.arrtime << " " << temp.id << endl;
					num[temp.returnId() - 1]++;
					r[i].pop();//从队列取出公交车
					temp.changeState(n + 1);
					w.push(temp);
				}
			}

			if (nextde[i] == ct && nextde[i] <= gap) {
				Bus te = w.top();
				w.pop();
				te.changeDetime(ct);
				te.changeArrtime(ct + dur[i]);
				te.changeState(i);
				r[i].push(te);
				nextde[i] += head;
			}
		}
	}
	/*
	record.txt文件存储形式
	每一行是一条行驶记录，分别为线路代号、车辆代号、出发时间、返回时间
	*/
	ofstream foutRes("..\\src\\record.txt", ios::out);
	for (int i = 0; i < res.size(); i++) {
		foutRes << res[i].returnState() + 1 << " " << res[i].returnId() << " " << res[i].returnDetime() << " " << res[i].returnArrtime() << endl;
	}
	foutRes.close();
}

int numofLine() {//返回线路网络中的线路总条数
	ifstream finLine("..\\src\\LineInfo.txt", ios::in);
	string nums;
	getline(finLine, nums);
	int n = atoi(nums.c_str());
	finLine.close();
	return n;
}

void op4_admin() {
	int n = numofLine();
	ifstream finRes("..\\src\\record.txt", ios::in);//读取出行记录信息
	int numofBus = 0;//记录支持整个系统所需要的总的公交车数量
	int *numofRe = new int[n];//记录公交车在每条线路上的运行次数
	for (int i = 0; i < n; i++) numofRe[i] = 0;
	string record;
	while (getline(finRes, record)) {
		vector<string> res = split(record, " ");
		vector<int> Res;
		for (int i = 0; i < res.size(); i++) Res.push_back(atof(res[i].c_str()));//转换record格式，方便处理
		numofRe[Res[0] - 1]++;
		if (Res[1] > numofBus) numofBus = Res[1];
	}
	finRes.close();
	cout << "支持整个公交系统正常运行需要" << numofBus << "辆公交车\n";
	cout << "每天在每条线路上公交车要行驶" << numofRe[0] << "个来回" << endl;
	cout << endl;
}

void op5(int id) {
	int n = numofLine();
	ifstream finRes("..\\src\\record.txt", ios::in);//读取出行记录信息
	int num = 0;
	int *numofRe = new int[n];//记录特定id的公交车在每条线路上的运行次数
	for (int i = 0; i < n; i++) numofRe[i] = 0;
	string record;
	bool run_flag = false;//检查有无运行
	while (getline(finRes, record)) {
		vector<string> res = split(record, " ");
		vector<int> Res;
		for (int i = 0; i < res.size(); i++) Res.push_back(atof(res[i].c_str()));
		if (Res[1] == id) {
			Time t = getNowTime();//获取当前时间
			Time start = Time(7, 0, 0);
			int gap = t.gap(start);
			if (gap > Res[2] && gap < Res[3]) {//若处于这个时间段内，正在特定记录对应的线路上运行
				cout << id << "号车现在在" << Res[0] << "号线运行\n";
				run_flag = true;
			}
			numofRe[Res[0] - 1]++;
			num++;
		}
	}
	//输出信息
	if (!run_flag) cout << id << "号车现在没有运行\n";
	finRes.close();
	cout << id << "号车每天运行" << num << "个来回\n";
	for (int i = 0; i < n; i++) {
		cout << "每天在" << i + 1 << "号线上该公交车要行驶" << numofRe[i] << "个来回" << endl;
	}
	cout << endl;
}

void copyF(string fso,string fdes) {//将一个文件的内容复制到另一个文件中
	ifstream finPre(fso, ios::in);
	ofstream fout(fdes, ios::out);
	fout.close();
	ofstream foutLine(fdes, ios::app);
	string line;
	while (getline(finPre, line)) if (line != "") foutLine << line << endl;
	foutLine.close();
	finPre.close();
}

void cleanwork(string line_id) {//删除某条线路后更新一下BustopInfo.txt和Bustop_pre.txt两个文件，保证记录的一致性
	ifstream finPreC("..\\src\\BustopInfo_pre.txt", ios::in);
	ofstream foutC("..\\src\\BustopInfo.txt", ios::out);
	foutC.close();
	ofstream foutLineC("..\\src\\BustopInfo.txt", ios::app);
	string id, loc_x, loc_y, lines;
	while (getline(finPreC, id))
	{
		getline(finPreC, loc_x);//读取横坐标
		getline(finPreC, loc_y);//读取纵坐标
		getline(finPreC, lines);//读取经过的各条线路
		vector<string> res = split(lines, " ");
		foutLineC << id << endl;
		foutLineC << loc_x << endl;
		foutLineC << loc_y << endl;
		for (int i = 0; i < res.size(); i++) {
			if (atoi(res[i].c_str()) > atoi(line_id.c_str())) foutLineC << atoi(res[i].c_str()) - 1 << " ";
			else foutLineC << atoi(res[i].c_str()) << " ";//检查线路代号是否需要更改
		}
		foutLineC << endl;
	}
	finPreC.close();
	foutLineC.close();
	copyF("..\\src\\BustopInfo.txt", "..\\src\\BustopInfo_pre.txt");
}

void deleteStop(string s, string line_id) {//删除线路时需要确定有关车站是否需要删除
	ifstream finPre("..\\src\\BustopInfo_pre.txt", ios::in);
	ofstream fout("..\\src\\BustopInfo.txt", ios::out);
	fout.close();
	ofstream foutLine("..\\src\\BustopInfo.txt", ios::app);
	string id, loc_x, loc_y, lines;

	while (getline(finPre, id))
	{
		getline(finPre, loc_x);//读取横坐标
		getline(finPre, loc_y);//读取纵坐标
		getline(finPre, lines);//读取经过的所有线路
		vector<string> res = split(lines, " ");
		if (!strcmp(id.c_str(), s.c_str())) {
			
			if (res.size() < 2) {//如果车站只经过了要被删除的线路，将车站删除
				std::cout << id << "车站已经被删除！\n";
				continue;
			}
			else {//否则，更新车站经过的线路信息，删除掉要废除的线路信息
				foutLine << id << endl;
				foutLine << loc_x << endl;
				foutLine << loc_y << endl;
				for (int i = 0; i < res.size(); i++) {
					if (strcmp(res[i].c_str(), line_id.c_str())) foutLine << atoi(res[i].c_str()) << " ";
				}
				foutLine << endl;
			}
		}
		else {
			foutLine << id << endl;
			foutLine << loc_x << endl;
			foutLine << loc_y << endl;
			foutLine << lines << endl;
		}
	}
	finPre.close();
	foutLine.close();
	copyF("..\\src\\BustopInfo.txt", "..\\src\\BustopInfo_pre.txt");
}

void op6(string line_id) {
	//读取文件
	ifstream finPre("..\\src\\LineInfo_pre.txt", ios::in);
	ofstream fout("..\\src\\LineInfo.txt", ios::out);
	fout.close();
	ofstream foutLine("..\\src\\LineInfo.txt", ios::app);
	string nums;
	int num;
	getline(finPre, nums);
	num = atoi(nums.c_str()) - 1;
	foutLine << num << endl;
	string id, bus_stops, distances;//分别记录线路名称，历经车站和各车站之间的距离
	bool flag = false;//判断线路是在要删除的线路之前还是之后
	while (getline(finPre, id))
	{
		getline(finPre, bus_stops);//读取车站
		getline(finPre, distances);//读取距离
		if (!strcmp(id.c_str(), line_id.c_str())) {//判断是否是要删除的线路
			flag = true;
			vector<string> res = split(bus_stops, " ");
			for (int i = 0; i < res.size(); i++) {
				deleteStop(res[i], line_id);
			}
			continue;
		}
		if (!flag) {//判断要记录的线路是在要删除线路之前还是之后
			foutLine << id << endl;
			foutLine << bus_stops << endl;
			foutLine << distances << endl;
		}
		else {
			int new_id = atoi(id.c_str()) - 1;
			foutLine << new_id << endl;
			foutLine << bus_stops << endl;
			foutLine << distances << endl;
		}
	}
	finPre.close();
	foutLine.close();
	copyF("..\\src\\LineInfo.txt", "..\\src\\LineInfo_pre.txt");
	cleanwork(line_id);//一些清理工作
	std::cout << line_id << "号线已经成功删除！";
	trip_generate();//更新系统运行记录
}

void updateStop(string s, int n) {
	//读取文件
	ifstream finPre("..\\src\\BustopInfo_pre.txt", ios::in);
	ofstream fout("..\\src\\BustopInfo.txt", ios::out);
	fout.close();
	ofstream foutLine("..\\src\\BustopInfo.txt", ios::app);
	string id, loc_x, loc_y, lines;

	while (getline(finPre, id))
	{
		getline(finPre, loc_x);//读取横坐标
		getline(finPre, loc_y);//读取纵坐标
		getline(finPre, lines);//读取经过的线路网络
		vector<string> res = split(lines, " ");
		foutLine << id << endl;
		foutLine << loc_x << endl;
		foutLine << loc_y << endl;
		if (!strcmp(id.c_str(), s.c_str())) {//更新原有的公交车站
			for (int i = 0; i < res.size(); i++) {
				foutLine << atoi(res[i].c_str()) << " ";
			}
			foutLine << n << endl;
		}
		else foutLine << lines << endl;
	}
	finPre.close();
	foutLine.close();
	copyF("..\\src\\BustopInfo.txt", "..\\src\\BustopInfo_pre.txt");
}

void op7() {
	int n = numofLine() + 1;
	ifstream finPre("..\\src\\LineInfo_pre.txt", ios::in);
	ofstream fout("..\\src\\LineInfo.txt", ios::out);
	fout.close();
	ofstream foutLine("..\\src\\LineInfo.txt", ios::app);
	foutLine << n << endl;//更新线路网络的总条数
	string line;
	getline(finPre, line);
	while (getline(finPre, line)) if (line != "") foutLine << line << endl;//将原有的线路信息复制下来
	finPre.close();
	foutLine << n << endl;
	ifstream finNew("..\\src\\LineInfo_new.txt", ios::in);//读取新增线路的具体信息

	getline(finNew, line);
	foutLine << line << endl;//更新线路包含车站信息
	getline(finNew, line);
	foutLine << line << endl;//更新线路各车站之间的距离信息
	getline(finNew, line);//读取原有公交车站信息
	vector<string> bus_stops_old = split(line, " ");
	for (int i = 0; i < bus_stops_old.size(); i++) {
		updateStop(bus_stops_old[i], n);
	}
	foutLine.close();
	ofstream fout1("..\\src\\BustopInfo.txt", ios::app);
	string name, loc_x, loc_y;//读取新增公交车站信息，直接放在文件的最后面即可
	while (getline(finNew, name)) {
		getline(finNew, loc_x);
		getline(finNew, loc_y);
		fout1 << name << endl;
		fout1 << loc_x << endl;
		fout1 << loc_y << endl;
		fout1 << n << endl;
	}
	fout1.close();
	finNew.close();
	copyF("..\\src\\BustopInfo.txt", "..\\src\\BustopInfo_pre.txt");
	copyF("..\\src\\LineInfo.txt", "..\\src\\LineInfo_pre.txt");
	cout << "成功增加" << n << "号线" << endl;
	trip_generate();//更新系统运行记录信息
}