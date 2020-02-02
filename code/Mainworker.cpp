#include "Mainworker.h"
#include "BusStop.h"
#include "Line.h"
#include "Time.h"
#include "Bus.h"

using namespace std;
using std::cout;


//����һϵ����Ҫ�Ĳ�������
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
	cout << "������ѡ��ִ�����²���\n";
	cout << "--------------------------------------------------------------------------------\n"
	        "1  ��ѯ��·����ſ�\n";
	cout << "2  ��ѯ������վ�Ļ�����Ϣ\n";
	cout << "3  ��ѯ������վ������ʱ�̱�\n";
	cout << "4  ��ѯ����������������״��\n";
	cout << "5  ��ѯ����������������״��\n";
	cout << "6  ɾ��������·\n"; 
	cout << "7  ����������·\n";
	cout << "8  �˳�����\n";
	cout << "--------------------------------------------------------------------------------\n\n";
step1:
	cout << "\n��ѡ��������Ĳ���(�������֮ǰ�����ּ���)��";
	int op;
	cin >> op;
	string stop_name;
	string line_id;
	string flag;
	trip_generate();
	switch (op) {//��������Ĳ�������ִ����Ӧ�Ĳ���
	case 1:
		op1();
		goto step1;
		break;
	case 2:
		cout << "������Ҫ��ѯ�ĳ�վ���ƣ�";
		cin >> stop_name;
		op2(stop_name);
		goto step1;
		break;
	case 3:
		cout << "������Ҫ��ѯʱ�̱�ĳ�վ���ƣ�";
		cin >> stop_name;
		op3(stop_name);
		goto step1;
		break;
	case 4:
		op4_admin();
		goto step1;
		break;
	case 5:
		cout << "��������Ҫ��ѯ�Ĺ��������ţ�";
		int id;
		cin >> id;
		op5(id);
		goto step1;
		break;
	case 6:
		cout << "��������Ҫɾ������·���ţ�";
		cin >> line_id;
		op6(line_id);
		goto step1;
		break;
	case 7:
		cout << "��ȷ��������LineInfo_new.txt�ļ�������������·����Ϣ?<Y/N>��";
		cin >> flag;
		if (flag == "Y" || flag == "y") op7();
		else cout << "����ȡ���ò���\n";
		goto step1;
		break;
	case 8:
		break;
	default:
		break;
	}
}

