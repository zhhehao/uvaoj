#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define LD long double

const int maxn = 100000 + 10;
const long double ESP = 1e-11;

struct Dist{
	int L, R;
	bool operator < (const Dist& b) const {
		if (L == b.L)
			return R < b.R;
		else
			return L < b.L;
	}
} d[maxn];

int n;

bool ok(LD len) {
	LD cur = 0.0, tmp;
	for (int i = 0; i < n; i++) {
		tmp = d[i].L * 1.0;
		cur = max(tmp, cur);
		if (cur+len-d[i].R > ESP)
			return false;
		cur += len;
	}
	return true;
}

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++)
			scanf("%d%d", &d[i].L, &d[i].R);
		sort(d, d+n);

		LD L = 0.0, R = d[n-1].R+ESP;
		while (R-L > ESP) {
			LD mid = (L+R) / 2;
			if (ok(mid))
				L = mid;
			else
				R = mid;
		}
		LD Min = 2000000;
		int p, q;
		for (int i = 1; i <= maxn; i++) {
			int j = floor(L*i);
			if (abs((LD)(j) / i - L) < Min) {
				p = j;
				q = i;
				Min = abs((LD)(j) / i - L);
				// printf("%d/%d\n", p, q);
			}
			j = ceil(L*i);
			if (abs((LD)(j) / i - L) < Min) {
				p = j;
				q = i;
				Min = abs((LD)(j) / i - L);
				// printf("%d/%d\n", p, q);
			}
		}
		printf("%d/%d\n", p, q);
	}
	return 0;
}
