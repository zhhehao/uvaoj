#include <cstdio>
#include <cstring>
const int maxn = 20 + 2;
int c[maxn];
// int cnt;

void search(int n, int* c, int cur) {
	if (cur == n) {
		int ok = 1;
		int sum = c[cur-1] + c[0];
		for (int j = 2; j < sum; j++)
			if (sum % j == 0)
				{ok = 0; break;}
		if (ok) {
			for (int i = 0; i < n; i++) {
				if (i) printf(" ");
				printf("%d", c[i]);
			}
			printf("\n");
//			cnt++;
		}
	}
	else for (int i = 2; i <= n; i++) {
		int ok = 1;
		c[cur] = i;
		for (int j = 0; j < cur; j++)
			if (c[j] == i) {ok = 0; break;}
		if (ok) {
			int sum = c[cur]+c[cur-1];
			for (int j = 2; j < sum; j++)
				if (sum % j == 0)
					{ok = 0;break;}
		}
		if (ok) 
			search(n, c, cur+1);
	}
}

int main() {
	int n, kase = 0;
	while (scanf("%d", &n) != EOF) {
		memset(c, 0, sizeof(c));
		c[0] = 1;
//		cnt = 0; 
		int cur = 1;
		if (kase++) printf("\n");
		printf("Case %d:\n", kase);
		search(n, c, cur);
//		printf("%d\n", cnt);
	}
	return 0;
}
