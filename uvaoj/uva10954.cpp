#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 5000 + 5;
priority_queue<int, vector<int>, greater<int> > pq;
int n, ans;

int main() {
	while (scanf("%d", &n) == 1 && n) {
		while (!pq.empty()) pq.pop();
		int num;
		for (int i = 0; i < n; i++) {
			scanf("%d", &num);
			pq.push(num);
		}
		ans = 0;
		while (!pq.empty()) {
			int a = pq.top(); pq.pop();
			if (pq.empty()) {
				printf("%d\n", ans);
				break;
			}
			int b = pq.top(); pq.pop();
			int sum = a+b;
			ans += sum;
			pq.push(sum);
		}
	}
	return 0;
}
