#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
struct Pos {
	int x, y;
};
struct Dice {
	int w, e;
};
Dice dice[7][7];
int board[12][12];
int r, c, sx, sy;
int vis[12][12][12][12];
vector<Pos> ans;
bool nofirst;

bool solve(int x, int y, int d1, int d2) {
	Pos pos; pos.x = x; pos.y = y; ans.push_back(pos);
	vis[x][y][d1][d2] = 1;
//	printf("%d %d\n", x, y);
	if (nofirst) {
		if (x == sx && y == sy) 
			return true;
	}
	nofirst = true;
	if (x-1>=1 && (!vis[x-1][y][d2][7-d1] || (x-1 == sx && y == sy))) {
		if (d1 == board[x-1][y] || board[x-1][y] == -1)  {
				if (solve(x-1, y, d2, 7-d1))
					return true;
		}
	}
	if (x+1<=r && (!vis[x+1][y][7-d2][d1] || (x+1 == sx && y == sy))) { 
		if (d1 == board[x+1][y] || board[x+1][y] == -1) {
				if (solve(x+1, y, 7-d2, d1)) 
					return true;
		}
	}
	if (y-1>=1 && (!vis[x][y-1][dice[d1][d2].w][d2] || (x == sx && y-1 == sy))) {
		if (d1 == board[x][y-1] || board[x][y-1] == -1) {
				if (solve(x, y-1, dice[d1][d2].w, d2)) 
					return true;
		}
	}
	if (y+1<=c && (!vis[x][y+1][dice[d1][d2].e][d2]) || (x == sx && y+1 == sy)) {
		if (d1 == board[x][y+1] || board[x][y+1] == -1) {
				if (solve(x, y+1, dice[d1][d2].e, d2)) 
					return true;
		}
	}
	ans.pop_back();
	return false;
}

int main() {
	char name[25];
	dice[1][2].w = 3; dice[1][2].e = 4;
	dice[1][3].w = 5; dice[1][3].e = 2;
	dice[1][4].w = 2; dice[1][4].e = 5;
	dice[1][5].w = 4; dice[1][5].e = 3;

	dice[2][1].w = 4; dice[2][1].e = 3;
	dice[2][3].w = 1; dice[2][3].e = 6;
	dice[2][4].w = 6; dice[2][4].e = 1;
	dice[2][6].w = 3; dice[2][6].e = 4;

	dice[3][1].w = 2; dice[3][1].e = 5;
	dice[3][2].w = 6; dice[3][2].e = 1;
	dice[3][5].w = 1; dice[3][5].e = 6;
	dice[3][6].w = 5; dice[3][6].e = 2;

	dice[4][1].w = 5; dice[4][1].e = 2;
	dice[4][2].w = 1; dice[4][2].e = 6;
	dice[4][5].w = 6; dice[4][5].e = 1;
	dice[4][6].w = 2; dice[4][6].e = 5;

	dice[5][1].w = 3; dice[5][1].e = 4;
	dice[5][3].w = 6; dice[5][3].e = 1;
	dice[5][4].w = 1; dice[5][4].e = 6;
	dice[5][6].w = 4; dice[5][6].e = 3;

	dice[6][2].w = 4; dice[6][2].e = 3;
	dice[6][3].w = 2; dice[6][3].e = 5;
	dice[6][4].w = 5; dice[6][4].e = 2;
	dice[6][5].w = 3; dice[6][5].e = 4;
	while (scanf("%s", name) == 1 && strcmp(name, "END")) {
		int d1, d2;
		scanf("%d%d%d%d%d%d", &r, &c, &sx, &sy, &d1, &d2) == 6;
		memset(board, 0, sizeof(board));
		for (int i = 1; i <= r; i++) 
			for (int j = 1; j <= c; j++)
				scanf("%d", &board[i][j]) == 1;
		ans.clear();
		memset(vis, 0, sizeof(vis));
		nofirst = false;
		bool result = solve(sx, sy, d1, d2);
		printf("%s\n", name);
		if (!result) {
			printf("  No Solution Possible\n");
			continue;
		}
		for (int i = 0; i < ans.size(); i++) {
			if (i % 9 == 0) printf("  ");
			printf("(%d,%d)", ans[i].x, ans[i].y);
			if (i != ans.size() - 1) printf(",");
			if (i % 9 == 8) printf("\n");
		}
		if (ans.size() % 9 != 0) printf("\n");
	}
	return 0;
}
