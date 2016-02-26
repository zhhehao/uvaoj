#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 15 + 2;
// a存储各个度数的个数，b存储各个环的度数，g存储整张图
int a[maxn], b[maxn], g[maxn][maxn], maxd, n, c[maxn];

void outputg() {
    for (int i = 0; i < maxn; i++) {
        for (int j = 0; j < maxn; j++)
            printf("%2d", g[i][j]);
        printf("\n");
    }
}

void outputdgree() {
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    for (int i = 1; i <= n; i++)
        printf("%d ", b[i]);
    printf("\n");
}

inline void split(int a) {
    for (int i = 1; i <= n; i++) {
        if (g[a][i]) {
            g[i][a] = g[a][i] = 0;
        }
    }
}

inline void split2(int a, int b) {
    g[a][b] = g[b][a] = 0;
}

inline void emerge(int a, int b) {
    g[a][b] = g[b][a] = 1;
}

inline void getdgree() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++)
            if (g[i][j] == 1) cnt++;
        b[i] = cnt;
        a[cnt]++;
    }
}

inline void getcom(int a, vector<int>& v) {
    for (int i = 1; i <= n; i++)
        if (g[a][i]) v.push_back(i);
}

inline void cycle(int u) {
    c[u] = 1;
    for (int v = 1; v <= n; v++) {
        if (g[u][v] && !c[v])
            cycle(v);
    }
}

inline int iscycle() {
    memset(c, 0, sizeof(c));
    for (int u = 1; u <= n; u++) {
        if (!c[u]) {
            cycle(u);
            break;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (c[i]) ans++;
    return ans;
}

int dfs(int d) {
//    printf("d is %d, maxd is %d\n", d, maxd);
    getdgree();
    if (a[1] == 2 && a[2] == n-2 && iscycle()==n) return d;
    if (d == maxd) return -1;
    int tmp[maxn]; memcpy(tmp, a, sizeof(a));
    for (int i = 1; i <= n; i++) {
        vector<int> linkcom; linkcom.clear();
        getcom(i, linkcom);
        split(i);
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                emerge(i, j);
                getdgree();
                if (a[1] == 2 && a[2] == n-2 && iscycle()==n) return d + 1;
                for (int k = 1; k <= n; k++) {
                    if (i != k && j != k) {
                        emerge(i, k);
                        getdgree();
                        if (memcmp(tmp, a, sizeof(a))) {
                            int ans = dfs(d+1);
                            if (ans >= 0) return ans;
                        }
                        split2(i, k);
                    }
                }
                split2(i, j);
            }
        }
        for (int j = 0; j < linkcom.size(); j++)
            emerge(i, linkcom[j]);
    }
    return -1;
}

int main() {
    int u, v, kase = 0;
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        memset(g, 0, sizeof(g));
        while (scanf("%d%d", &u, &v) == 2 && u != -1) {
            g[u][v] = g[v][u] = 1;
        }
        int ans;
        for (maxd = 1; ; maxd++) {
            ans = dfs(0);
            if (ans >= 0) break;
        }
//        printf("cycle is %d\n", iscycle());
        printf("Set %d: Minimum links to open is %d\n", ++kase, ans);
    }
    return 0;
}
