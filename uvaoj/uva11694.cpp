#include <cstdio>
#include <cstring>
const int maxn = 7;
const char line[] = {'/', '\\'};
const int dx[] = {-1, -1, 0, 0};
const int dy[] = {-1, 0, -1, 0};
char dot[maxn+1][maxn+1], cell[maxn][maxn];
int n, ox, oy, vis[maxn][maxn];

void init() {
	scanf("%d", &n);
	for (int i = 0; i <= n; i++)
		scanf("%s", dot[i]);
	memset(cell, '\0', sizeof(cell));
}

void pr() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%c", cell[i][j]);
		}
		printf("\n");
	}
}

bool chkdot(int x, int y) {
	if (dot[x][y] == '.') return true;
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i], ny = y + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (i == 0 && cell[nx][ny] == '\\') cnt++;
		else if (i == 1 && cell[nx][ny] == '/') cnt++;
		else if (i == 2 && cell[nx][ny] == '/') cnt++;
		else if (i == 3 && cell[nx][ny] == '\\') cnt++;
	}
	if (cnt == (dot[x][y] - '0')) return true;
	else return false;
}

bool dfscycle(int x, int y, int dir) {
	// printf("cell is %c, x is %d, y is %d, dir is %d\n", cell[x][y], x, y, dir);
	// for (int i = 0; i < n; i++) {
	// 	for (int j = 0; j < n; j++) {
	// 		printf("%d ", vis[i][j]);
	// 	}
	// 	printf("\n");
	// }
	if (x == ox && y == oy) return true;
	if (cell[x][y] == '\\' && dir == 1) {
		int cx = x, cy = y;
		while (cx >= 0 && cy >= 0 && cx < n && cy < n) {
			vis[cx][cy] = 1;
			if (!vis[cx-1][cy] && cell[cx-1][cy] == '/') {
				vis[cx-1][cy] = 1;
				if (dfscycle(cx-1, cy, 2))
					return true;
				vis[cx-1][cy] = 0;
			}
			if (!vis[cx][cy-1] && cell[cx][cy-1] == '/') {
				vis[cx][cy-1] = 1;
				if (dfscycle(cx, cy-1, 4))
					return true;
				vis[cx][cy-1] = 0;
			}
			cx--; cy--;
			if (cell[cx][cy] != '\\') break;
			if (cx == ox && cy == oy) return true;
		}
	}
	else if (cell[x][y] == '\\' && dir == 3) {
		int cx = x, cy = y;
		while (cx >= 0 && cy >= 0 && cx < n && cy < n) {
			vis[cx][cy] = 1;
			if (!vis[cx+1][cy] && cell[cx+1][cy] == '/') {
				vis[cx+1][cy] = 1;
				if (dfscycle(cx+1, cy, 4))
					return true;
				vis[cx+1][cy] = 0;
			}
			if (!vis[cx][cy+1] && cell[cx][cy+1] == '/') {
				vis[cx][cy+1] = 1;
				if (dfscycle(cx, cy+1, 2))
					return true;
				vis[cx][cy+1] = 0;
			}
			cx++; cy++;
			if (cell[cx][cy] != '\\') break;
			if (cx == ox && cy == oy) return true;
		}
	}
	else if (cell[x][y] == '/' && dir == 2) {
		int cx = x, cy = y;
		while (cx >= 0 && cy >= 0 && cx < n && cy < n) {
			vis[cx][cy] = 1;
			if (!vis[cx][cy+1] && cell[cx][cy+1] == '\\') {
				vis[cx][cy+1] = 1;
				if (dfscycle(cx, cy+1, 3))
					return true;
				vis[cx][cy+1] = 0;
			}
			if (!vis[cx-1][cy] && cell[cx-1][cy] == '\\') {
				vis[cx-1][cy] = 1;
				if (dfscycle(cx-1, cy, 1))
					return true;
				vis[cx-1][cy] = 0;
			}
			cx--; cy++;
			if (cell[cx][cy] != '/') break;
			if (cx == ox && cy == oy) return true;
		}
	}
	else if (cell[x][y] == '/' && dir == 4) {
		int cx = x, cy = y;
		while (cx >= 0 && cy >= 0 && cx < n && cy < n) {
			vis[cx][cy] = 1;
			if (!vis[cx][cy-1] && cell[cx][cy-1] == '\\') {
				vis[cx][cy-1] = 1;
				if (dfscycle(cx, cy-1, 1))
					return true;
				vis[cx][cy-1] = 0;
			}
			if (!vis[cx+1][cy] && cell[cx+1][cy] == '\\') {
				vis[cx+1][cy] = 1;
				if (dfscycle(cx+1, cy, 3))
					return true;
				vis[cx+1][cy] = 0;
			}
			cx++; cy--;
			if (cell[cx][cy] != '/') break;
			if (cx == ox && cy == oy) return true;
		}
	}
	return false;
}

bool cycle(int x, int y) {
	if (x == 0 || y == 0) return false;
	if (cell[x][y] == '\\' || cell[x][y-1] == '/') return false;
	memset(vis, 0, sizeof(vis));
	ox = x; oy = y;
	if (dfscycle(x, y-1, 1)) return true;
	else return false;
}

bool chk(int pos) {
	int x = pos /n, y = pos % n;
	if (cycle(x, y)) return false;
	if (!chkdot(x, y)) return false;
	if (y == n-1) {
		if (!chkdot(x, n)) return false;
	}
	if (x == n-1) {
		if (!chkdot(n, y)) return false;
	}
	if (y == n-1 && x == n-1) {
		if (!chkdot(n, n)) return false;
	}
	return true;
}

bool dfs(int pos) {
	if (pos == n * n) return true;
	int x = pos / n, y = pos % n;
	for (int i = 0; i < 2; i++) {
		cell[x][y] = line[i];
		if (chk(pos)) {
			if (dfs(pos+1)) return true;
		}
	}
	return false;
}

int main() {
	int T;
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	scanf("%d", &T);
	while (T--) {
		// for (int i = 0; i < 5; i++)
		// 	scanf("%s", cell[i]);
		// ox = 4; oy = 2; n = 5;
		// memset(vis, 0, sizeof(vis));
		// printf("%d\n", dfscycle(4, 1, 1));
		init();
		dfs(0);
		pr();
	}
	return 0;
}
