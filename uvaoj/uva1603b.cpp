#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int maxs = 60;
const int maxm = 60;

int n, exists[maxm];
int s, size[maxs], fullsize[maxs], contains[maxs][maxm];
int best;

inline int row_match(int x, int y) {
    return (2*n+1)*x+y;
}

inline int col_match(int x, int y) {
    return (2*n+1)*x+n+y;
}

inline int match_count(int n) {
    return 2*n*(n+1);
}

void init() {
    int m, v;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < match_count(n); ++i) exists[i] = 1;
    while (m--) {
        scanf("%d", &v);
        exists[v-1] = 0;
    }
    s = 0;
    memset(contains, 0, sizeof(contains));
    for (int i = 1; i <= n; i++)
        for (int x = 0; x <= n-i; x++)
            for (int y = 0; y <= n-i; y++) {
                size[s] = 0;
                fullsize[s] = 4*i;
                for (int j = 0; j < i; j++) {
                    int a = row_match(x, y+j);
                    int b = row_match(x+i, y+j);
                    int c = col_match(x+j, y);
                    int d = col_match(x+j, y+i);
                    contains[s][a] = 1;
                    contains[s][b] = 1;
                    contains[s][c] = 1;
                    contains[s][d] = 1;
                    size[s] += exists[a] + exists[b] + exists[c] + exists[d];
                }
                ++s;
            }
}

int find_square() {
    for (int i = 0; i < s; i++)
        if (size[i] == fullsize[i]) return i;
    return -1;
}

void dfs(int dep) {
    if (dep >= best) return;

    int k = find_square();
    if (k == -1) {
        best = dep;
        return;
    }
    for (int i = 0; i < match_count(n); i++)
        if (contains[k][i]) {
            for (int j = 0; j < s; j++)
                if (contains[j][i]) size[j]--;
            dfs(dep+1);
            for (int j = 0; j < s; j++)
                if(contains[j][i]) size[j]++;
        }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        init();
        best = n*n;
        dfs(0);
        printf("%d\n", best);
    }
    return 0;
}
