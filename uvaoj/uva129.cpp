#include <cstdio>
#include <cstring>
const int maxn = 80 + 2;
int n, m, cnt;
char c[maxn];

int dfs(int cur) {
	if (cnt++ == n) {
		for (int i = 0; i < cur; i ++) {
			if (i%4 == 0 && i!=64 && i!=0) printf(" ");
			printf("%c", c[i]);
			if (i == 63 && cur > 64) printf("\n");
		}
		printf("\n%d\n", cur);
		return 0;
	}
	else for (int i = 0; i < m; i++) {
		int ok = 1;
		c[cur] = i + 'A';
		for (int j = 1; j*2 <= cur + 1; j++) {
			int good = 1;
			for (int k = 0; k < j; k++) {
				if (c[cur-k] != c[cur-k-j]) 
					{good = 0; break;}
			}
			if (good) {ok = 0; break;}
		}
		if (ok) {
			if (!dfs(cur+1)) return 0;
		}
	}		
	return 1;
}

int main() {
	while (scanf("%d%d", &n, &m) == 2 && n) {
		memset(c, '\0', sizeof(c));
		cnt = 0;
		dfs(0);
	}
	return 0;
}
