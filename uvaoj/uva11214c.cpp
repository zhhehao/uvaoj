#include <cstdio>
#include <cstring>
int n, m, maxd, ans;
int a[10][10], vis[4][30];
char buf[12];

void init() {
    scanf("%d", &m);
    fgets(buf, 12, stdin);
    memset(a, 0, sizeof(a));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < n; i++) {
        fgets(buf, 12, stdin);
        for (int j = 0; j < m; j++) {
            if (buf[j] == 'X') {
                a[i][j] = 1;
            }
        }
    }
}

inline bool chk() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] && !vis[0][i] && !vis[1][j] && !vis[2][i+j] && !vis[3][i-j+10])
                return false;
        }
    }
    return true;
}

int dfs(int d, int pos) {
    if (chk()) return d;
//    if (maxd == 5) return 5;
    if (d == maxd) return -1;
    for (int i = pos; i < n*m; i++) {
        int r = i / m, c = i % m;
        int t1 = vis[0][r], t2 = vis[1][c], t3 = vis[2][r+c], t4 = vis[3][r-c+10];
        vis[0][r] = vis[1][c] = vis[2][r+c] = vis[3][r-c+10] = 1;
        int ans = dfs(d+1, i);
        if (ans >= 0) return ans;
        vis[0][r] = t1;
        vis[1][c] = t2;
        vis[2][r+c] = t3;
        vis[3][r-c+10] = t4;
    }
    return -1;
}

int main() {
    int kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        init();
        for (maxd = 1; ; maxd++) {
            ans = dfs(0, 0);
            if (ans >= 0) break;
        }
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}
