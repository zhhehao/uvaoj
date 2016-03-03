#include <cstdio>
#include <cstring>
int r, c, vis[15][15], b[15][15], ans[35], tmp[35], maxd, maxc;

void init() {
    memset(b, 0, sizeof(b));
    char buf[20];
    maxc = 0;
    for (int i = 0; i < r; i++) {
        scanf("%s", buf);
        for (int j = 0; j < c; j++) {
            if (buf[j] == '#') continue;
            b[i][j] = buf[j] - '0';
            maxc++;
        }
    }
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
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (b[i][j] > 0) {
                if (maxd == maxc-1 && b[i][j] < ans[0]) continue;
                vis[i][j] = 1;
                dfs(0, i, j);
                vis[i][j] = 0;
            }
        }
    }
}

int main() {
//    freopen("data.in", "r", stdin);
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
