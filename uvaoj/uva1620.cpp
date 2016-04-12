#include <cstdio>

const int maxn = 500 + 5;

int n, s[maxn];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &s[i]);
			for (int j = 0; j < i; j++) {
				if (s[j] > s[i])
					cnt++;
			}
		}
		if (!(cnt & 1) || !(n & 1))
			printf("possible\n");
		else
			printf("impossible\n");
	}
	return 0;
}
