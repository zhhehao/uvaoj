#include <set>
#include <queue>
#include <string>
#include <iostream>
using namespace std;

const int MAXN = 1005;
set<int> t[MAXN];

int main() {
	int n, m, members;
	int kase = 1;
	for (;;) {
		queue<int> q[MAXN];
		queue<int> qt;
		cin >> n;
		if (n == 0) break;
		for (int i = 0; i < n; i++) {
			cin >> m;
			t[i].clear();
			for (int j = 0; j < m; j++) {
				cin >> members;
				t[i].insert(members);
			}
		}
		cout << "Scenario #" << kase++ << endl;
		string cmd;
		int staff;
		for (;;) {
			cin >> cmd;
			if (cmd[0] == 'S') break;
			if (cmd[0] == 'E') {
				cin >> staff;
				int team;
				for (int i = 0; i < n; i++) 
					if (t[i].count(staff) == 1) team = i;
				if (q[team].empty()) qt.push(team);
				q[team].push(staff);
			}
			if (cmd[0] == 'D') {
				int team = qt.front();
				cout << q[team].front() << endl;
				q[team].pop();
				if (q[team].empty())
						qt.pop();
			}
		}
		cout << endl;
	}
	return 0;
}
