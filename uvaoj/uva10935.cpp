#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
	int n;
	while ((cin >> n) && (n != 0)) {
		queue<int> q;
		vector<int> v;
		for (int i = 1; i <= n; i++)
			q.push(i);
		while (q.size() > 1) {
			v.push_back(q.front());
			q.pop();
			q.push(q.front());
			q.pop();
		}
		
		cout << "Discarded cards:";
		int kase = 1;
		for (int i = 0; i < v.size(); i++) {
			if (kase++ > 1) cout << ",";
			cout << " " << v[i];
		}
		cout <<"\nRemaining card: " << q.front() << endl;

		q.pop();
		v.resize(0);
	}
	return 0;
}
