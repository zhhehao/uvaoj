#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 20 + 2;
int b1[maxn][maxn], b2[maxn][maxn];
struct Grid{ int x, y, m, k;};

void robot(int xe, int ye, int ke) {
	queue<Grid> q; while (!q.empty()) q.pop();
	Grid g; g.x = 1; g.y = 1; g.m = 0; g.k = ke; q.push(g);
	memset(b2, -1, sizeof(b2));
	while (!q.empty()) {
		int x, y, m, k; x = q.front().x; y = q.front().y;
		m = q.front().m; k = q.front().k; q.pop();
		if (x < 1 || y < 1 || x > xe || y > ye) continue;
		if (b2[x][y] >= 0 && b2[x][y] < m) continue;
		if (m > 0 &&  b2[x][y] == m && b1[x][y] == 0) continue;
		if (b1[x][y] == 1 && k == 0) continue;
		b2[x][y] = m;
		if (x==xe && y==ye) break;
		if (b1[x][y] == 0) k = ke;
		else if (b1[x][y] == 1) k--;
		Grid qr;
		qr.x = x+1; qr.y = y; qr.m = m+1; qr.k=k; q.push(qr);
		qr.x = x-1; qr.y = y; qr.m = m+1; qr.k=k; q.push(qr);
		qr.x = x; qr.y = y+1; qr.m = m+1; qr.k=k; q.push(qr);
		qr.x = x; qr.y = y-1; qr.m = m+1; qr.k=k; q.push(qr);
	}
}

int main() {
	int t; scanf("%d", &t);
	while (t--) {
		memset(b1, -1, sizeof(b1));
		int m, n, k; scanf("%d%d%d", &m, &n, &k);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &b1[i][j]);
		robot(m, n, k);
		printf("%d\n", b2[m][n]);
//		for (int i = 0; i <= m; i++) {
//			for (int j = 0; j <= n; j++)
//				printf("%2d", b2[i][j]);
//			printf("\n");
//		}
	}
	return 0;
}
