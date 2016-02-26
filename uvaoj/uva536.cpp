#include <cstdio>
#include <cstring>
const int maxn = 26 + 2;
int preord[maxn], inord[maxn], lbt[maxn], rbt[maxn];

int build(int l1, int r1, int l2, int r2) {
	int root = preord[l1];
	int p = l2; while (inord[p] != root) p++;
	if (p - l2 > 0)
		lbt[root] = build(l1+1, l1+p-l2, l2, p-1);
	if (r2 - p > 0)
		rbt[root] = build(r1+1+p-r2, r1, p+1, r2);
	return root;
}

void dfs(int node) {
	if (lbt[node] > 0) dfs(lbt[node]);
	if (rbt[node] > 0) dfs(rbt[node]);
	printf("%c", node - 1 + 'A');
}

int main() {
	char buf1[30], buf2[30];
	while (scanf("%s", buf1) != EOF) {
		memset(lbt, 0, sizeof(lbt));
		memset(rbt, 0, sizeof(rbt));
		int len = strlen(buf1); scanf("%s", buf2) == 1;
		for (int i = 0; i < len; i++) {preord[i] = buf1[i]-'A'+1; inord[i] = buf2[i]-'A'+1;}
		int root = build(0, len-1, 0, len-1);
		dfs(root);
		printf("\n");
	}
	return 0;
}
