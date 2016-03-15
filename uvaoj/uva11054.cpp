#include <cstdio>
#include <cmath>
using namespace std;

int main() {
	int n;
	while (scanf("%d", &n) && n) {
		long long ans = 0, k = 0;
		int val;
		for (int i = 0; i < n; i++) {
			scanf("%d", &val);
			ans += abs(k);
			k += val;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
