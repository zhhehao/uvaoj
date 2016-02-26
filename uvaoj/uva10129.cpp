#include <cstdio>
#include <cstring>
const int maxn = 1000 + 5;
int g[26][26], c[26], n;
char s[maxn];

void euler1(int u) {
	c[u]++;
	for (int v = 0; v < 26; v++)
		if (g[u][v]) {
			g[u][v]--;
			c[u]--;
			euler1(v);
		}
}

void euler2(int v) {
	c[v]++;
	for (int u = 0; u < 26; u++)
		if (g[u][v]) {
			g[u][v]--;
			c[v]--;
			euler2(u);
		}
}

int main() {
	int t;
	scanf("%d", &t) == 1;
	while (t--) {
		scanf("%d", &n) == 1;
		memset(g, 0, sizeof(g));
		memset(c, 0, sizeof(c));
		memset(s, '\0', sizeof(s));
		int cnt = n;
		while (cnt--) {
			scanf("%s", s) == 1;
			g[s[0]-'a'][s[strlen(s)-1]-'a']++;
		}

		for (int i = 0; i < 26; i++) 
			for (int j = 0; j < 26; j++)
				if (g[i][j]) {
					euler1(i);
					euler2(i);
					goto start;
				}
start:
		bool iscon = true;
		for (int i = 0; i < 26; i++)
			for (int j = 0; j < 26; j++)
				if (g[i][j]) {
					iscon = false; 
					goto end;
				}
end:
		int dcnt = 0;
		for (int i = 0; i < 26; i++)
			if (c[i]) dcnt++;
		if (!iscon || dcnt > 2) {
			printf("The door cannot be opened.\n");
			continue;
		}
		printf("Ordering is possible.\n");
		

//		for (int i = 0; i < 26; i++) {
//			for (int j = 0; j < 26; j++)
//				printf("%d", g[i][j]);
//			printf("\n");
//		}
//		printf("\n");
	}
	return 0;
}
