#include <cstdio>
#include <cstring>
#include <cctype>
#include <vector>
using namespace std;
char buf[15], a[4], b[4], c[6];
int ans[8];
const int w[] = {-2, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int maxd, la, lb, lc, all, lena, lenb, lenc, blen, chlen;

inline void init() {
    int cnt = 0, cnta = 0, cntb = 0, cntc = 0;
    while (buf[cnt] != ' ') a[cnta++] = buf[cnt++];
    a[cnta] = '\0'; cnt++;
    while (buf[cnt] != ' ') b[cntb++] = buf[cnt++];
    b[cntb] = '\0'; cnt++;
    while (buf[cnt] == '*' || isdigit(buf[cnt])) c[cntc++] = buf[cnt++];
    c[cntc] = '\0';
    int lcnt = 0;
    blen = strlen(buf);
    memset(ans, -1, sizeof(ans));
    for (int i = 0; i < blen; i++) {
        if (buf[i] == '*')
            ans[lcnt++] = -2;
        else if (isdigit(buf[i]))
            ans[lcnt++] = buf[i] - '0';
    }
    lena = strlen(a);
    lenb = strlen(b);
    lenc = strlen(c);
    la = 0;
    lb = lena;
    lc = lena + lenb;
    chlen = lena+lenb+lenc;
//    for (int i = 0; i < chlen; i++)
//        printf("%d ", ans[i]);
//    printf("\n");
}

inline bool cmp(int* ch, int num) {
    int nm = num, cnt = 0;
    while (nm) {
        nm /= 10; cnt++;
    }
    if (cnt != lenc) return false;
    for (int i = lc+lenc-1; i >= lc; i--) {
        int x = num % 10;
        if (x != ch[i] && ch[i] != -2) return false;
        num /= 10;
    }
    return true;
}

inline int getnum(int st, int lst, int* ch) {
    if (lst == 1) return ch[st];
    else
        return ch[st]*10+ch[st+1];
}

bool jdfs(int p, int* ch) {
    if (p == lc) {
        int na = getnum(la, lena, ch);
        int nb = getnum(lb, lenb, ch);
//        printf("na is %d, nb is %d\n", na, nb);
        if (cmp(ch, na*nb)) all++;
//        printf("all is %d\n", all);
        if (all > 1) return false;
        return true;
    }
    if (ch[p] != -2) {
        if (!jdfs(p+1, ch)) return false;
    }
    else {
       int st = 1;
       if (p == la || p == lb) st++;
       for (int i = st; i < 11; i++) {
            int ccc = ch[p];
            ch[p] = w[i];
            if (!jdfs(p+1, ch)) return false;
            ch[p] = ccc;
       }
    }
    return true;
}

inline bool judge() {
    int ch[8];
    all = 0;
    memcpy(ch, ans, sizeof(ans));
    if (jdfs(0, ch)) {
        if (all == 1)
            return true;
        else
            return false;
    }
    return false;
}

bool dfs(int p, int d) {
    if (judge()) return true;
    if (d == maxd) {
        return false;
    }
    for (int i = 0; i < 11; i++) {
        if (ans[p] == w[i] && chlen-p-1<maxd-d) continue;
        if ((p == la || p == lb || p == lc) && i == 1) continue;
        int add = 1;
        if (ans[p] == w[i]) add--;
        int cch = ans[p];
        ans[p] = w[i];
        if (dfs(p+1, d+add)) return true;
        ans[p] = cch;
    }
    return false;
}

int main() {
    int kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (fgets(buf, 15, stdin)) {
        if (buf[0] == '0') break;
        init();
//        printf("%d\n", judge());
        for (maxd = 1; ; maxd++) {
            if (dfs(0, 0)) break;
        }
        printf("Case %d: ", ++kase);
        for (int i = 0; i < chlen; i++) {
            if (i == lb || i == lc) printf(" ");
            if (ans[i] >= 0)
                printf("%d", ans[i]);
            else if (ans[i] == -2)
                printf("%c", '*');
        }
        printf("\n");
    }
    return 0;
}
