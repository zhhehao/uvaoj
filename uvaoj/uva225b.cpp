#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 100 + 2;
int a[maxn], ans, v1[maxn][maxn], v2[maxn][maxn], v3[maxn][maxn], v4[maxn][maxn];
struct Block {
    int x, y;
};
Block pos;

inline void addblock(int x, int y) {
    if (x >= 0 && y >= 0)
        v1[x][y] = 1;
    else if (x < 0 && y > 0)
        v2[abs(x)][y] = 1;
    else if (x <= 0 && y <= 0)
        v3[abs(x)][abs(y)] = 1;
    else if (x > 0 && y < 0)
        v4[x][abs(y)] = 1;
}

inline void addstop(int x, int y) {
    if (x >= 0 && y >= 0)
        v1[x][y] = 2;
    else if (x < 0 && y > 0)
        v2[abs(x)][y] = 2;
    else if (x <= 0 && y <= 0)
        v3[abs(x)][abs(y)] = 2;
    else if (x > 0 && y < 0)
        v4[x][abs(y)] = 2;
}


inline void delstop(int x, int y) {
    if (x >= 0 && y >= 0)
        v1[x][y] = 0;
    else if (x < 0 && y > 0)
        v2[abs(x)][y] = 0;
    else if (x <= 0 && y <= 0)
        v3[abs(x)][abs(y)] = 0;
    else if (x > 0 && y < 0)
        v4[x][abs(y)] = 0;
}

inline int chk(int x, int y) {
    int ok = 0;
    if (x >= 0 && y >= 0) {
        if (v1[x][y] == 1) ok = 1;
    }
    else if (x < 0 && y > 0) {
        if (v2[abs(x)][y] == 1) ok = 1;
    }
    else if (x <= 0 && y <= 0) {
        if (v3[abs(x)][abs(y)] == 1) ok = 1;
    }
    else if (x > 0 && y < 0) {
        if (v4[x][abs(y)] == 1) ok = 1;
    }

    return ok;
}

inline int chkstop(int x, int y) {
    int ok = 0;
    if (x >= 0 && y >= 0) {
        if (v1[x][y] == 2) ok = 1;
    }
    else if (x < 0 && y > 0) {
        if (v2[abs(x)][y] == 2) ok = 1;
    }
    else if (x <= 0 && y <= 0) {
        if (v3[abs(x)][abs(y)] == 2) ok = 1;
    }
    else if (x > 0 && y < 0) {
        if (v4[x][abs(y)] == 2) ok = 1;
    }
    return ok;
}

inline int mv(int d, int dir) {
    int x, y;
    if (dir == 1) {
        for (int i = 1; i <= d; i++) {
            x = pos.x + i;
            if (chk(x, pos.y)) return 0;
        }
        pos.x += d;
        if (chkstop(pos.x, pos.y)) {pos.x -= d; return 0;}
        return 1;
    }
    else if (dir == 3) {
        for (int i = 1; i <= d; i++) {
            y = pos.y - i;
            if (chk(pos.x, y)) return 0;
        }
        pos.y -= d;
        if (chkstop(pos.x, pos.y)) {pos.y += d; return 0;}
        return 1;
    }
    else if (dir == 2) {
        for (int i = 1; i <= d; i++) {
            y = pos.y + i;
            if (chk(pos.x, y)) return 0;
        }
        pos.y += d;
        if (chkstop(pos.x, pos.y)) {pos.y -= d; return 0;}
        return 1;
    }
    else if (dir == 4) {
        for (int i = 1; i <= d; i++) {
            x = pos.x - i;
            if (chk(x, pos.y)) return 0;
        }
        pos.x -= d;
        if (chkstop(pos.x, pos.y)) {pos.x += d; return 0;}
        return 1;
    }
}

void dfs(int d, int n, int dir) {
//    printf("d is %d, dir is %d\, posx is %d, posy is %d\n", d, dir, pos.x, pos.y);
    a[d] = dir;
    Block tmp1 = pos;
    if (!mv(d, dir)) return;
    if (d == n-2) {
        int cut = 1;
        if ((abs(pos.x) == d+1 && abs(pos.y) == d+2) || (abs(pos.x) == d+2 && abs(pos.y) == d+1))
            cut = 0;
        if (cut) {pos = tmp1; return;}
    }
    if (d == n-1) {
        int cut = 1;
        if (pos.x == 0 || pos.y == 0) cut = 0;
        if (cut) {pos = tmp1; return;}
    }
    if (!pos.x && !pos.y && d != n) {
        pos = tmp1; return;
    }
    if (d == n) {
        if (pos.x == 0 && pos.y == 0) {
            for (int i = 1; i <= n; i++)
                switch(a[i]) {
                    case 1: printf("e"); break;
                    case 2: printf("n"); break;
                    case 3: printf("s"); break;
                    case 4: printf("w"); break;
                }
            printf("\n");
            ans++;
        }
        pos = tmp1;
        return;
    }
    addstop(pos.x, pos.y);
    if (dir == 1 || dir == 4) {
        dfs(d+1, n, 2);
        dfs(d+1, n, 3);
    }
    else if (dir == 2 || dir == 3) {
        dfs(d+1, n, 1);
        dfs(d+1, n, 4);
    }
    delstop(pos.x, pos.y);
    pos = tmp1;
}

int main() {
    int T, n, k;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        memset(v1, 0, sizeof(v1));
        memset(v2, 0, sizeof(v2));
        memset(v3, 0, sizeof(v3));
        memset(v4, 0, sizeof(v4));
        while (k--) {
            int x, y;
            scanf("%d%d", &x, &y);
            addblock(x, y);
        }
        memset(a, 0, sizeof(a));
        ans = 0;
        for (int i = 1; i <= 4; i++) {
                pos.x = pos.y = 0;
                dfs(1, n, i);
        }
        printf("Found %d golygon(s).\n\n", ans);
    }
    return 0;
}
