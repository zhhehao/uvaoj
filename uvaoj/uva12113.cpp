#include <cstdio>
#include <cstring>
char a[45], b[45], buf[5][12];
int sq[9] = {1, 3, 5, 10, 12, 14, 19, 21, 23};
int R, C;

inline bool judge() {
    if (!memcmp(a, b, sizeof(a)))
        return true;
    else
        return false;
}

void init() {
    for (int i = 1; i < 5; i++)
        fgets(buf[i], 12, stdin);
    for (int i = 0; i < 5; i++)
        memcpy(a+i*9, buf[i], 9);
    R = C = 0;
    for (int i = 0; i < 45; i++) {
        if (a[i] == '_') R++;
        else if (a[i] == '|') C++;
    }
//    printf("R is %d, C is %d\n", R, C);
    memset(b, ' ', sizeof(b));
}



bool dfs(int d, int r, int c) {
//    printf("d %d R %d C %d r %d c %d\n", d, R, C, r, c);
    if ((r == R && c == C) || d == 6) {
       if (judge()) return true;
       return false;
    }
    char bak[45]; int r1 = r, c1 = c;
    memcpy(bak, b, sizeof(b));
    for (int i = 0; i < 9; i++) {
        int x = sq[i];
        if (b[x] != '_') {b[x] = '_'; r++;}
        else b[x] = '_';
        if (b[x+2] != '_') {b[x+2] = '_'; r++;}
        else b[x+2] = '_';
        if (b[x+18] != '_') {b[x+18] = '_'; r++;}
        else b[x+18] = '_';
        if (b[x+20] != '_') {b[x+20] = '_'; r++;}
        else b[x+20] = '_';

        if (b[x+8] != '|') {b[x+8] = '|'; c++;}
        else b[x+8] = '|';
        if (b[x+12] != '|') {b[x+12] = '|'; c++;}
        else b[x+12] = '|';
        if (b[x+17] != '|') {b[x+17] = '|'; c++;}
        else b[x+17] = '|';
        if (b[x+21] != '|') {b[x+21] = '|'; c++;}
        else b[x+21] = '|';

        if (b[x+9] == '_') {b[x+9] = ' '; r--;}
        else b[x+9] = ' ';
        if (b[x+11] == '_') {b[x+11] = ' '; r--;}
        else b[x+11] = ' ';
        if (b[x+10] == '|') {b[x+10] = ' '; c--;}
        else b[x+10] = ' ';
        if (b[x+19] == '|') {b[x+19] = ' '; c--;}
        else b[x+19] = ' ';

        if (dfs(d+1, r, c)) return true;
        r = r1; c = c1;
        memcpy(b, bak, sizeof(b));
    }
    return false;
}

int main() {
    int kase = 0;
//    freopen("data.in", "r", stdin);
//    freopen("data.out", "w", stdout);
    while (fgets(buf[0], 12, stdin)) {
        if (buf[0][0] == '0') break;
        init();
        bool ans = dfs(0, 0, 0);
        printf("Case %d: ", ++kase);
        if (ans)
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}
