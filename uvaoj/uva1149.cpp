#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
int items[maxn];

int main() {
	int T, n, l, kase = 0; scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &l);
		for (int i = 0; i < n; i++) scanf("%d", &items[i]);
		sort(items, items+n);
		int ans = 0;
		if (items[n-1]*2 <= l) {
			if (n % 2 == 0)
				ans = n / 2;
			else
				ans = n / 2 + 1;
		}
		else if (items[0]*2 > l) {
			ans = n;
		}
		else {
			int pos = lower_bound(items, items+n, l/2) - items;
			while (items[pos]*2 <= l) pos++;
			int L = pos, R = n-1, L0 = pos;
			if (items[L] + items[0] > l) {
				if (L % 2 == 0)
					ans += L / 2;
				else
					ans += L / 2 + 1;

				ans += (R-L+1);
			}
			else {
				int L1 = upper_bound(items, items+n, l-items[L]) - items;
				while (items[L1] + items[L] > l) L1--;
				L++; L1--;
				while (L <= R) {
					if (L1 < 0) break;
					while (items[L]+items[L1] > l) {
						L1--;
						if (L1 < 0) goto out;
					}
					L++; L1--;
				}
				out:
				int big, pair;
				if (L > R) {
					big = 0;
					pair = R-L0+1;
				}
				else {
					big = R-L+1;
					pair = L-L0;
				}
				int left = pos - pair;
				if (left % 2 == 0)
					left = left / 2;
				else
					left = left / 2 + 1;
				ans = left + big + pair;
			}
		}
		if (kase++)
			printf("\n");
		printf("%d\n", ans);
	}
	return 0;
}
