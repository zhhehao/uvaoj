#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int maxn = 800000 + 10;

struct Job{
	int q, d;
	bool operator < (const Job& b) const {
		return d < b.d;
	}
} job[maxn];

int n;

int main() {
	int T, kase = 0; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%d", &job[i].q, &job[i].d);
		sort(job, job+n);
		priority_queue<int> pq;
		// while (!pq.empty()) pq.pop();

		int ans = 0, t = 0;
		for (int i = 0; i < n; i++) {
			ans++;
			t += job[i].q;
			pq.push(job[i].q);
			if (t > job[i].d) {
				ans--;
				t -= pq.top();
				pq.pop();
			}
		}
		if (kase++) printf("\n");
		printf("%d\n", ans);
	}
	return 0;
}
