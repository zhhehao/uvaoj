#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
const int maxn = 11;
int b[maxn][maxn], sqname, ub[maxn][maxn], fk[60], maxd, mk[60];
int a[30];
struct MS {
    vector<int> sq;
    set<int> ssq;
    int name;
};
vector<MS> ms;

inline int caldis(int x, int y, int n) {
    int minx = min(2*n - x, x);
    int miny = min(2*n - y, y);
    return min(minx, miny);
}

inline void initsquare(int x, int y, int a) {
    int va = ub[x][y];
    int x1 = x - a;
    int x2 = x + a;
    int y1 = y - a;
    int y2 = y + a;
    for (int i = x1; i <= x2; i++) {
        if (b[i][y1] > 0) {
            if (!ms[b[i][y1]-1].ssq.count(va)) {
                ms[b[i][y1]-1].ssq.insert(va);
                ms[b[i][y1]-1].sq.push_back(va);
            }
            if (!ms[b[i][y2]-1].ssq.count(va)) {
                ms[b[i][y2]-1].ssq.insert(va);
                ms[b[i][y2]-1].sq.push_back(va);
            }
        }
    }
    for (int i = y1; i <= y2; i++) {
        if (b[x1][i] > 0) {
            if (!ms[b[x1][i]-1].ssq.count(va)) {
                ms[b[x1][i]-1].ssq.insert(va);
                ms[b[x1][i]-1].sq.push_back(va);
            }
            if (!ms[b[x2][i]-1].ssq.count(va)) {
                ms[b[x2][i]-1].ssq.insert(va);
                ms[b[x2][i]-1].sq.push_back(va);
            }
        }
    }
}


void initmatch(int a, int n) {
    for (int i = 1; i < 2*n; i++)
        for (int j = 1; j < 2*n; j++)
            if (b[i][j] == 0) {
                int dis = caldis(i, j, n);
                if (dis == a || (dis%2 == a%2 && dis > a)) {
                    ub[i][j] = sqname++;
                    initsquare(i, j, a);
                }
            }

}

inline int cntsq() {
    int cnt = 0;
    for (int i = 1; i < sqname; i++)
        if (fk[i] == 0) cnt++;
    return cnt;
}

void init(int n) {
    ms.clear(); MS m;
    int cnt = 0, num = 1;
    for (int i = 0; i < 2*n+1; i++)
        for (int j = 0; j < 2*n+1; j++) {
            if (cnt++ % 2 == 0) {
                b[i][j] = 0;
                ub[i][j] = 0;
            }
            else {
                m.name = num++;
                b[i][j] = m.name;
                ms.push_back(m);
            }
        }
    sqname = 1;
    for (int i = 1; i <= n; i++)
        initmatch(i, n);
    memset(fk, 0, sizeof(fk));

//    for (int i = 0; i < 2*n+1; i++) {
//        for (int j = 0; j < 2*n+1; j++)
//            printf("%3d", ub[i][j]);
//        printf("\n");
//    }
//    printf("\n");
//    for (int i = 0; i < 2*n+1; i++) {
//        for (int j = 0; j < 2*n+1; j++)
//            printf("%3d", b[i][j]);
//        printf("\n");
//    }
}

struct D {
    int id, siz;
    bool operator < (const D& a) const {
        return siz > a.siz;
    }
};

inline int msiz(int a) {
    int cnt = 0;
    for (int i = 0; i < ms[a].sq.size(); i++)
        if (fk[ms[a].sq[i]] == 0) cnt++;
    return cnt;
}

int dfs(int d) {
//    printf("d is %d, sq is %d\n", d, cntsq());
    if (cntsq() == 0) return d;
    if (d == maxd) return -1;
    int tf[60], tm[60];
    memcpy(tf, fk, sizeof(fk));
    memcpy(tm, mk, sizeof(mk));
    vector<D> dd; dd.clear();
    for (int i = 0; i < ms.size(); i++)
        if (mk[i] == 1) {
            D d1; d1.id = i; d1.siz = msiz(i);
            dd.push_back(d1);
        }
    sort(dd.begin(), dd.end());
    if (dd[0].siz == 1) return cntsq() + d;
    int k = cntsq(), cnt = 0;
    for (int i = 0; i < dd.size(); i++) {
        cnt += dd[i].siz;
        if (cnt < k) continue;
        if (i+1+d> maxd) return -1;
    }

    for (int i = 0; i < dd.size(); i++) {
        mk[dd[i].id] = 0;
        a[d] = dd[i].id;
        for (int j = 0; j < ms[dd[i].id].sq.size(); j++)
            fk[ms[dd[i].id].sq[j]] = 1;
        int ans = dfs(d+1);
        if (ans > 0) return ans;
        memcpy(fk, tf, sizeof(fk));
        memcpy(mk, tm, sizeof(mk));
    }
    return -1;
}

int main() {
    int t, n, k, ans;
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    scanf("%d", &t) == 1;
    while (t--) {
        scanf("%d%d", &n, &k) == 2;
        memset(b, 0, sizeof(b));
        memset(ub, -1, sizeof(ub));
        memset(mk, 0, sizeof(mk));
        init(n);
        for (int i = 0; i < ms.size(); i++)
            mk[i] = 1;
        int match;
        while (k--) {
            scanf("%d", &match) == 1;
            for (int i = 0; i < ms.size(); i++)
                if (ms[i].name == match) {
                    for (int j = 0; j < ms[i].sq.size(); j++) {
                        fk[ms[i].sq[j]] = 1;
                    }
                    break;
                }
            mk[match-1] = 0;
        }

        for (maxd = 1;   ; maxd++) {
            ans = dfs(0);
            if (ans > 0) break;
        }
        printf("%d\n", ans);
    }
    return 0;
}
