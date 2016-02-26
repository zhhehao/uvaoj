#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn = 14349000;
const int b3[15] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969};
int b[15], a[100][2], g[15][15];
int vis[maxn];
int n, m, s, t, maxd, ans;
int bf[15], bff[15];

inline int code() {
    int rem = 0;
    for (int i = 0; i < n; i++) {
        rem += b[i] * b3[i];
    }
    return rem;
}

void init() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    int M = m, N = n-1;
    memset(b, 0, sizeof(b));
    b[s-1] = 2;
    int ob;
    while (M--) {
        scanf("%d", &ob);
        b[ob-1] = 1;
    }
    memset(g, 0, sizeof(g));
    int u, v;
    while (N--) {
        scanf("%d%d", &u, &v);
        g[u-1][v-1] = g[v-1][u-1] = 1;
    }
    memset(vis, 0, sizeof(vis));
    vis[code()] = 1;
    memset(a, 0, sizeof(a));
}

void bfs() {
    memset(bf, 0, sizeof(bf));
    memset(bff, 0, sizeof(bff));
    queue<int> q; q.push(t-1);
    while (!q.empty()) {
        int f = q.front(); q.pop();
        for (int i = 0; i < n; i++) {
            if (i != t-1 && g[f][i] == 1 && bf[i] == 0) {
                bf[i] = bf[f] + 1;
                bff[i] = f;
                q.push(i);
            }
        }
    }
}

inline int getrob() {
    for (int i = 0; i < n; i++)
        if (b[i] == 2) return i;
}

inline int getob(int i) {
    int sum = 0;
    while (i != t-1) {
        sum += b[bff[i]];
        i = bff[i];
    }
    return sum;
}

int dfs(int d) {
//    printf("d is %d, maxd is %d\n",d, maxd);
    if (b[t-1] == 2) return d;
    if (d == maxd) return -2;
    int rob = getrob();
    if (bf[rob] + getob(rob) > maxd - d) return -2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && g[i][j] == 1 && b[i] != 0 && b[j] == 0) {
                b[j] = b[i];
                b[i] = 0;
                int cod = code();
                if (!vis[cod]) {
                    vis[cod] = 1;
                    a[d][0] = i;
                    a[d][1] = j;
                    int ans = dfs(d+1);
                    if (ans >= -1) return ans;
                    vis[cod] = 0;
                }
                b[i] = b[j];
                b[j] = 0;
            }
        }
    }
    return -2;
}

int main() {
    int T, kase = 0;
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    scanf("%d", &T);
    while (T--) {
        init();
        bfs();
//        for (int i = 0; i < n; i++)
//            printf("%d ", bf[i]);
//        printf("\n");
//        for (int i = 0; i < n; i++)
//            printf("%d ", bff[i]);
//        printf("\n");
        for (maxd = 0; ; maxd++) {
            ans = dfs(0);
            if (ans >= -1) break;
        }
        printf("Case %d: %d\n", ++kase, ans);
        if (ans > 0) {
            for (int i = 0; i < ans; i++) {
                printf("%d %d\n", a[i][0]+1, a[i][1]+1);
            }
        }
        printf("\n");
    }
    return 0;
}
