#include <cstdio>
#include <cstring>
const int maxn = 7;
const char line[] = {'/', '\\'};
const int dx[] = {-1, -1, 0, 0};
const int dy[] = {-1, 0, -1, 0};
char dot[maxn+1][maxn+1], cell[maxn][maxn];
int n;

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
		if (nx < 0 || nx > n || ny < 0 || ny > n) continue;
		if (i == 0 && cell[nx][ny] == '\\') cnt++;
		else if (i == 1 && cell[nx][ny] == '/') cnt++;
		else if (i == 2 && cell[nx][ny] == '/') cnt++;
		else if (i == 3 && cell[nx][ny] == '\\') cnt++;
	}
	if (cnt == (dot[x][y] - '0')) return true;
	else return false;
}

bool cycle(int x, int y) {
	if (x == 0 || y == 0) return false;
	if (cell[x][y] != '/') return false;
	if (cell[x][y-1] != '\\') return false;
	if (cell[x-1][y-1] != '/') return false;
	if (cell[x-1][y] != '\\') return false;
	return true;
}

bool chk(int pos) {
	int x = pos /n, y = pos % n;
	if (cycle(x, y)) return false;
	if (!chkdot(x, y)) return false;
	if (y == n-1) {
		if (!chkdot(x, y+1)) return false;
	}
	if (x == n-1) {
		if (!chkdot(x+1, y)) return false;
	}
	if (y == n-1 && x == n-1) {
		if (!chkdot(x+1, y+1)) return false;
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
		init();
		dfs(0);
		pr();
	}
	return 0;
}
