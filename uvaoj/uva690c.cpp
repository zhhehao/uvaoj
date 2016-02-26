#include <cstdio>
#include <cstring>
#define min(a, b) ((a)<(b)?(a):(b))
int n, b[5], w[20], ans, cnt;
char buf[5][20];

inline bool judge(int s0, int s1, int s2, int s3, int s4) {
    return ((s0&b[0]) == 0 &&
            (s1&b[1]) == 0 &&
            (s2&b[2]) == 0 &&
            (s3&b[3]) == 0 &&
            (s4&b[4]) == 0 );
}

void init() {
    memset(b, 0, sizeof(b));
    for (int i = 0; i < 5; i++) {
        scanf("%s", buf[i]);
        int sum = 0;
        for (int j = 0; j < n; j++)
            if (buf[i][j] == 'X')
                sum += (1<<(n-1-j));
        b[i] = sum;
    }
    cnt = 0;
    memset(w, -1, sizeof(w));
    for (int i = 1; i <= n; i++)
        if (judge((b[0]>>i), (b[1]>>i), (b[2]>>i), (b[3]>>i), (b[4]>>i)))
            w[cnt++] = i;
    ans = 200;
}

void dfs(int s0, int s1, int s2, int s3, int s4, int d, int len) {
    if (d == 10) {
        ans = min(ans, len);
        return;
    }
    if (len + (10-d)*w[0] > ans) return;
    for (int i = 0; i < cnt; i++) {
        int t0 = (s0>>w[i]), t1 = (s1>>w[i]), t2 = (s2>>w[i]), t3 = (s3>>w[i]), t4 = (s4>>w[i]);
        if (judge(t0, t1, t2, t3, t4))
            dfs(t0^b[0], t1^b[1], t2^b[2], t3^b[3], t4^b[4], d+1, len+w[i]);
    }

}

int main() {
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        init();
        dfs(b[0], b[1], b[2], b[3], b[4], 1, n);
        printf("%d\n", ans);
    }
    return 0;
}
