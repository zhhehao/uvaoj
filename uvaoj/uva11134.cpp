#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5000 + 5;
int rec[maxn][4], row[maxn], col[maxn], n, ansx[maxn], ansy[maxn];

struct Cell {
	int s, e, id;
	bool operator < (const Cell& a) const {
		if (e == a.e) {
			return s < a.s;
		}
		else
			return e < a.e;
	}
};

Cell crow[maxn], ccol[maxn];

void init() {
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &rec[i][0], &rec[i][1], &rec[i][2], &rec[i][3]);
		crow[i].s = rec[i][0]; crow[i].e = rec[i][2]; crow[i].id = i;
		ccol[i].s = rec[i][1]; ccol[i].e = rec[i][3]; ccol[i].id = i;
	}
	sort(crow, crow+n);
	sort(ccol, ccol+n);
	memset(row, 0, sizeof(row));
	memset(col, 0, sizeof(col));
}

int solve1() {
	for (int i = 0; i < n; i++) {
		int ok = 0;
		for (int j = crow[i].s; j <= crow[i].e; j++) {
			if (row[j]) continue;
			ansx[crow[i].id] = j;
			row[j] = 1;
			ok = 1;
			break;
		}
		if (!ok) return 0;
	}
	return 1;
}

int solve2() {
	for (int i = 0; i < n; i++) {
		int ok = 0;
		for (int j = ccol[i].s; j <= ccol[i].e; j++) {
			if (col[j]) continue;
			ansy[ccol[i].id] = j;
			col[j] = 1;
			ok = 1;
			break;
		}
		if (!ok) return 0;
	}
	return 1;
}

int main() {
	while (scanf("%d", &n) && n) {
		init();
		if (solve1() && solve2()) {
			for (int i = 0; i < n; i++)
				printf("%d %d\n", ansx[i], ansy[i]);
		}
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}
