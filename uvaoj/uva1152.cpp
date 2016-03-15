#include <cstdio>
#include <vector>
using namespace std;
const int maxn = 1000099;
int n, a[4005], b[4005], c[4005], d[4005], cnt;
vector<int> vhash[maxn+5];

inline int hash(int num) {
	return num % 500003 + 500005;
}

void init() {
	for (int i = 0; i < maxn; i++) vhash[i].clear();
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
	cnt = 0;
}

void hinit() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int sum = a[i]+b[j];
			vhash[hash(sum)].push_back(sum);
		}
	}
}

void  solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int sum = -1 * (c[i]+d[j]);
			int hsum = hash(sum);
			int len = vhash[hsum].size();
			if (len == 0) continue;
			for (int k = 0; k < len; k++) {
				if (sum == vhash[hsum][k]) cnt++;
			}
		}
	}

}

int main() {
	int T, kase = 0;
	scanf("%d", &T);
	while (T--) {
		init();
		hinit();
		solve();
		if (kase++ > 0) printf("\n");
		printf("%d\n", cnt);
	}
	return 0;
}
