#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
struct State {
	int maze[4][6];
	int x, y;
};
State st[100000];
int step[100000][2];
int m, n;
const int dir[16][4] = {0, 0, 0, 0,
						1, 0, 0, 0,
						0, 1, 0, 0,
						1, 1, 0, 0,
						0, 0, 1, 0,
						1, 0, 1, 0,
						0, 1, 1, 0,
						1, 1, 1, 0,
						0, 0, 0, 1,
						1, 0, 0, 1,
						0, 1, 0, 1,
						1, 1, 0, 1,
						0, 0, 1, 1,
						1, 0, 1, 1,
						0, 1, 1, 1,
						1, 1, 1, 1};
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};

void init() {
	n--; m--;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			scanf("%d", &st[1].maze[i][j]);
		}
	}
	st[1].x = m; st[1].y = n;
	step[1][0] = step[1][1] = -1;
}

bool outit(int x, int y, int front) {
	if (x >= 1 && x <= 2 && y >=1 && y <= 4) return false;
	if (x == 0 && dir[st[front].maze[x][y]][1] == 0) {
		step[front+1][0] = front;
		step[front+1][1] = 1;
		return true;
	}
	if (x == 3 && dir[st[front].maze[x][y]][3] == 0) {
		step[front+1][0] = front;
		step[front+1][1] = 3;
		return true;
	}
	if (y == 0 && dir[st[front].maze[x][y]][0] == 0) {
		step[front+1][0] = front;
		step[front+1][1] = 0;
		return true;
	}
	if (y == 5 && dir[st[front].maze[x][y]][2] == 0) {
		step[front+1][0] = front;
		step[front+1][1] = 2;
		return true;
	}
	return false;
}

void pr(int pos) {
	vector<int> v; v.clear();
	while (pos != 1) {
		v.push_back(step[pos][1]);
		pos = step[pos][0];
	}
	for (int i = v.size()-1; i >= 0; i--) {
		if (v[i] == 0) printf("W");
		else if (v[i] == 1) printf("N");
		else if (v[i] == 2) printf("E");
		else if (v[i] == 3) printf("S");
	}
	printf("\n");
}

void bfs() {
	int front = 1, rear = 2;
	while (front < rear) {
		State& s = st[front];
		// printf("x is %d, y is %d\n", s.x, s.y);
		if (outit(s.x, s.y, front)) {
			pr(front+1);
			return;
		}
		for (int i = 0; i < 4; i++) {
			int nx = s.x + dx[i], ny = s.y + dy[i];
			if (nx < 0 || nx > 3 || ny < 0 || ny > 5) continue;
			if (nx == st[step[front][0]].x && ny == st[step[front][0]].y) continue;
			if (dir[s.maze[s.x][s.y]][i] == 0) {
				State& t = st[rear];
				memcpy(t.maze, s.maze, sizeof(s.maze));
				t.x = nx; t.y = ny;
				step[rear][0] = front;
				step[rear][1] = i;
				rear++;
			}
			else if (dir[s.maze[s.x][s.y]][i] == 1 && dir[s.maze[nx][ny]][i] == 0) {
				State& t = st[rear];
				memcpy(t.maze, s.maze, sizeof(s.maze));
				t.x = nx; t.y = ny;
				step[rear][0] = front;
				step[rear][1] = i;
				if (i == 0) {
					t.maze[nx][ny+1] -= 1;
					t.maze[nx][ny] -= 3;
					if (ny > 0) t.maze[nx][ny-1] += 4;
				}
				else if (i == 1) {
					t.maze[nx+1][ny] -= 2;
					t.maze[nx][ny] -= 6;
					if (nx > 0) t.maze[nx-1][ny] += 8;
				}
				else if (i == 2) {
					t.maze[nx][ny-1] -= 4;
					t.maze[nx][ny] += 3;
					if (ny < 5) t.maze[nx][ny+1] += 1;
				}
				else if (i == 3) {
					t.maze[nx-1][ny] -= 8;
					t.maze[nx][ny] += 6;
					if (nx < 3) t.maze[nx+1][ny] += 2;
				}
				rear++;
			}
		}
		front++;
	}
}

int main() {
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	while (scanf("%d%d", &n, &m) == 2 && n) {
		init();
		bfs();
	}
	return 0;
}
