#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int r, c, vis[15][15], b[15][15], ans[35], tmp[35], maxd, maxc;

struct Maze {
    int value, x, y;
    bool operator < (const Maze& a) const {
        return value > a.value;
    }
};

Maze maze[35];

void init() {
    memset(b, 0, sizeof(b));
    char buf[20];
    maxc = 0;
    for (int i = 0; i < r; i++) {
        scanf("%s", buf);
        for (int j = 0; j < c; j++) {
            if (buf[j] == '#') continue;
            b[i][j] = buf[j] - '0';
            maze[maxc].value = b[i][j];
            maze[maxc].x = i;
            maze[maxc].y = j;
            maxc++;
        }
    }
    sort(maze, maze+maxc);
//    printf("maxc is %d\n", maxc);
}

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void dfs(int d, int x, int y) {
    tmp[d] = b[x][y];
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < r && ny >= 0 && ny < c && b[nx][ny] > 0 && !vis[nx][ny]) {
            vis[nx][ny] = 1;
            dfs(d+1, nx, ny);
            vis[nx][ny] = 0;
        }
        if (d < maxd) continue;
        else if (d > maxd) {
            maxd = d;
            memcpy(ans, tmp, sizeof(ans));
        }
        else if (d == maxd) {
            if (memcmp(tmp, ans, sizeof(ans)) > 0) {
                memcpy(ans, tmp, sizeof(ans));
            }
        }
    }
}

void solve() {
    maxd = 0;
    memset(ans, 0, sizeof(ans));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < maxc; i++) {
        if (maxd == maxc-1 && maze[i].value < ans[0]) break;
        vis[maze[i].x][maze[i].y] = 1;
        dfs(0, maze[i].x, maze[i].y);
        vis[maze[i].x][maze[i].y] = 0;
    }
}

int main() {
////    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (scanf("%d%d", &r, &c) == 2 && r) {
        init();
        solve();
        for (int i = 0; i <= maxd; i++)
            printf("%d", ans[i]);
        printf("\n");
    }
    return 0;
}
