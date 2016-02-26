#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
// b存储grid of pips，c存储结果，ans存储结果的个数，
// bone存储骨牌点，bc存储哪些骨牌已经被用过了
int b[7][8], c[7][8], ans, bone[7][7], bc[29];

void initbone() { // 初始化骨牌点，用作查询
    memset(bone, -1, sizeof(bone));
    int num = 1;
    for (int i = 0; i < 7; i++)
        for (int j = i; j < 7; j++)
            bone[i][j] = num++;
}

inline int getbone(int x, int y) { // 通过点值查骨牌的号码
    if (x > y) swap(x, y);
    return bone[x][y];
}

void dfs(int d) {
//    printf("d is %d\n", d);
//            for (int i = 0; i < 7; i++) {
//            for (int j = 0; j < 8; j++)
//                printf("%4d", c[i][j]);
//            printf("\n");
//        }
    if (d == 28) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 8; j++)
                printf("%4d", c[i][j]);
            printf("\n");
        }
        printf("\n");
        ans++;
        return;
    }
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 8; j++) {
            if (!c[i][j]) {
                if (j+1 < 8 && !c[i][j+1]) {
                    int bo = getbone(b[i][j], b[i][j+1]);
                    if (!bc[bo]) {
                        bc[bo] = 1;
                        c[i][j] = c[i][j+1] = bo;
                        dfs(d+1);
                        bc[bo] = 0;
                        c[i][j] = c[i][j+1] = 0;
                    }
                }
                if (i+1 < 7 && !c[i+1][j]) {
                    int bn = getbone(b[i][j], b[i+1][j]);
                    if (!bc[bn]) {
                        bc[bn] = 1;
                        c[i][j] = c[i+1][j] = bn;
                        dfs(d+1);
                        bc[bn] = 0;
                        c[i][j] = c[i+1][j] = 0;
                    }
                }
                return;
            }
        }
}

int main() {
    int kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    initbone();
    while (scanf("%d", &b[0][0]) != EOF) {
        for (int i = 1; i < 8; i++) scanf("%d", &b[0][i]);
        for (int i = 1; i < 7; i++)
            for (int j = 0; j < 8; j++)
                scanf("%d", &b[i][j]);
        if (kase++) printf("\n\n\n");
        printf("Layout #%d:\n\n\n", kase);
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 8; j++)
                printf("%4d", b[i][j]);
            printf("\n");
        }
        printf("\nMaps resulting from layout #%d are:\n\n\n", kase);
        memset(c, 0, sizeof(c));
        memset(bc, 0, sizeof(bc));
        ans = 0;
        dfs(0);
        printf("There are %d solution(s) for layout #%d.\n", ans, kase);
    }

    return 0;
}
