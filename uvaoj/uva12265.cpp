#include <cstdio>
#include <cstring>

const int maxn = 1000 + 10;

char land[maxn][maxn];
int hh[maxn], ans[maxn*2], n, m;

struct Rect {
	int c, h;
	Rect(int c = 0, int h = 0):c(c), h(h) {}
} rect[maxn];

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++) scanf("%s", land[i]);

		memset(hh, 0, sizeof(hh));
		memset(ans, 0, sizeof(ans));

		for (int i = 0; i < n; i++) {
			int top = -1;
			for (int j = 0; j < m; j++) {
				if (land[i][j] == '#') {
					hh[j] = 0;
					top = -1;
				}
				else {
					hh[j]++;
					Rect r(j, hh[j]);
					if (top < 0) rect[++top] = r;
					else {
						while (top >= 0 && r.h <= rect[top].h) r.c = rect[top--].c;
						if (top < 0 || r.h-r.c > rect[top].h-rect[top].c) rect[++top] = r;
					}
					ans[j-rect[top].c+rect[top].h+1]++;
				}
			}
		}

		for (int i = 1; i <= n+m; i++)
			if (ans[i]) printf("%d x %d\n", ans[i], i*2);
	}
	return 0;
}
