#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100 + 5;

struct Tree{
	int x, y;
	bool operator < (const Tree& b) const {
		return x < b.x;
	}
};

int n, w, h, th[10010], cnt;
Tree tr[maxn];

void init() {
	scanf("%d%d%d", &n, &w, &h);
	th[0] = 0; th[1] = h;
	cnt = 2;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &tr[i].x, &tr[i].y);
		th[cnt++] = tr[i].y;
	}
	sort(tr, tr+n);
	tr[n++].x = w;
	sort(th, th+cnt);
	cnt = unique(th, th+cnt) - th;
}

void solve() {
	int ansX = 0, ansY = 0, ansL = 1;
	for (int i = 0; i < cnt; i++) {
		for (int j = i+1; j < cnt; j++) {
			int maxP = 0, maxL = 0, prex = 0;
			for (int k = 0; k < n; k++) {
				if (k == n-1 || (tr[k].y > th[i] && tr[k].y < th[j])) {
					if (tr[k].x-prex > maxL) {
						maxL = tr[k].x-prex;
						maxP = prex;
					}
					prex = tr[k].x;
				}
			}
			int L = min(maxL, th[j]-th[i]);
			if (L > ansL) {
				ansL = L;
				ansX = maxP;
				ansY = th[i];
			}
		}
	}
	printf("%d %d %d\n", ansX, ansY, ansL);
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		init();
		solve();
		if (T) printf("\n");
	}
	return 0;
}
