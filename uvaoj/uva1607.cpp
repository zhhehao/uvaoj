#include <cstdio>

const int maxn = 200000 + 10;

int n, m;

struct Gate {
	int a, b, o;
} gate[maxn];

int cal(int x) {
	for (int i = 1; i <= m; i++) {
		int a = gate[i].a, b = gate[i].b;
		int va = a < 0 ? -a > x : gate[a].o;
		int vb = b < 0 ? -b > x : gate[b].o;
		gate[i].o = !(va && vb);
	}
	return gate[m].o;
}

int solve(int x) {
	int L = 1, R = n;
	while (L < R) {
		int M = L + (R-L)/2;
		if (cal(M) == x) R = M;
		else L = M+1;
	}
	return L;
}

int main() {
	int t; scanf("%d", &t);
	while (t--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++)
			scanf("%d%d", &gate[i].a, &gate[i].b);
		int ans1 = cal(0);
		int ans2 = cal(n);
		if (ans1 == ans2) {
			for (int i = 1; i <= n; i++) printf("0");
		}
		else {
			int x = solve(ans2);
			for (int i = 1; i < x; i++) printf("0");
			printf("x");
			for (int i = x+1; i <= n; i++) printf("1");
		}
		printf("\n");
	}
	return 0;
}
