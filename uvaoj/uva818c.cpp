#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 15 + 2;
// g¥Ê¥¢’˚’≈Õº
int g[maxn][maxn], maxd, n, c[maxn], ans;

void outputg() {
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++)
            printf("%2d", g[i][j]);
        printf("\n");
    }
}

inline void split(int a) {
    for (int i = 1; i <= n; i++) {
        g[a][i] = g[i][a] = 0;
    }
}

inline bool getdgree() {
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (g[i][j] == 1) cnt++;
        if (cnt > 2) return false;
    }
    return true;
}

inline bool cycle(int u, int s) {
    c[u] = -1;
    for (int v = 1; v <= n; v++) {
        if (g[u][v] && v != s) {
            if (c[v] < 0) return false;
            else if (!c[v] && !cycle(v, u))  return false;
        }
    }
    c[u] = 1;
    return true;
}

inline int iscycle() {
    memset(c, 0, sizeof(c));
    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        if (!c[u]) {
            if (!cycle(u, 0)) {
                    return -1;
            }
            cnt++;
        }
    }
    return cnt;
}

inline void judge(int s) {
    int cnt = 0;
    for (int i = 0; i < n; i++)
        if (s&(1<<i)) {
            split(i+1);
            cnt++;
        }
//    outputg();
    if (!getdgree()) return;
    int seg = iscycle();
//    printf("seg is %d, cnt is %d\n", seg, cnt);
    if (seg < 0) return;
    if ((seg-cnt) <= (cnt+1))
        ans = min(ans, cnt);
}

int solve() {
    ans = 20;
    int bak[maxn][maxn];
    memcpy(bak, g, sizeof(g));
    for (int i = 0; i < (1<<n); i++) {
        judge(i);
        memcpy(g, bak, sizeof(g));
    }
}

int main() {
    int u, v, kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        memset(g, 0, sizeof(g));
        while (scanf("%d%d", &u, &v) == 2 && u != -1) {
            g[u][v] = g[v][u] = 1;
        }
//        outputg();
//        printf("\n");
        solve();
        printf("Set %d: Minimum links to open is %d\n", ++kase, ans);
    }
    return 0;
}
