#include <cstdio>
#include <cstring>
const int maxn = 100 + 5;
char oil[maxn][maxn];
int buf[maxn][maxn];
int m, n;

void dfs(int x, int y, int v) {
	buf[x][y] = v;
	if (x-1>=0) {
		if (y-1>=0 && oil[x-1][y-1] == '@' && buf[x-1][y-1] == 0) dfs(x-1, y-1, v);
		if (y+1<n && oil[x-1][y+1] == '@' && buf[x-1][y+1] == 0) dfs(x-1, y+1, v);
		if (oil[x-1][y] == '@' && buf[x-1][y] == 0) dfs(x-1, y, v);
	}
	if (x+1<m) {
		if (y-1>=0 && oil[x+1][y-1] == '@' && buf[x+1][y-1] == 0) dfs(x+1, y-1, v);
		if (y+1<n && oil[x+1][y+1] == '@' && buf[x+1][y+1] == 0) dfs(x+1, y+1, v);
		if (oil[x+1][y] == '@' && buf[x+1][y] == 0) dfs(x+1, y, v);
	}
	if (y-1>=0 && oil[x][y-1] == '@' && buf[x][y-1] == 0) dfs(x, y-1, v);
	if (y+1<n && oil[x][y+1] == '@' && buf[x][y+1] == 0) dfs(x, y+1, v);

}

int main() {
	while (scanf("%d%d", &m, &n) == 2 && m != 0) {
		memset(oil, '\0', sizeof(oil));
		memset(buf, 0, sizeof(buf));
		for (int i = 0; i < m; i++) scanf("%s", oil[i]) == 1;
		int cnt = 1;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				if (oil[i][j] == '@' && buf[i][j] == 0)
					dfs(i, j, cnt++);
//		for (int i = 0; i < m; i++) {
//			for (int j = 0; j < n; j++)
//				printf("%d ", buf[i][j]);
//			printf("\n");
//		}
		printf("%d\n", cnt-1);
	}
	return 0;
}
