#include <cstdio>
#include <cstring>

const int maxn = 100000 + 10;
int s, n, c[maxn*3], vis[maxn], ok[maxn*2];

int main() {
	int t;
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &s, &n);
		memset(c, -1, sizeof(c));
		for (int i = 0; i < n; i++) scanf("%d", &c[i+s]);
		int tot = 0;
		memset(vis, 0, sizeof(vis));
		memset(ok, 0, sizeof(ok));
		for (int i = 0; i < n+s+1; i++) {
			if (tot == s) ok[i] = 1;
			if (i < s && tot == i) ok[i] = 1;
			if (i > n && tot == n+s-i) ok[i] = 1;
			if (i == n+s) break;
			if (c[i] != -1 && --vis[c[i]] == 0) tot--;
			if (c[i+s] != -1 && vis[c[i+s]]++ == 0) tot++;
		}
		int ans = 0;
		for (int i = 0; i < s; i++) {
			int yes = 1;
			for (int j = i; j < n+s+1; j += s)
				if (!ok[j]) {yes = 0; break;}
			if (yes) ans++;
		}
		if (ans == n+1) ans = s;
		printf("%d\n", ans);
	}
	return 0;
}
