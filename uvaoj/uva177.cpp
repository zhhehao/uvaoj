#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 8192 + 5;
int n, cnt, minx, maxy;

struct Line{
	int x, y;
	char ch;
	bool operator < (const Line& b) const {
		if (y == b.y)
			return x < b.x;
		else
			return y < b.y;
	}
} line[maxn];

void rotate(Line& l, int x0, int y0) {
	if (l.ch == '_') {
		int nx = l.x - x0, ny = l.y - y0;
		l.x = ny+x0; l.y = -nx-2+y0; l.ch = '|';
		return;
	}
	else {
		int nx = l.x - x0, ny = l.y - y0;
		l.x = ny+x0; l.y = -nx+y0; l.ch = '_';
		return;
	}
}

void gen(int x0, int y0, int d) {
	if (d == n) return;
	int R = cnt;
	for (int i = 0; i < R; i++) {
		line[cnt] = line[i];
		rotate(line[cnt], x0, y0);
		minx = min(minx, line[cnt].x);
		maxy = max(maxy, line[cnt].y);
		cnt++;
	}
	Line l = line[0];
	rotate(l, x0, y0);
	gen(l.x, l.y+2, d+1);
}

int main() {
	// int kase = 0;
	while (scanf("%d", &n) && n) {
		cnt = 1; minx = 0; maxy = 0;
		line[0].x = 0;
		line[0].y = 0;
		line[0].ch = '_';
		gen(2, 0, 0);
		// printf("%d %d %d\n", minx, maxy, cnt);
		for (int i = 0; i < cnt; i++) {
			line[i].x = line[i].x - minx;
			line[i].y = maxy - line[i].y;
			if (line[i].ch == '_') line[i].x++;
		}
		sort(line, line+cnt);
		// if (kase++) printf("\n");
		if (n == 1) {
			for (int i = 0; i < cnt; i++)
				line[i].x--;
		}
		int cc = 0;
		for (int i = 0; ; i += 2) {
			for (int j = 0; ;j++) {
				if (line[cc].y == i && line[cc].x == j) {
					printf("%c", line[cc].ch);
					if (cc == cnt-1) goto end;
					if (line[cc+1].y > line[cc].y) {
						printf("\n");
						cc++;
						break;
					}
					cc++;
				}
				else
					printf(" ");
			}
		}
		end:
		printf("\n^\n");
	}
	return 0;
}
