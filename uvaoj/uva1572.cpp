#include <cstdio>
#include <cstring>
const int maxn = 52 + 2;
int g[maxn][maxn];

void connect(char a, char b, char c, char d) {
	if (a == '0' || c == '0') return;
	int u = (a - 'A') * 2 + (b == '+' ? 0 : 1);
	int v = (c - 'A') * 2 + (d == '+' ? 0 : 1);
//	printf("%d %d\n", u, u ^1);
	u = u^1;
	g[u][v] = 1;
}

void side(char *c) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) if (i != j)
			connect(c[2*i], c[2*i+1], c[2*j], c[2*j+1]);
}

int c[maxn];

bool dfs(int u) {
	c[u] = -1;
	for (int v = 0; v < 52; v++) if (g[u][v])  {
		if (c[v] < 0) return true;
		else if (!c[v] && dfs(v))
			return true;
	}
	c[u] = 1;
	return false;
}

bool ans() {
	memset(c, 0, sizeof(c));
	for (int i = 0; i < 52; i++) if (!c[i]) 
			if (dfs(i)) return true;
	return false;
}

int main() {
		int t;
	while (scanf("%d", &t) != EOF) {
		char s[10]; memset(g, 0, sizeof(g));
		while (t--) {scanf("%s", s) == 1; side(s);}
		if (ans()) 
			printf("unbounded\n");
		else
			printf("bounded\n");
	}
	return 0;
}
