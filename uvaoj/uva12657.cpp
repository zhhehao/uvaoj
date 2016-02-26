#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100000 + 10;
int left[maxn], right[maxn];
#define link(L, R) right[L]=R; left[R]=L;

int main() {
	int n, m;
	int kase = 0;
	while (scanf("%d%d", &n, &m) == 2) {
		for (int i = 1; i <= n; i++) {
			left[i] = i-1;
			right[i] = (i+1)%(n+1);
		}
		left[0] = n;
		right[0] = 1;
		int cmd, x, y, inv = 0;
		while (m--) {
			scanf("%d", &cmd) == 1;
			if (cmd == 4) inv = !inv;
			else {
				scanf("%d%d", &x, &y) == 2;
				if (cmd == 3 && right[y] == x) swap(x, y);
				if (cmd != 3 && inv) cmd = 3 - cmd;
				if (cmd == 1 && x == left[y]) continue;
				if (cmd == 2 && x == right[y]) continue;

				int lx = left[x], rx = right[x], ly = left[y], ry = right[y];
				if (cmd == 1) {
					link(lx, rx);
					link(ly, x);
					link(x, y);
				}
				else if (cmd == 2) {
					link(lx, rx);
					link(y, x);
					link(x, ry);
				}
				else if (cmd == 3) {
					if(right[x] == y) {
						link(lx, y);
						link(y, x);
						link(x, ry);
					}
					else {
						link(lx, y);
						link(y, rx);
						link(ly, x);
						link(x, ry);
					}
				}
			}
		}
		int b = 0;
		long long ans = 0;
		for (int i = 1; i <= n; i++) {
			b = right[b];
			if (i%2==1) ans += b;
		}
		if (inv && n%2 == 0) 
			ans = (long long)n*(n+1)/2 - ans;
		printf("Case %d: %lld\n", ++kase, ans);
	}
	return 0;
}
