#include <cstdio>
#include <cstring>
const int maxn = 256 + 5;
char nodes[maxn];
int main() {
	int n, kase = 0;
	while (scanf("%d", &n) == 1 && n != 0) {
		memset(nodes, '\0', sizeof(nodes)); char order[8], buf[8];
		memset(order, '\0', sizeof(order));	memset(buf, '\0', sizeof(buf));
		for (int i = 1; i <= n; i++) {char ch[2]; scanf("%s", ch) == 1; order[i] = ch[1];}
		scanf("%s", nodes+(2<<(n-1))) == 1;
		int m; scanf("%d", &m) == 1;
		printf("S-Tree #%d:\n", ++kase);
		for (int i = 0; i < m; i++) {
			scanf("%s", buf+1) == 1;	
			int ans = 1;
			for (int j = 1; j <= n; j++)
				if (buf[order[j]-'0'] == '0')
					ans = 2 * ans;
				else
					ans = 2 * ans + 1;
			printf("%d", nodes[ans] - '0');
		}
		printf("\n\n");
	}
	return 0;
}
