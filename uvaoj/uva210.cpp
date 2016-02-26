#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

struct Program {
	int id;
	deque<string> qcmd;
};

int main() {
	int t;
	cin >> t;
	string str;
	getline(cin, str); // 吃掉一个回车
	int kase = 1;
	while (t--) {
		if (kase++ > 1) cout << endl; // 连续两个输出之间有一个空行
		getline(cin, str); // 吃掉一个空行
		int n, t1, t2, t3, t4, t5, tq;
		cin >> n >> t1 >> t2 >> t3 >> t4 >> t5 >> tq;
		getline(cin, str); // 吃掉一个回车
		vector<Program> vp;
		deque<int> dqr;
		for (int i = 0; i < n; i++) { // 输入每个程序
			Program program;
			program.id = i;
			dqr.push_back(program.id);
			for (;;) {
				getline(cin, str);
				program.qcmd.push_back(str);
				if (str[2] == 'd') break;
			}
			vp.push_back(program);
		}
		bool lock = false; // 标记lock状态
		int lockid;
		int var[26];
		memset(var, 0, sizeof(var));
		queue<int> qb;
		for (;;) {
			int id, time;
			if (dqr.empty()) break; // 所有程序执行完毕
			id = vp[dqr.front()].id;
			dqr.pop_front();
			string cmd;
			time = tq;
			do {
				cmd = vp[id].qcmd.front();
				vp[id].qcmd.pop_front();
				if (cmd[2] == '=') {
//					if (lock && lockid != id) {
//					time -= t1;
//					continue;
//					}
					stringstream ss(cmd);
					string vari, nouse;
					int value;
					ss >> vari >> nouse >> value;
					var[vari[0]-'a'] = value;
					time -= t1;
				} else if (cmd[2] == 'i') {
					cout << vp[id].id + 1;
					cout << ": ";
					cout << var[cmd[cmd.size()-1]-'a'] << endl;
					time -= t2;
				} else if (cmd[2] == 'c') {
					if (lock) {
						vp[id].qcmd.push_front(cmd);
						qb.push(id);
						goto end;
					} else {
						lock = true;
						lockid = id;
					}
					time -= t3;
				} else if (cmd[2] == 'l') {
					lock = false;
					time -= t4;
					if (!qb.empty()) {
						dqr.push_front(qb.front());
						qb.pop();
					}
				} else if (cmd[2] == 'd') {
					break;
				}
			} while (time > 0);
			if (!vp[id].qcmd.empty())
				dqr.push_back(id);
			end:
				continue;
		}
	}
	return 0;
}
