#include <cstdio>
#include <cstring>
#include <cctype>
const int maxn = 20;
int n, k;
char b[maxn][maxn], ans[maxn][maxn];

void outp() {
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		printf("%c", ans[i][j]);
    	}
    	printf("\n");
    }
}

void init() {
    memset(b, '\0', sizeof(b));
    memset(ans, '.', sizeof(ans));
    for (int i = 0; i < n; i++) {
    	scanf("%s", b[i]);
    }
}

int dfs(int d, int pos) {
	while (pos != n*n && ans[pos/n][pos%n] != '.') pos++;
	if (pos == n*n) return 1;
	int bx = pos/n, by = pos%n;
	for (int i = bx; i < n; i++) {
		for (int j = by; j < n; j++) {
			int cnt = 0, area = (i-bx+1)*(j-by+1);
			if (area > 9) break;
			if (ans[i][j] != '.') break;
			int now = -1;
			int out = 0;
			for (int x = bx; x < i+1; x++) {
				for (int y = by; y < j+1; y++) {
					if (isdigit(b[x][y])) {
						cnt++;
						now = (b[x][y] - '0');
					}
					if (ans[x][y] != '.') {
						out = 1;
						break;
					}
				}
				if (out || cnt>1 || (now != -1 && now != area)) break;
			}
			if (cnt> 1 || (now != -1 && (area > now || now %(i-bx+1) != 0)) || out) break;
			if (cnt == 0 || now > area) continue;
			for (int x = bx; x < i+1; x++) {
				for (int y = by; y < j+1; y++) {
					ans[x][y] = 'A' + d;
				}
			}
			if (dfs(d+1, pos+(j-by+1))) return 1;
			for (int x = bx; x < i+1; x++) {
				for (int y = by; y < j+1; y++) {
					ans[x][y] = '.';
				}
			}
		}
	}
	return 0;
}

int main() {
    // freopen("data.in", "r", stdin);
    // freopen("data.out", "w", stdout);
    while (scanf("%d%d", &n, &k) == 2 && n) {
        init();
        dfs(0, 0);
        outp();
    }
    return 0;
}
