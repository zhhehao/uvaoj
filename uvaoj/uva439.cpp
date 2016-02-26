#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int board[8][8];
struct Point{int x, y, m;};
int knight(int x1, int y1, int x2, int y2) {
	queue<Point> q; Point point; point.x = x1; point.y = y1; point.m = 0; q.push(point);
	while (!q.empty()) {
		int x, y, m; x = q.front().x; y = q.front().y; m = q.front().m; q.pop();
		board[x][y] = m;
		if (x == x2 && y == y2) break;
		Point p;
		if (x-1>=0 && y-2>=0) {p.x = x-1; p.y = y-2; p.m = m + 1; q.push(p);}
		if (x-1>=0 && y+2<=7) {p.x = x-1; p.y = y+2; p.m = m + 1; q.push(p);}
		if (x-2>=0 && y-1>=0) {p.x = x-2; p.y = y-1; p.m = m + 1; q.push(p);}
		if (x-2>=0 && y+1<=7) {p.x = x-2; p.y = y+1; p.m = m + 1; q.push(p);}
		if (x+1<=7 && y-2>=0) {p.x = x+1; p.y = y-2; p.m = m + 1; q.push(p);}
		if (x+1<=7 && y+2<=7) {p.x = x+1; p.y = y+2; p.m = m + 1; q.push(p);}
		if (x+2<=7 && y-1>=0) {p.x = x+2; p.y = y-1; p.m = m + 1; q.push(p);}
		if (x+2<=7 && y+1<=7) {p.x = x+2; p.y = y+1; p.m = m + 1; q.push(p);}
	}
	return board[x2][y2];
}

int main() {
	char be[2], en[2];
	while (scanf("%s", be) != EOF) {
		memset(board, 0, sizeof(board));
		scanf("%s", en) == 1;
		int x1 = be[1]-'1', y1 = be[0]-'a', x2 = en[1]-'1', y2 = en[0]-'a';
		printf("To get from %c%c to %c%c takes %d knight moves.\n",
				be[0], be[1], en[0], en[1], knight(x1, y1, x2, y2));
	}
	return 0;
}
