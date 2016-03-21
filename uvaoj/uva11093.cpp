#include <cstdio>
typedef long long LL;

const int maxn = 100000 + 10;
int p[maxn], q[maxn], ans, n;

bool cycle(int s) {
	int ps = 0, qs = 0, cnt = n;
	ans = s;
	while (cnt--) {
		ps += p[s];
		qs += q[s];
		if (qs > ps) {
			ans = s + 1;
			return false;
		}
		ps -= qs;
		qs = 0;
		if (s == n)
			s = 1;
		else
			s++;
	}
	return true;
}

int main() {
	int t, kase = 0; scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		LL sp = 0, sq = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &p[i]);
			sp += p[i];
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &q[i]);
			sq += q[i];
		}
		if (sp < sq) {printf("Case %d: Not possible\n", ++kase); continue;}
		ans = 1;
		int ok = 0, s = 1;
		while (s <= n) {
			if (cycle(s)) {
				ok = 1; break;
			}
			else
				s = ans;
		}
		if (ok)
			printf("Case %d: Possible from station %d\n", ++kase, ans);
		else
			printf("Case %d: Not possible\n", ++kase);
	}
	return 0;
}
