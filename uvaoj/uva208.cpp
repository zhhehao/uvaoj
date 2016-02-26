#include <cstdio>
#include <cstring>
const int maxn = 20 + 2;
int g[maxn][maxn], c[maxn], a[maxn], cnt;

void dfs(int d, int u, int n) {
//    printf("d is %d, u is %d\n", d, u);
    a[d] = u;
    if (u == n) {
        for (int i = 0; i <= d; i++) {
            if (i) printf(" ");
            printf("%d", a[i]);
        }
        printf("\n");
        cnt++;
        return;
    }
    c[u] = -1;
    for (int v = 0; v < maxn; v++)
        if (g[u][v] && c[v] == 0) {
            dfs(d+1, v, n);
        }
    c[u] = 0;
}

int chkst() {
    int ok = 0;
    for (int i = 0; i < maxn; i++)
        if (g[1][i] == 1) {ok = 1; break;}
    return ok;
}

int chken(int n) {
    int ok = 0;
    for (int i = 0; i < maxn; i++)
        if (g[n][i] == 1) {ok = 1; break;}
    return ok;
}

int pathtest(int u, int n) {
    if (u == n) return 1;
    c[u] = -1;
    for (int v = 0; v < maxn; v++)
        if (g[u][v] && c[v] == 0) {
            if (pathtest(v, n)) return 1;
        }
    c[u] = 0;
    return 0;
}

int main() {
    int n, u, v, kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) != EOF) {
        memset(g, 0, sizeof(g));
        while (scanf("%d%d", &u, &v) && u) {
            g[u][v] = g[v][u] = 1;
        }
        memset(a, 0, sizeof(a));
        memset(c, 0, sizeof(c));
        cnt = 0;
        printf("CASE %d:\n", ++kase);
        if (!chkst() || !chken(n)) goto end;
        if (pathtest(1, n)) {
            memset(c, 0, sizeof(c));
            dfs(0, 1, n);
        }
        end:
        printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, n);
    }
    return 0;
}
