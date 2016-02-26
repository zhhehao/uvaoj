#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 10000;

int a[MAXN];

int main() {
	int rev, n, q, que, ans, kase = 0;
	while ((rev=scanf("%d%d", &n, &q)==2 && n)) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < n; i++)
			rev = scanf("%d", &a[i]);
		sort(a, a+n);
		printf("CASE# %d:\n", ++kase);
		for (int i = 0; i < q; i++) {
			rev = scanf("%d", &que);
			ans = lower_bound(a, a+n, que) - a;
			if (a[ans] == que)
				printf("%d found at %d\n",que ,ans + 1);
			else
				printf("%d not found\n", que);
		}
	}
	return 0;
}
