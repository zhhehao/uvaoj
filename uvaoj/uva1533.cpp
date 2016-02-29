#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 32767 + 5;
typedef int State[16];
State st[maxn], goal;
int vis[maxn], b[16][16];
struct Dist{
    int f, x, y, dis;
};
struct Pair{
    int x, y;
};
Dist dist[maxn];

const int c[24][3] = {2, 0, 0,
              2, 4, 0,
              2, 4, 7,
              3, 0, 0,
              3, 6, 0,
              3, 6, 10,
              4, 0, 0,
              4, 7, 0,
              5, 0, 0,
              5, 9, 0,
              5, 8, 0,
              6, 0, 0,
              6, 10, 0,
              7, 0, 0,
              8, 0, 0,
              8, 9, 0,
              9, 0, 0,
              10, 0, 0,
              12, 0, 0,
              12, 13, 0,
              12, 13, 14,
              13, 0, 0,
              13, 14, 0,
              14, 0, 0};

void draw() {
    memset(b, -1, sizeof(b));
    b[1][4] = b[4][1] = 0;
    b[1][7] = b[7][1] = 1;
    b[1][11] = b[11][1] = 2;
    b[1][6] = b[6][1] = 3;
    b[1][10] = b[10][1] = 4;
    b[1][15] = b[15][1] = 5;
    b[2][7] = b[7][2] = 6;
    b[2][11] = b[11][2] = 7;
    b[2][9] = b[9][2] = b[3][8] = b[8][3] = b[4][6] = b[6][4] = 8;
    b[2][14] = b[14][2] = 9;
    b[3][12] = b[12][3] = 10;
    b[3][10] = b[10][3] = 11;
    b[3][15] = b[15][3] = 12;
    b[4][11] = b[11][4] = 13;
    b[4][13] = b[13][4] = b[5][12] = b[12][5] = b[7][9] = b[9][7] = 14;
    b[7][10] = b[10][7] = 15;
    b[5][14] = b[14][5] = b[6][13] = b[13][6] = b[8][10] = b[10][8] = 16;
    b[6][15] = b[15][6] = 17;
    b[11][13] = b[13][11] = 18;
    b[11][14] = b[14][11] = 19;
    b[11][15] = b[15][11] = 20;
    b[12][14] = b[14][12] = 21;
    b[12][15] = b[15][12] = 22;
    b[13][15] = b[15][13] = 23;
}

void outp() {
    for (int i = 1; i < 16; i++)
        printf("%d ", goal[i]);
    printf("\n");
    for (int i = 1; i < 16; i++) {
        for (int j = 1; j < 16; j++) {
            printf("%d ", b[i][j]);
        }
        printf("\n");
    }
}

inline int code(State& s) {
    int sum = 0;
    for (int i = 1; i < 16; i++)
        if (s[i] != 0)
            sum += (s[i]<<(i-1));
    return sum;
}

void init(int n) {
    memset(goal, 0, sizeof(goal));
    goal[n] = 1;
    memset(st[1], 0, sizeof(st[1]));
    for (int i = 1; i < 16; i++) st[1][i] = 1;
    st[1][n] = 0;
    memset(vis, 0, sizeof(vis));
    vis[code(st[1])] = 1;
    dist[1].f = 0;
    dist[1].x = 0;
    dist[1].y = 0;
    dist[1].dis = 0;
}

void pr(int d) {
    printf("%d\n", dist[d].dis);
    vector<Pair> vp; vp.clear();
    Pair p;
    int pd = d;
    while (dist[pd].f != 0) {
        p.x = dist[pd].x;
        p.y = dist[pd].y;
        vp.push_back(p);
        pd = dist[pd].f;
    }
    int len = vp.size()-1;
    for (int i = len; i >= 0; i--) {
        if (i != len) printf(" ");
        printf("%d %d", vp[i].x, vp[i].y);
    }
    printf("\n");
}

inline bool oper(int x, int y, int di) {
    State&s = st[di];
    int pos = b[x][y];
    int ok = true;
    for (int i = 0; i < 3; i++) {
        if (c[pos][i] == 0) break;
        if (s[c[pos][i]] == 0) {
            ok = false;
            break;
        }
    }
    if (!ok)
        return false;
    s[x] = 0;
    s[y] = 1;
    for (int i = 0; i < 3; i++) {
        if (c[pos][i] == 0) break;
        s[c[pos][i]] = 0;
    }
    dist[di].x = x;
    dist[di].y = y;
    int cod = code(s);
    if (!vis[cod]) {
        vis[cod] = 1;
        return true;
    }
    else
        return false;
}

void bfs() {
    int fron = 1, rear = 2;
    while (fron < rear) {
        State& s = st[fron];
        if (memcmp(goal, s, sizeof(goal)) == 0) {
            pr(fron);
            return;
        }
        for (int i = 1; i < 16; i++) {
            for (int j = 1; j < 16; j++) {
                if (b[i][j] >= 0 && s[i] == 1 && s[j] == 0) {
                    State& t = st[rear];
                    memcpy(t, s, sizeof(s));
                    dist[rear].dis = dist[fron].dis + 1;
                    dist[rear].f = fron;
                    if (oper(i, j, rear)) rear++;
                }
            }
        }
        fron++;
    }
}

int main() {
    draw();
    int T, kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
//        if (kase++) printf("\n");
        if (n >= 1 && n <= 15) {
            init(n);
            bfs();
        }
        else {
            printf("IMPOSSIBLE\nIMPOSSIBLE\n");
            continue;
        }
    }
    return 0;
}
