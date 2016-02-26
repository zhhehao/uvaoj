#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int b[24], maxd;
char a[1000];
int g[8][7] = {
{0, 2, 6, 11, 15, 20, 22},
{1, 3, 8, 12, 17, 21, 23},
{10, 9, 8, 7, 6, 5, 4},
{19, 18, 17, 16, 15, 14, 13},
{23, 21, 17, 12, 8, 3, 1},
{22, 20, 15, 11, 6, 2, 0},
{13, 14, 15, 16, 17, 18, 19},
{4, 5, 6, 7, 8, 9, 10},
};
int cen[] = {6, 7, 8, 11, 12, 15, 16, 17};
int rev[] = {5, 4, 7, 6, 1, 0, 3, 2};

bool isdone() {
	int ok = 1;
	for (int i = 0; i < 7; i++)
		if (b[cen[i]] != b[cen[i+1]]) {ok = 0; break;}
	if (ok) return true;
	else return false;
}

int dif(int n) {
	int cnt = 0;
	for (int i = 0; i < 8; i++)
		if (b[cen[i]] != n) cnt++;
	return cnt;
}

int h() {
	return min(min(dif(1), dif(2)), dif(3));	
}

void move(int n) {
	int tmp = b[g[n][0]];
	for (int i = 0; i < 6; i++) 
		b[g[n][i]] = b[g[n][i+1]];
	b[g[n][6]] = tmp;
}

int dfs(int d) {
//	printf("d is %d, maxd is %d\n", d, maxd);
	if (isdone()) return 1;
	if (h()+d > maxd) return -1;
	for (int i = 0; i < 8; i++) {
		a[d] = i + 'A';
		move(i);
		if (dfs(d+1) > 0) return 1;
		move(rev[i]);
	}
	return -1;
}

int main() {
	int t;
	while (scanf("%d", &t) == 1 && t) {
		memset(b, 0, sizeof(b));
		memset(a, '\0', sizeof(a));
		b[0] = t;
		for (int i = 1; i < 24; i++)
			scanf("%d", &b[i]) == 1;
//		for (int i = 0; i < 8; i++)
//			printf("%2d", b[cen[i]]);
//		printf("\n%d\n", h());
		if (isdone()) {
			printf("No moves needed");
		}
		else {
			for (maxd = 1; ; maxd++)  
				if (dfs(0) > 0) break;
			int len = strlen(a);
			for (int i = 0; i < len; i++)
				printf("%c", a[i]);
		}
		printf("\n%d\n", b[cen[0]]);
	}
	return 0;
}
