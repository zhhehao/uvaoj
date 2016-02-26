#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
const int maxstate = 10000000;
const int maxn = 1679616;

typedef int State[2][9];
State st[maxstate], st2[maxstate];
int vis[maxn][9];
int goal[9];

void init_lookup_table() {
    memset(vis, 0, sizeof(vis));
}

const int pos[3][3] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const int bsix[8] = {1, 6, 36, 216, 1296, 7776, 46656, 279936};
const int bsta[3][3] = {-1, 0, 1,
                        2, -1, 3,
                        4, 5, -1};
const int dx[9][4] = {1, 3, 0, 0,
                -1, 1, 3, 0,
                -1, 3, 0, 0,
                -3, 1, 3, 0,
                3, 1, -3 ,-1,
                -3, 3, -1, 0,
                -3, 1, 0, 0,
                -3, 1, -1, 0,
                -3, -1, 0, 0};

inline int code(State& s) {
    int res = 0, cnt = 0;
    for (int i = 0; i < 9; i++) {
        if (s[0][i] == 3) continue;
        res += bsta[s[0][i]][s[1][i]] * bsix[cnt++];
    }
    return res;
}

void init(int m, int n) {
    init_lookup_table();
    int c[2][9];
    memset(c, 0, sizeof(c));
    for (int i = 0; i < 9; i++) c[1][i] = 1;
    c[0][pos[n-1][m-1]] = c[1][pos[n-1][m-1]] = 3;
    memcpy(st[1], c, sizeof(c));
    vis[code(st[1])][pos[n-1][m-1]] = 1;
    char ch[9], buf[9];
    memset(buf, '\0', sizeof(buf));
    fgets(ch, 9, stdin);
    fgets(ch, 9, stdin);
    sscanf(ch, "%c %c %c", &buf[0], &buf[1], &buf[2]);
    fgets(ch, 9, stdin);
    sscanf(ch, "%c %c %c", &buf[3], &buf[4], &buf[5]);
    fgets(ch, 9, stdin);
    sscanf(ch, "%c %c %c", &buf[6], &buf[7], &buf[8]);
    for (int i = 0; i < 9; i++) {
        if (buf[i] == 'W') goal[i] = 0;
        else if (buf[i] == 'R') goal[i] = 1;
        else if (buf[i] == 'B') goal[i] = 2;
        else if (buf[i] == 'E') goal[i] = 3;
    }
}

inline void roll(int& t, int& f, int dir) {
    if (dir == -1 || dir == 1) {
        if ((t == 0 && f == 1) || (t == 1 && f == 0)) t = 2;
        else if ((t == 0 && f == 2) || (t == 2 && f == 0)) t = 1;
        else if ((t == 1 && f == 2) || (t == 2 && f == 1)) t = 0;
    }
    else if (dir == 3 || dir == -3) {
        swap(t, f);
    }
}

void dfs(queue<int>& q, int& cnt, int d, State& c) {
    if (d == 9) {
        int pos = code(c), x;
        for (x = 0; x < 9; x++) if (c[0][x] == 3) break;
        vis[pos][x] = -1;
        memcpy(st2[cnt], c, sizeof(c));
        q.push(cnt);
        cnt++;
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (c[0][d] == 3) {
            c[1][d] == 3;
            dfs(q, cnt, d+1, c);
        }
        if (c[0][d] == i) continue;
        c[1][d] = i;
        dfs(q, cnt, d+1, c);
    }
}

int bfs() {
    int rear = 1, rear2 = 1;
    queue<int> q1, q2;
    while (!q1.empty()) q1.pop(); while (!q2.empty()) q2.pop();
    q1.push(rear); rear++;
    State dq;
    memset(dq, 0, sizeof(dq));
    memcpy(dq, goal, sizeof(goal));
    dfs(q2, rear2, 0, dq);
    while (!q1.empty() || !q2.empty()) {
        if (q1.size() <= q2.size() || q2.empty()) {
            int fron = q1.front(); q1.pop();
            State& s = st[fron];
            int pos1 = code(s);
            int x;
            for (x = 0; x < 9; x++) if (s[0][x] == 3) break;
            for (int i = 0; i < 4; i++) {
                if (dx[x][i] == 0) break;
                State& t = st[rear];
                memcpy(&t, &s, sizeof(s));
                int newx = x + dx[x][i];
                roll(t[0][newx], t[1][newx], dx[x][i]);
                t[0][x] = t[0][newx];
                t[1][x] = t[1][newx];
                t[0][newx] = t[1][newx] = 3;
                if (memcmp(goal, t, sizeof(goal)) == 0) return vis[pos1][x];
                int pos2 = code(t);
                if (vis[pos2][newx] < 0) return vis[pos1][x] + vis[pos2][newx] * -1 - 1;
                if (!vis[pos2][newx]) {
                    vis[pos2][newx] = vis[pos1][x] + 1;
                    if (vis[pos2][newx] > 21) continue;
                    q1.push(rear);
                    rear++;
                }
            }
        }
        else {
            int fron2 = q2.front(); q2.pop();
            State& s = st2[fron2];
            int pos1 = code(s);
            int x;
            for (x = 0; x < 9; x++) if (s[0][x] == 3) break;
            for (int i = 0; i < 4; i++) {
                if (dx[x][i] == 0) break;
                State& t = st2[rear2];
                memcpy(&t, &s, sizeof(s));
                int newx = x + dx[x][i];
                roll(t[0][newx], t[1][newx], dx[x][i]);
                t[0][x] = t[0][newx];
                t[1][x] = t[1][newx];
                t[0][newx] = t[1][newx] = 3;
                int pos2 = code(t);
                if (vis[pos2][newx] > 0) return vis[pos1][x]*-1 + vis[pos2][newx] - 1;
                if (!vis[pos2][newx]) {
                    vis[pos2][newx] = vis[pos1][x] - 1;
                    if (vis[pos2][newx] > 9) continue;
                    q2.push(rear2);
                    rear2++;
                }
            }
        }
    }
    return -1;
}

int main() {
    int m, n;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (scanf("%d%d", &m, &n) == 2 && m) {
        init(m, n);
        if (memcmp(goal, st[1], sizeof(goal)) == 0) {
            printf("0\n");
            continue;
        }
        int ans = bfs();
        if (ans > 30)
            printf("-1\n");
        else
            printf("%d\n", ans);
    }
    return 0;
}
