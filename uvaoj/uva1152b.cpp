#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 4000 + 5;
int n, a[maxn], b[maxn], c[maxn], d[maxn], sum[maxn*maxn], cnt, ans;

int main() {
	int T, kase = 0;
	scanf("%d", &T);
	while (T--) {
		cnt = ans = 0;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%d%d%d", &a[i], &b[i], &c[i], &d[i]);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				sum[cnt++] = a[i] + b[j];
			}
		}
		sort(sum, sum+cnt);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ans += upper_bound(sum, sum+cnt, -c[i]-d[j]) - lower_bound(sum, sum+cnt, -c[i]-d[j]);
			}
		}
		if (kase++ > 0) printf("\n");
		printf("%d\n", ans);
	}
	return 0;
}
