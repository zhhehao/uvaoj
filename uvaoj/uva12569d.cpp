#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn = 14349000;
const int b3[15] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969};
int b[15], a[100][2], g[15][15];
int vis[maxn], dist[maxn], ef;
int state[maxn][15];
int n, m, s, t, maxd, ans;
struct Poi{
    int x, y, f;
};

Poi poi[maxn];

inline int code(int* cod) {
    int rem = 0;
    for (int i = 0; i < n; i++) {
        rem += cod[i] * b3[i];
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
    memset(dist, 0, sizeof(dist));
    memset(a, 0, sizeof(a));
//    memset(state, 0, sizeof(state));
}

int bfs() {
    if (b[t-1] == 2) return 0;
    int cod = code(b);
    vis[cod] = 1;
    poi[cod].x = -1; poi[cod].y = -1;
    for (int k = 0; k < n; k++)
        state[cod][k] = b[k];
    queue<int> qt; qt.push(cod);
    while (!qt.empty()) {
        int bt = qt.front(); qt.pop();
        int cbt[15];
        for (int k = 0; k < n; k++)
            cbt[k] = state[bt][k];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && g[i][j] == 1 && cbt[i] != 0 && cbt[j] == 0) {
                    cbt[j] = cbt[i];
                    cbt[i] = 0;
                    int cod2 = code(cbt);
                    if (cbt[t-1] == 2) {
                        ef = cod2;
                        poi[cod2].x = i;
                        poi[cod2].y = j;
                        poi[cod2].f = bt;
                        return dist[bt]+1;
                    }
                    if (!vis[cod2]) {
                        poi[cod2].x = i;
                        poi[cod2].y = j;
                        poi[cod2].f = bt;
                        vis[cod2] = 1;
                        dist[cod2] = dist[bt] + 1;
                        for (int k = 0; k < n; k++)
                            state[cod2][k] = cbt[k];
                        qt.push(cod2);
                    }
                    cbt[i] = cbt[j];
                    cbt[j] = 0;
                }
            }
        }
    }
    return -1;
}

void pr() {
    vector<Poi> vp; vp.clear();
    Poi pp;
    while (poi[ef].x != -1) {
        pp.x = poi[ef].x;
        pp.y = poi[ef].y;
        vp.push_back(pp);
        ef = poi[ef].f;
    }
    for (int i = vp.size()-1; i >= 0; i--)
        printf("%d %d\n", vp[i].x+1, vp[i].y+1);

}

int main() {
    int T, kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    scanf("%d", &T);
    while (T--) {
        init();
        ans = bfs();
        printf("Case %d: %d\n", ++kase, ans);
        if (ans > 0) {
            pr();
        }
        printf("\n");
    }
    return 0;
}
