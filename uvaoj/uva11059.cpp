#include <cstdio>
#include <cstring>
const int maxn = 18 + 2;
int buf[maxn], n;
long long ans;

void solve() {
	for (int s = 0; s < n; s++)
		for (int e = s; e < n; e++) {
			long long num = 1;
			for (int i = s; i <= e; i++)
				num *= buf[i];
			if (num > ans) ans = num;
		}
}

int main() {
	int kase = 0;
	while (scanf("%d", &n) != EOF) {
		memset(buf, 0, sizeof(buf));
		for (int i = 0; i < n; i++) 
			scanf("%d", &buf[i]) == 1;
		ans = 0;
		solve();
		printf("Case #%d: The maximum product is %lld.\n\n", ++kase, ans);
	}
	return 0;
}
