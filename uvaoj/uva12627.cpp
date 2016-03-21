#include <cstdio>
typedef long long LL;
int k, a, b;

LL tp(int x) {
	if (x == 0) return 1;
	LL rec = 1;
	for (int i = 0; i < x; i++)
		rec *= 3;
	return rec;
}

LL f(int x, int y) {
	if (y == 0) return 0;
	else if (x == 0) return 1;
	else if (y == (1<<x)) return tp(x);
	else if (y <= (1<<(x-1))) return f(x-1, y) * 2;
	else return f(x-1, y-(1<<(x-1))) + 2*tp(x-1);
}

int main() {
	int T, kase = 0; scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &k, &a, &b);
		LL ans;
		if (k == 0) ans = 1;
		else ans = f(k, b)-f(k, a-1);
		printf("Case %d: %lld\n", ++kase, ans);
	}
	return 0;
}
