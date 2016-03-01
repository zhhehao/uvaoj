#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100;
int st[maxn], ans, n, sub[maxn], rem[maxn];

void init() {
    memset(st, 0, sizeof(st));
    memset(sub, -1, sizeof(sub));
    for (int i = 0; i < n; i++) scanf("%d", &st[i]);
}

void solve(int cur) {
    memset(rem, 0, sizeof(rem));
    int s = 0, e = -1, cnt = 0;
    while (e != n-1) {
        s = e+1;
        if (cnt == cur)
            e = n-1;
        else
            e = sub[cnt];
//        printf("s is %d, e is %d\n", s, e);
        for (int i = s; i <= e; i++)
            rem[cnt] += st[i];
        cnt++;
    }
//    printf("cnt is %d\n", cnt);
    int ok = 1;
    for (int i = 0; i < cnt-1; i++) {
        if (rem[i] != rem[i+1]) {ok = 0; break;}
    }
    if (ok)
        ans = min(rem[0], ans);
    else
        return;
}

void subset(int cur) {
//    for (int i = 0; i < cur; i++)
//        printf("%d ", sub[i]);
//    printf("\n");
    if (cur != 0) {
        solve(cur);
    }
    int s = cur?sub[cur-1]+1:0;
    for (int i = s; i < n-1; i++) {
        sub[cur] = i;
        subset(cur+1);
    }
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        init();
        ans = 10000;
        sort(st, st+n);
        do {
            subset(0);
        } while (next_permutation(st, st+n));
        printf("%d\n", ans);
    }
    return 0;
}
