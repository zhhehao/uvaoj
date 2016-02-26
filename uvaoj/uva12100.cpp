#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n, m;
		cin >> n >> m;
		queue<int> q;
		int a[10];
		memset(a, 0, sizeof(a));
		while (n--) {
			int num;
			cin >> num;
			q.push(num);
			a[num]++;
		}
		int pr = 0;
		for (;;) {
			if (m < 0) {
				cout << pr << endl;
				break;
			}
			int job;
			job = q.front();
			q.pop();
			if (job == 9) {
					pr++;
					m--;
					a[9]--;
					continue;
			}
			bool big = false;
			for (int i = 9; i > job; i--) {
				if (a[i] > 0) {
					big = true;
					break;
				}
			}
			if (big) {
				q.push(job);
				if (m == 0)
					m = q.size() - 1;
				else
					m--;
			}else {
				pr++;
				a[job]--;
				m--;
			}
		}
	}
	return 0;
}
