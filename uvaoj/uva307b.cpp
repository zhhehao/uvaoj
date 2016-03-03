#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200;
int st[maxn], vis[maxn], n, d, sum;

bool cmp(const int& a, const int &b) {
    return a > b;
}

void init() {
    memset(st, 0, sizeof(st));
    sum = 0;
    for (int i = 0; i < n; i++) {scanf("%d", &st[i]); sum += st[i];}
    sort(st, st+n, cmp);
}

bool dfs(int now, int pos, int cnt) {
    if (d * cnt == sum) return true;
    for (int i = pos; i < n; i++) {
        if (vis[i] || (i && !vis[i-1] && st[i] == st[i-1])) continue;
        if (now + st[i] == d) {
            vis[i] = 1;
            if (dfs(0, 0, cnt+1)) return true;
            vis[i] = 0;
            return false;
        }
        else if (now + st[i] < d) {
            vis[i] = 1;
            if (dfs(now+st[i], i+1, cnt)) return true;
            vis[i] = 0;
            if (now == 0) return false;
        }
    }
    return false;
}

int main() {
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (scanf("%d", &n) == 1 && n) {
        init();
        for (d = st[0]; d < sum; d++) {
            if (sum % d != 0) continue;
            memset(vis, 0, sizeof(vis));
            if (dfs(0, 0, 0)) break;
        }
        printf("%d\n", d);
    }
    return 0;
}
