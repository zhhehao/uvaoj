#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

const int maxn = 200000 + 10;
int n, t[maxn], f[maxn], g[maxn];
map<int, int> mt;

void init() {
	mt.clear();
	f[n-1] = 1;
	for (int i = n-2; i >= 0; i--) {
		if (t[i] < t[i+1]) f[i] = f[i+1] + 1;
		else f[i] = 1;
	}
	g[0] = 1;
	for (int i = 1; i < n; i++) {
		if (t[i] > t[i-1]) g[i] = g[i-1] + 1;
		else g[i] = 1;
	}
}

void solve() {
	int ans = 1;
	mt[t[0]] = g[0];
	for (int i = 1; i < n; i++) {
		map<int, int>::iterator it = mt.lower_bound(t[i]);
		int ok = 1;
		if (it != mt.begin()) {
			ans = max(ans, f[i] + (--it)->second);
			if (g[i] <= it->second) ok = 0;
		}
		if (ok) {
			mt.erase(t[i]);
			mt[t[i]] = g[i];
			it = mt.find(t[i]);
			it++;
			while (it != mt.end() && it->first > t[i] && it->second <= g[i]) mt.erase(it++);
		}
	}
	printf("%d\n", ans);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", &t[i]);
		if (n == 1) {printf("1\n"); continue;}
		init();
		solve();
	}
	return 0;
}