void mainworker_guest(){
	cout << "������ѡ��ִ�����²���\n";
	cout << "--------------------------------------------------------------------------------\n";
	cout << "1  ��ѯ��·����ſ�\n";
	cout << "2  ��ѯ������վ�Ļ�����Ϣ\n";
	cout << "3  ��ѯ������վ������ʱ�̱�\n";
	cout << "4  ��ȡ�����Լ����ڵ�����Ĺ�����վ����\n";
	cout << "5  ��ȡ�����Լ�Ŀ�ĵ�����Ĺ�����վ����\n";
	cout << "6  �ṩ���й滮���\n";
	cout << "7  �˳�����\n";
	cout << "--------------------------------------------------------------------------------\n\n";
step1:
	cout << "\n��ѡ��������Ĳ���(�������֮ǰ�����ּ���)��";
	int op;
	cin >> op;
	string stop_name, self, dest;
	srand(time(NULL));
	//�������λ������
	double x1 = (rand() % 600) / 100.0 - 3.0;
	double y1 = (rand() % 600) / 100.0 - 3.0;
	double x2 = (rand() % 600) / 100.0 - 3.0;
	double y2 = (rand() % 600) / 100.0 - 3.0;
	Position p_self = Position(x1, y1);//�������λ��
	Position p_des = Position(x2, y2);//�����Ŀ�ĵ�λ��
	switch (op) {//��������Ĳ�������ִ����Ӧ�Ĳ���
	case 1:
		op1();
		goto step1;
		break;
	case 2:
		cout << "������Ҫ��ѯ�ĳ�վ���ƣ�";
		cin >> stop_name;
		op2(stop_name);
		goto step1;
		break;
	case 3:
		cout << "������Ҫ��ѯʱ�̱�ĳ�վ���ƣ�";
		cin >> stop_name;
		op3(stop_name);
		goto step1;
		break;
	case 4:
		cout << "���������ڵ�λ��Ϊ";
		p_self.printPosition();
		self = op4_guest(p_self);
		cout << "��������������λ������ĳ�վΪ" << self << endl;
		goto step1;
		break;
	case 5:
		cout << "����Ŀ�ĵ����ڵľ���λ��Ϊ";
		p_des.printPosition();
		dest = op4_guest(p_des);
		cout << "��������Ŀ�ĵ�����λ������ĳ�վΪ" << dest << endl;
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


vector<string> split(const string& str, const string& delim) {//��delimΪ�ָ�������stringת����vector
	vector<string> res;
	if ("" == str) return res;
	//�Ƚ�Ҫ�и���ַ�����string����ת��Ϊchar*����
	char * strs = new char[str.length() + 1];
	strcpy_s(strs, str.length() + 1, str.c_str());

	char * d = new char[delim.length() + 1];
	strcpy_s(d, delim.length() + 1, delim.c_str());
	char *pTmp = NULL;
	char *p = strtok_s(strs, d, &pTmp);
	while (p) {
		string s = p; //�ָ�õ����ַ���ת��Ϊstring����
		res.push_back(s); //����������
		p = strtok_s(NULL, d, &pTmp);
	}
	return res;
}

Time getNowTime(){//��ȡ��ǰϵͳʱ��
	time_t t = time(nullptr);
	struct tm nowTime;
	localtime_s(&nowTime, &t);
	Time time = Time(nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
	return time;
}

void op1() {//��ȡLineInfo.txt�������·����Ļ�����Ϣ
	/*
	LineInfo.txt�ļ���֯��ʽ
	��һ������·���������·������������ÿ���з�Ϊһ����飬�ֱ�Ϊ��·��id�������ĳ�վ������վ֮��ľ���
	*/
	ifstream finLine("..\\src\\LineInfo.txt", ios::in);//�����ļ�
	string line_id, bus_stops, distances;//�ֱ��¼��·���ƣ�������վ�͸���վ֮��ľ���
	string nums;
	getline(finLine, nums);
	cout << "\n��·���繲������" << nums << "����·��������·�Ĵ�����Ϣ����\n\n";
	while (getline(finLine, line_id))
	{
		getline(finLine, bus_stops);//��ȡ��վ
		vector<string> BusStop = split(bus_stops, " ");
		getline(finLine, distances);//��ȡ����
		vector<string> Dist = split(distances, " ");
		//���������Ϣ
		cout << "��·����:" << line_id << endl;
		cout << "������վ�ֱ�Ϊ:\n";
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

void op2(string s) {//��ȡBustopInfo.txt�ļ�������ض��Ĺ�����վ��Ϣ
	/*
	BustopInfo.txt�ļ���֯��ʽ
	ÿ���з�Ϊһ����飬�ֱ�Ϊ������վ�����ƣ������꣬�����꣬�����ĸ�����·
	*/
	ifstream finBus("..\\src\\BustopInfo.txt", ios::in);
	string stop_name, loc_x, loc_y, lines;
	bool flag = true;//�˳�����
	while (getline(finBus, stop_name) && flag)
	{
		//���ļ��ж�ȡ�����Ϣ
		getline(finBus, loc_x);
		getline(finBus, loc_y);
		getline(finBus, lines);
		//�ж��Ƿ���������Ҫ��
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
	if (flag) cout << "��������Ϊ" << s << "�ĳ�վ";//�������ֲ����������ĳ�վ
	cout << endl << endl;
	finBus.close();
}

vector<string> getLinethrBus(string s) {//��ȡͨ���ض�������վ��������·
	vector<string> Lines;
	ifstream finBus("..\\src\\BustopInfo.txt", ios::in);
	string stop_name, loc_x, loc_y, lines;
	bool flag = true;//�˳�����
	while (getline(finBus, stop_name) && flag)
	{
		//���ļ��ж�ȡ�����Ϣ
		getline(finBus, loc_x);
		getline(finBus, loc_y);
		getline(finBus, lines);
		//�ж��Ƿ���������Ҫ��
		if (!strcmp(s.c_str(), stop_name.c_str())) {
			flag = false;
			Lines = split(lines, " ");
		}
	}
	finBus.close();
	return Lines;
}

Line returnLine(string line,string s) {//��ȡ������վs����·line�ľ�����Ϣ������Line����
	ifstream finLine("..\\src\\LineInfo.txt", ios::in);//�����ļ�
	string line_id, bus_stops, distances;//�ֱ��¼��·���ƣ�������վ�͸���վ֮��ľ���
	string nums;//��¼��·������
	int index = 0;//�궨��վ����·�ϵľ���λ��
	Line lin;
	getline(finLine, nums);
	while (getline(finLine, line_id))
	{
		getline(finLine, bus_stops);//��ȡ��վ
		getline(finLine, distances);//��ȡ����
		if (!strcmp(line.c_str(), line_id.c_str())) {//�ж��Ƿ��ҵ�
			vector<string> BusStop = split(bus_stops, " ");
			vector<string> Dist = split(distances, " ");
			
			for (int i = 0; i < BusStop.size(); i++) {
				if (!strcmp(s.c_str(), BusStop[i].c_str())) break;
				index++;//����index
			}
			vector<double> dist;
			for (int i = 0; i < Dist.size(); i++) dist.push_back(atof(Dist[i].c_str()));
			lin = Line(atoi(line.c_str()), dist, index);//��ʼ��Line����
		}
	}
	finLine.close();
	return lin;
}

void op3(string s) {
	//��ȡconfig�ļ��е���������
	ifstream config("..\\src\\config.txt", ios::in);
	string speed, headway, start_time, end_time;//��ȡ������ʻ�ٶȣ���ͷʱ�࣬��ʼʱ�䣬��ֹʱ��
	getline(config, speed);
	double vec = atof(speed.c_str());
	getline(config, headway);
	double h = atof(headway.c_str());
	int head = static_cast<int>(h * 60);//�Է��Ӽƣ����ַ��Ӿ���
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
	config.close();//�ر��ļ�

	vector<string> Lines = getLinethrBus(s);//��ȡ����������վ��������·����
	int max = Lines.size();
	cout << "�ù�����վ��" << max << "����·ͨ��\n";
	double Dist, tD;
	int gap1, gap2;//�������ȵ��﹫����վ��������ʱ����Ϣ
	for (int i = 0; i < max; i++) {
		cout << "\n��·" << Lines[i] << "��" << s << "��վ������ʱ�̱�\n";
		Line lin = returnLine(Lines[i], s);
		Dist = lin.D(lin.ind());
		gap1 = static_cast<int>(Dist / vec * 60) + lin.ind();
		tD = lin.TotalD();
		gap2 = static_cast<int>(2 * tD / vec * 60) + 2 * lin.TotalS() - gap1;
		cout << "\n��source���յ�վ��ʱ�̱����£�\n";
		t.adv(0, gap1, 0);
		while (t.early(end)) {
			t.prinTime();
			t.adv(0, head, 0);//�Գ�ͷʱ�����
		}
		t = start;
		cout << "\n���յ�վ��source��ʱ�̱����£�\n";
		t.adv(0, gap2, 0);
		while (t.early(end)) {
			t.prinTime();
			t.adv(0, head, 0);//�Գ�ͷʱ�����
		}
		t = start;
	}
}

string op4_guest(Position p) {
	ifstream finBus("..\\src\\BustopInfo.txt", ios::in);
	string stop_name, loc_x, loc_y, lines;//��ȡ�����������ƣ������ꡢ�����ꡢ������·����
	double min = 1000000.0;
	string min_stop = "source";
	double te;
	while (getline(finBus, stop_name))
	{
		//���ļ��ж�ȡ�����Ϣ
		getline(finBus, loc_x);
		getline(finBus, loc_y);
		getline(finBus, lines);
		//��ȡ������վλ��
		double x = atof(loc_x.c_str());
		double y = atof(loc_y.c_str());
		Position temp = Position(x, y);
		te = p.distance(temp);
		if (te < min) {
			min = te;
			min_stop = stop_name;
		}//���¾�����̵Ĺ�����վ��Ϣ
	}
	finBus.close();
	return min_stop;
}

void op6_guest(string st, string dest) {//���й滮
	if (st == dest) {
		cout << "���о�����̣���ѡ����\n";
	}//�����غ�Ŀ�ĵؾ����㹻�������и���
	else {
		vector<string> LinesofSt = getLinethrBus(st);
		vector<string> LinesofDest = getLinethrBus(dest);
		string sameLine = " ";//��������������վ�Ƿ���ͬһ����·��
		for (int i = 0; i < LinesofSt.size(); i++) {
			for (int j = 0; j < LinesofDest.size(); j++) {
				if (LinesofDest[j] == LinesofSt[i]) sameLine = LinesofDest[j];
			}
		}
		if (sameLine != " ") {//��ͬһ����·�ϲ���Ҫ����
			int step0;
			Line line1 = returnLine(sameLine, st);
			Line line2 = returnLine(sameLine, dest);
			step0 = line1.ind() - line2.ind();
			step0 = step0 > 0 ? step0 : -step0;
			cout << "��" << st << "��վ�ϳ�����" << sameLine << "���ߵ���" << dest << "��վ��;��" << step0 << "����վ" << endl;
		}
		else {//��source��վΪ��תվ����
			Line line1 = returnLine(LinesofSt[0], st);
			Line line2 = returnLine(LinesofDest[0], dest);
			int step1, step2;
			step2 = line2.TotalS() - line2.ind();
			step1 = line1.ind();
			cout << "��" << st << "��վ�ϳ�����" << line1.returnId() << "���ߵ���source��վ��;��" << step1 << "����վ" << endl;
			cout << "��source��վת��" << line2.returnId() << "���ߵ���" << dest << "��վ��;��" << step2 << "����վ" << endl;
		}
	}
	
}

void trip_generate() {//����First-In-Fisrt-Out���ԣ����������ļ���Ϣ����·������Ϣ���Ź������ĳ���
	/*
	config.txt�ļ��Ĵ洢����
	��һ��Ϊ���������ٶȣ��ڶ���Ϊ��ͷʱ�࣬������Ϊϵͳ��ʼ����ʱ�䣬������Ϊϵͳ��ֹ����ʱ��
	*/
	std::ifstream config("..\\src\\config.txt", ios::in);
	string speed, headway, start_time, end_time;//��ȡ������ʻ�ٶȣ���ͷʱ�࣬��ʼʱ�䣬��ֹʱ��
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
	std::ifstream finLine("..\\src\\LineInfo.txt", ios::in);//�����ļ�
	getline(finLine, nums);
	int n = atoi(nums.c_str());//��ȡ��·�����������·����
	int *dur = new int[n];//��¼ÿ����·��תһ��
	std::stack<Bus> w;
	std::queue<Bus> *r = new std::queue<Bus>[n];//���ö���ʵ��FIFO
	int index = 0;
	string line_id, bus_stops, distances;//�ֱ��¼��·���ƣ�������վ�͸���վ֮��ľ���
	Line lin;
	while (getline(finLine, line_id))
	{
		getline(finLine, bus_stops);//��ȡ��վ
		getline(finLine, distances);//��ȡ����
		vector<string> Dist = split(distances, " ");
		vector<double> dist;
		for (int i = 0; i < Dist.size(); i++) dist.push_back(atof(Dist[i].c_str()));
		lin = Line(atoi(line_id.c_str()), dist, 0);
		//����ÿ����·������ʱ�䣬�ٶ�ÿ��������վ���³���ʱһ����
		dur[index] = 2 * static_cast<int>(lin.TotalD() / vec * 60) + 2 * lin.TotalS();
		index++;
	}
	finLine.close();

	int maxdur = dur[0];//ȷ������ϵͳ�Ľ���ʱ��
	for (int i = 0; i < n; i++) {
		if (maxdur < dur[i]) maxdur = dur[i];
	}
	static int m = 100;

	for (int i = m; i >= 1; i--) {
		Bus tem;//��ʼ�����Ա����ʹ��
		tem.changeId(i);
		tem.changeState(n + 1);
		w.push(tem);
	}

	int *num = new int[m];//��¼ÿ���������д���
	for (int i = 0; i < m; i++) num[i] = 0;

	int *nextde = new int[n];
	for (int i = 0; i < n; i++) nextde[i] = 0;
	int gap = start.gap(end);//ϵͳ���ܹ�����ʱ�䣬�Է��Ӽ�

	vector<Bus> res;//��¼ÿ������
	for (int ct = 0; ct <= gap + maxdur; ct++) {
		for (int i = 0; i < n; i++) {
			if (r[i].empty() == false) {
				Bus temp = r[i].front();
				if (temp.returnArrtime() == ct) {
					res.push_back(temp);
					//cout << temp.state + 1 << " " << temp.detime << " " << temp.arrtime << " " << temp.id << endl;
					num[temp.returnId() - 1]++;
					r[i].pop();//�Ӷ���ȡ��������
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
	record.txt�ļ��洢��ʽ
	ÿһ����һ����ʻ��¼���ֱ�Ϊ��·���š��������š�����ʱ�䡢����ʱ��
	*/
	ofstream foutRes("..\\src\\record.txt", ios::out);
	for (int i = 0; i < res.size(); i++) {
		foutRes << res[i].returnState() + 1 << " " << res[i].returnId() << " " << res[i].returnDetime() << " " << res[i].returnArrtime() << endl;
	}
	foutRes.close();
}

int numofLine() {//������·�����е���·������
	ifstream finLine("..\\src\\LineInfo.txt", ios::in);
	string nums;
	getline(finLine, nums);
	int n = atoi(nums.c_str());
	finLine.close();
	return n;
}

void op4_admin() {
	int n = numofLine();
	ifstream finRes("..\\src\\record.txt", ios::in);//��ȡ���м�¼��Ϣ
	int numofBus = 0;//��¼֧������ϵͳ����Ҫ���ܵĹ���������
	int *numofRe = new int[n];//��¼��������ÿ����·�ϵ����д���
	for (int i = 0; i < n; i++) numofRe[i] = 0;
	string record;
	while (getline(finRes, record)) {
		vector<string> res = split(record, " ");
		vector<int> Res;
		for (int i = 0; i < res.size(); i++) Res.push_back(atof(res[i].c_str()));//ת��record��ʽ�����㴦��
		numofRe[Res[0] - 1]++;
		if (Res[1] > numofBus) numofBus = Res[1];
	}
	finRes.close();
	cout << "֧����������ϵͳ����������Ҫ" << numofBus << "��������\n";
	cout << "ÿ����ÿ����·�Ϲ�����Ҫ��ʻ" << numofRe[0] << "������" << endl;
	cout << endl;
}

void op5(int id) {
	int n = numofLine();
	ifstream finRes("..\\src\\record.txt", ios::in);//��ȡ���м�¼��Ϣ
	int num = 0;
	int *numofRe = new int[n];//��¼�ض�id�Ĺ�������ÿ����·�ϵ����д���
	for (int i = 0; i < n; i++) numofRe[i] = 0;
	string record;
	bool run_flag = false;//�����������
	while (getline(finRes, record)) {
		vector<string> res = split(record, " ");
		vector<int> Res;
		for (int i = 0; i < res.size(); i++) Res.push_back(atof(res[i].c_str()));
		if (Res[1] == id) {
			Time t = getNowTime();//��ȡ��ǰʱ��
			Time start = Time(7, 0, 0);
			int gap = t.gap(start);
			if (gap > Res[2] && gap < Res[3]) {//���������ʱ����ڣ������ض���¼��Ӧ����·������
				cout << id << "�ų�������" << Res[0] << "��������\n";
				run_flag = true;
			}
			numofRe[Res[0] - 1]++;
			num++;
		}
	}
	//�����Ϣ
	if (!run_flag) cout << id << "�ų�����û������\n";
	finRes.close();
	cout << id << "�ų�ÿ������" << num << "������\n";
	for (int i = 0; i < n; i++) {
		cout << "ÿ����" << i + 1 << "�����ϸù�����Ҫ��ʻ" << numofRe[i] << "������" << endl;
	}
	cout << endl;
}

void copyF(string fso,string fdes) {//��һ���ļ������ݸ��Ƶ���һ���ļ���
	ifstream finPre(fso, ios::in);
	ofstream fout(fdes, ios::out);
	fout.close();
	ofstream foutLine(fdes, ios::app);
	string line;
	while (getline(finPre, line)) if (line != "") foutLine << line << endl;
	foutLine.close();
	finPre.close();
}

void cleanwork(string line_id) {//ɾ��ĳ����·�����һ��BustopInfo.txt��Bustop_pre.txt�����ļ�����֤��¼��һ����
	ifstream finPreC("..\\src\\BustopInfo_pre.txt", ios::in);
	ofstream foutC("..\\src\\BustopInfo.txt", ios::out);
	foutC.close();
	ofstream foutLineC("..\\src\\BustopInfo.txt", ios::app);
	string id, loc_x, loc_y, lines;
	while (getline(finPreC, id))
	{
		getline(finPreC, loc_x);//��ȡ������
		getline(finPreC, loc_y);//��ȡ������
		getline(finPreC, lines);//��ȡ�����ĸ�����·
		vector<string> res = split(lines, " ");
		foutLineC << id << endl;
		foutLineC << loc_x << endl;
		foutLineC << loc_y << endl;
		for (int i = 0; i < res.size(); i++) {
			if (atoi(res[i].c_str()) > atoi(line_id.c_str())) foutLineC << atoi(res[i].c_str()) - 1 << " ";
			else foutLineC << atoi(res[i].c_str()) << " ";//�����·�����Ƿ���Ҫ����
		}
		foutLineC << endl;
	}
	finPreC.close();
	foutLineC.close();
	copyF("..\\src\\BustopInfo.txt", "..\\src\\BustopInfo_pre.txt");
}

void deleteStop(string s, string line_id) {//ɾ����·ʱ��Ҫȷ���йس�վ�Ƿ���Ҫɾ��
	ifstream finPre("..\\src\\BustopInfo_pre.txt", ios::in);
	ofstream fout("..\\src\\BustopInfo.txt", ios::out);
	fout.close();
	ofstream foutLine("..\\src\\BustopInfo.txt", ios::app);
	string id, loc_x, loc_y, lines;

	while (getline(finPre, id))
	{
		getline(finPre, loc_x);//��ȡ������
		getline(finPre, loc_y);//��ȡ������
		getline(finPre, lines);//��ȡ������������·
		vector<string> res = split(lines, " ");
		if (!strcmp(id.c_str(), s.c_str())) {
			
			if (res.size() < 2) {//�����վֻ������Ҫ��ɾ������·������վɾ��
				std::cout << id << "��վ�Ѿ���ɾ����\n";
				continue;
			}
			else {//���򣬸��³�վ��������·��Ϣ��ɾ����Ҫ�ϳ�����·��Ϣ
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
	//��ȡ�ļ�
	ifstream finPre("..\\src\\LineInfo_pre.txt", ios::in);
	ofstream fout("..\\src\\LineInfo.txt", ios::out);
	fout.close();
	ofstream foutLine("..\\src\\LineInfo.txt", ios::app);
	string nums;
	int num;
	getline(finPre, nums);
	num = atoi(nums.c_str()) - 1;
	foutLine << num << endl;
	string id, bus_stops, distances;//�ֱ��¼��·���ƣ�������վ�͸���վ֮��ľ���
	bool flag = false;//�ж���·����Ҫɾ������·֮ǰ����֮��
	while (getline(finPre, id))
	{
		getline(finPre, bus_stops);//��ȡ��վ
		getline(finPre, distances);//��ȡ����
		if (!strcmp(id.c_str(), line_id.c_str())) {//�ж��Ƿ���Ҫɾ������·
			flag = true;
			vector<string> res = split(bus_stops, " ");
			for (int i = 0; i < res.size(); i++) {
				deleteStop(res[i], line_id);
			}
			continue;
		}
		if (!flag) {//�ж�Ҫ��¼����·����Ҫɾ����·֮ǰ����֮��
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
	cleanwork(line_id);//һЩ������
	std::cout << line_id << "�����Ѿ��ɹ�ɾ����";
	trip_generate();//����ϵͳ���м�¼
}

void updateStop(string s, int n) {
	//��ȡ�ļ�
	ifstream finPre("..\\src\\BustopInfo_pre.txt", ios::in);
	ofstream fout("..\\src\\BustopInfo.txt", ios::out);
	fout.close();
	ofstream foutLine("..\\src\\BustopInfo.txt", ios::app);
	string id, loc_x, loc_y, lines;

	while (getline(finPre, id))
	{
		getline(finPre, loc_x);//��ȡ������
		getline(finPre, loc_y);//��ȡ������
		getline(finPre, lines);//��ȡ��������·����
		vector<string> res = split(lines, " ");
		foutLine << id << endl;
		foutLine << loc_x << endl;
		foutLine << loc_y << endl;
		if (!strcmp(id.c_str(), s.c_str())) {//����ԭ�еĹ�����վ
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
	foutLine << n << endl;//������·�����������
	string line;
	getline(finPre, line);
	while (getline(finPre, line)) if (line != "") foutLine << line << endl;//��ԭ�е���·��Ϣ��������
	finPre.close();
	foutLine << n << endl;
	ifstream finNew("..\\src\\LineInfo_new.txt", ios::in);//��ȡ������·�ľ�����Ϣ

	getline(finNew, line);
	foutLine << line << endl;//������·������վ��Ϣ
	getline(finNew, line);
	foutLine << line << endl;//������·����վ֮��ľ�����Ϣ
	getline(finNew, line);//��ȡԭ�й�����վ��Ϣ
	vector<string> bus_stops_old = split(line, " ");
	for (int i = 0; i < bus_stops_old.size(); i++) {
		updateStop(bus_stops_old[i], n);
	}
	foutLine.close();
	ofstream fout1("..\\src\\BustopInfo.txt", ios::app);
	string name, loc_x, loc_y;//��ȡ����������վ��Ϣ��ֱ�ӷ����ļ�������漴��
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
	cout << "�ɹ�����" << n << "����" << endl;
	trip_generate();//����ϵͳ���м�¼��Ϣ
}