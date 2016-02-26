#include <cstdio>
#include <cstring>
const int maxn = 20 + 2;
int c[maxn], vis[maxn], n;
// int cnt;

void search(int cur) {
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
		if (!vis[i]) {
			int ok = 1;
			c[cur] = i;
			int sum = c[cur]+c[cur-1];
			for (int j = 2; j < sum; j++)
				if (sum % j == 0)
					{ok = 0;break;}	
			if (ok) {
				vis[i] = 1;
				search(cur+1);
				vis[i] = 0;
			}
		}
	}
}

int main() {
	int kase = 0;
	while (scanf("%d", &n) != EOF) {
		memset(c, 0, sizeof(c));
		memset(vis, 0, sizeof(vis));
		c[0] = vis[0] = 1;
//		cnt = 0; 
		if (kase++) printf("\n");
		printf("Case %d:\n", kase);
		search(1);
//		printf("%d\n", cnt);
	}
	return 0;
}
