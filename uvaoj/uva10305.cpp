#include <cstdio>
#include <cstring>
const int maxn = 1000 + 10;
int g[maxn][maxn], c[maxn], ans[maxn], t, n, m;

void dfs(int u) {
	c[u] = -1;
	for (int v = 1; v <= n; v++) {
		if (g[u][v] && !c[v]) dfs(v);
	}
	c[u] = 1;
	ans[--t] = u;
}

int main() {
	while (scanf("%d%d", &n, &m) == 2 && n != 0) {
		memset(g, 0, sizeof(g));
		memset(c, 0, sizeof(c));
		int u, v;
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v) == 2;
			g[u][v] = 1;
		}
		t = n;
		for (int i = 1; i <= n; i++) {
			if (!c[i]) dfs(i);
		}

		for (int i = 0; i < n - 1; i++)
			printf("%d ", ans[i]);
		printf("%d\n", ans[n-1]);
	}
	return 0;
}
