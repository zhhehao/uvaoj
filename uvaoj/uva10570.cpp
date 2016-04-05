#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 500 + 10;

int n, L[maxn], R[maxn];


int main() {
	while (scanf("%d", &n) == 1 && n) {
		int num;
		for (int i = 0, j = n-1; i < n; i++, j--) {
			scanf("%d", &num);
			num--;
			L[i] = R[j] = num;
		}

		int ans = maxn, l[maxn], r[maxn];
		for (int s = 0; s < n; s++) {
			memcpy(l, L, sizeof(L));
			memcpy(r, R, sizeof(R));

			int cnt1 = 0, cnt2 = 0;
			for (int i = 0; i < n; i++) {
				while ((l[i]+s)%n != i) {
					swap(l[(l[i]+s)%n], l[i]);
					cnt1++;
				}
			}
			for (int i = 0; i < n; i++) {
				while ((r[i]+s)%n != i) {
					swap(r[(r[i]+s)%n], r[i]);
					cnt2++;
				}
			}
			ans = min(ans, min(cnt1, cnt2));
			if (ans == 0)
				goto output;
		}
		output:
		printf("%d\n", ans);
	}
	return 0;
}
