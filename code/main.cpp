#include "UserInfo.h"
#include "BusStop.h"
#include "Line.h"
#include "Mainworker.h"

using namespace std;

int main() {//�������������¼����
	cout << "*************************\n*       ��ӭʹ��        *\n*************************\n" << endl;//��ӭ��Ϣ

	//ȷ��ʹ�������
step_id:
	cout << "��ѡ�������ݣ�1-����Ա 2-�˿ͣ���";
	string identity;
	cin >> identity;
	cout << "\n";
	if (identity == "1") {
		//���������֤
		string op;//ѡ���¼����ע�����û�
	step_admin:
		cout << "��ѡ��������Ĳ�����1-��¼ 2-ע�ᣩ��";
		cin >> op;
	step_config:
		if (op == "1" || op == "2"){
			cout << "�������û�����";
			string user, pw;
			cin >> user;
			cout << "���������룺";
			pw = inputPassword();//��ȡ���������
			trim(pw);
			//cout << pw << endl;
			UsrInfo usr = UsrInfo(user, pw);
			if (op == "1") {
				int flag_login = login(usr);//��֤��¼��Ϣ
				if (flag_login == 1) {
					cout << "\n\n��¼�ɹ�!\n\n";
					mainworker_admin();//�ɹ���¼֮����еĺ�������

				}
				else if (flag_login == 2) {
					cout << "\n\n�˻��������ڣ������ԣ�\n\n";
					goto step_config;//����step_config����
				}
				else {
					cout << "\n\n�û��������벻ƥ�䣬�����ԣ�\n\n";
					goto step_config;//����step_config����
				}
			}
			else {
				int flag_sign = regest(usr);//��֤ע����Ϣ
				if (flag_sign == 1) {
					cout << "\n\nע��ɹ�\n\n";
					mainworker_admin();//�ɹ���¼֮����еĺ�������
				}
				else {
					cout << "\n\n�û����ѱ�ռ�ã������ԣ�\n\n";
					goto step_config;//����step_config����
				}
			}
		}
		else {
			cout << "���벻�Ϲ淶�������ԣ�\n\n";
			goto step_admin;//����step_admin����
		}

	}
	else if (identity == "2") {
		cout << "\n\n";
		mainworker_guest();//�˿ͽ��еĺ�������
	}
	else {
		cout << "���벻�Ϲ淶�������ԣ�\n\n";
		goto step_id;//����step_id����
	}
	return 0;
}