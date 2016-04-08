#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, m, k, s[maxn], vis[maxn];

bool solve() {
	memset(vis, 0, sizeof(vis));
	s[1] = 1; s[2] = 2; s[3] = 3;
	vis[1] = vis[2] = vis[3] = 1;
	int L = 1, R = 4, cnt = 3, ans = n+1, tmp;

	while (R <= n) {
		s[R] = (s[R-1]+s[R-2]+s[R-3]) % m + 1;
		tmp = s[R++];
		vis[tmp]++;
		if (tmp <= k && vis[tmp] == 1) cnt++;

		while (L < R && cnt == k) {
			ans = min(ans, R-L);
			tmp = s[L++];
			vis[tmp]--;
			if (tmp <= k && vis[tmp] == 0) cnt--;
		}
	}
	if (ans <= n) {
		printf("%d\n", ans);
		return true;
	}
	return false;
}

int main() {
	int T, kase = 0; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &n, &m, &k);
		printf("Case %d: ", ++kase);
		if (k == 1) {printf("1\n"); continue;}
		if (k == 2) {printf("2\n"); continue;}
		if (k == 3) {printf("3\n"); continue;}
		if (!solve())
			printf("sequence nai\n");
	}
	return 0;
}
