#include <cstdio>
#include <cstring>
#include <set>
using namespace std;
#define max(a, b) ((a)>(b)?(a):(b))
typedef long long LL;
// 此题用的是贪婪算法，可参照维基百科 古埃及分数 条目。
const int maxn = 1000;
int a, b, maxd;
LL v[maxn], ans[maxn];
set<LL> sk;

LL gcd(LL a, LL b) { // 求最大公约数
    return b == 0 ? a : gcd(b, a%b);
}

inline int getf(LL a, LL b) { // 贪婪算法
    return b/a+1;
}

bool better(int d) { // 如果有更优解，更新
    for (int i = d; i >= 0; i--)
        if (v[i] != ans[i]) {
            return ans[i] == -1 || v[i] < ans[i];
        }
    return false;
}

bool dfs(int d, int from, LL aa, LL bb) {
    if (d == maxd) {
        if (bb % aa) return false;
        v[d] = bb / aa;
        if (sk.count(v[d])) return false;
        if (better(d)) memcpy(ans, v, sizeof(LL)*(d+1));
        return true;
    }
    bool ok = false;
    from = max(from, getf(aa, bb));
    for (int i = from; ; i++) {
        if (bb * (maxd+1-d) <= i * aa) break; // 重要的剪枝，参照书上说明。
        if (sk.count(i)) continue;
        v[d] = i;
        LL b2 = bb * i;
        LL a2 = aa * i - bb;
        LL g = gcd(a2, b2);
        if (dfs(d+1, i+1, a2/g, b2/g)) ok = true;
    }
    return ok;
}

int main() {
    int t, kase = 0, k;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d", &a, &b, &k);
        sk.clear();
        while (k--) {
            int num;
            scanf("%d", &num);
            sk.insert(num);
        }
//        for (int i = 0; i < vk.size(); i++)
//            printf("%d\n", vk[i]);
        for (maxd = 1; ; maxd++) {
            memset(ans, -1, sizeof(ans));
            if (dfs(0, getf(a, b), a, b)) break;
        }
        printf("Case %d: %d/%d=", ++kase, a, b);
        for (int i = 0; i < maxd; i++)
            printf("1/%d+", ans[i]);
        printf("1/%d\n", ans[maxd]);
    }
    return 0;
}
