#include <cstdio>

const int maxn = 100000 + 10;

int n, L;
char buf[maxn];
int s[maxn], p[maxn];

int cmp(int x1, int x2, int x3, int x4) {
	return (s[x2]-s[x1-1])*(x4-x3+1) - (s[x4]-s[x3-1])*(x2-x1+1);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%s", &n, &L, buf+1);

		s[0] = 0;
		for (int i = 1; i <= n; i++) s[i] = s[i-1] + buf[i] - '0';
		int ansL = 1, ansR = L;

		int i = 0, j = 0;
		for (int t = L; t <= n; t++) {
			while (j-i > 1 && cmp(p[j-2], t-L, p[j-1], t-L) >= 0) j--;
			p[j++] = t-L+1;

			while (j-i > 1 && cmp(p[i], t, p[i+1], t) <= 0) i++;
			int c = cmp(p[i], t, ansL, ansR);
			if (c > 0 || c== 0 && t-p[i] < ansR-ansL) {
				ansL = p[i]; ansR = t;
			}
		}
		printf("%d %d\n", ansL, ansR);
	}
	return 0;
}
