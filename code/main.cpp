#include "UserInfo.h"
#include "BusStop.h"
#include "Line.h"
#include "Mainworker.h"

using namespace std;

int main() {//主函数，处理登录问题
	cout << "*************************\n*       欢迎使用        *\n*************************\n" << endl;//欢迎信息

	//确认使用者身份
step_id:
	cout << "请选择你的身份（1-管理员 2-乘客）：";
	string identity;
	cin >> identity;
	cout << "\n";
	if (identity == "1") {
		//进行身份验证
		string op;//选择登录或者注册新用户
	step_admin:
		cout << "请选择接下来的操作（1-登录 2-注册）：";
		cin >> op;
	step_config:
		if (op == "1" || op == "2"){
			cout << "请输入用户名：";
			string user, pw;
			cin >> user;
			cout << "请输入密码：";
			pw = inputPassword();//获取输入的密码
			trim(pw);
			//cout << pw << endl;
			UsrInfo usr = UsrInfo(user, pw);
			if (op == "1") {
				int flag_login = login(usr);//验证登录信息
				if (flag_login == 1) {
					cout << "\n\n登录成功!\n\n";
					mainworker_admin();//成功登录之后进行的后续操作

				}
				else if (flag_login == 2) {
					cout << "\n\n账户名不存在，请重试！\n\n";
					goto step_config;//跳回step_config重试
				}
				else {
					cout << "\n\n用户名和密码不匹配，请重试！\n\n";
					goto step_config;//跳回step_config重试
				}
			}
			else {
				int flag_sign = regest(usr);//验证注册信息
				if (flag_sign == 1) {
					cout << "\n\n注册成功\n\n";
					mainworker_admin();//成功登录之后进行的后续操作
				}
				else {
					cout << "\n\n用户名已被占用，请重试！\n\n";
					goto step_config;//跳回step_config重试
				}
			}
		}
		else {
			cout << "输入不合规范，请重试！\n\n";
			goto step_admin;//跳回step_admin重试
		}

	}
	else if (identity == "2") {
		cout << "\n\n";
		mainworker_guest();//乘客进行的后续操作
	}
	else {
		cout << "输入不合规范，请重试！\n\n";
		goto step_id;//跳回step_id重试
	}
	return 0;
}