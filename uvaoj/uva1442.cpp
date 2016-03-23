#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
int n, p[maxn], s[maxn], l[maxn];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d", &p[i]);
		for (int i = 0; i < n; i++) scanf("%d", &s[i]);

		l[0] = s[0];
		for (int i = 1; i < n; i++) {
			if (l[i-1] < p[i]) l[i] = p[i];
			else if (l[i-1] > s[i]) l[i] = s[i];
			else l[i] = l[i-1];

		}

		l[n-1] = min(l[n-1], s[n-1]);
		int ans = l[n-1] - p[n-1];
		for (int i = n-2; i >= 0; i--) {
			if (l[i+1] < p[i]) l[i] = min(p[i], l[i]);
			else if (l[i+1] > s[i]) l[i] = min(s[i], l[i]);
			else l[i] = min(l[i], l[i+1]);
			ans += (l[i] - p[i]);
		}

		printf("%d\n", ans);
	}
	return 0;
}
