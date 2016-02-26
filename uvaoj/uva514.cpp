#include <iostream>
#include <queue>
#include <stack>
using namespace std;

int main() {
	int t;
	while (cin >> t && t != 0) {
		queue<int> q1, q2;
		stack<int> s1;
		int coach;
		while (cin >> coach && coach != 0) {
			while (!q1.empty()) q1.pop();
			while (!q2.empty()) q2.pop();
			while (!s1.empty()) s1.pop();
			for (int i = 1; i <= t; i++)
				q1.push(i);
			q2.push(coach);
			for (int i = 2; i <= t; i++) {
				cin >> coach;
				q2.push(coach);
			}
			while (q1.front() != q2.front()) {
				s1.push(q1.front());
				q1.pop();
				if (q1.empty()) {
					cout << "No\n";
					goto end;
				}
			}
			q1.pop();
			q2.pop();
			begin:
			if (q2.empty()) {
				cout << "Yes\n";
				goto end;
			}
			else {
				if (s1.empty()) {
					while (q2.front() != q1.front()) {
						s1.push(q1.front());
						q1.pop();
					}
					q2.pop();
					q1.pop();
					goto begin;
				}
				else {
					if (q1.empty()) {
						if (s1.top() != q2.front()) {
							cout << "No\n";
							goto end;
						}
						else {
							s1.pop();
							q2.pop();
							goto begin;
						}
					}
					else {
						if (s1.top() == q2.front()) {
							s1.pop();
							q2.pop();
							goto begin;
						}
						else {
							if (q2.front() == q1.front()) {
								q2.pop();
								q1.pop();
								goto begin;
							}
							else {
								while (q1.front() != q2.front()) {
									s1.push(q1.front());
									q1.pop();
									if (q1.empty()) {
										cout << "No\n";
										goto end;
									}
								}
								q1.pop();
								q2.pop();
								goto begin;
							}
						}
					}
				}
			}
			cout << "Yes\n";
			end:
				continue;
		}
		cout << endl;
	}
	return 0;
}	
