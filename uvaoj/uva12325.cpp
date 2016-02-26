#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n, s1, v1, s2, v2;

int main() {
	int t, kase = 0; scanf("%d", &t) == 1;
	while (t--) {
		scanf("%d%d%d%d%d\n", &n, &s1, &v1, &s2, &v2) == 5;
		if (s1 > s2) {
			swap(s1, s2);
			swap(v1, v2);
		}
		long long ans = 0;
		if (n/s2 >= 65535) { // 绝妙的构思
			for (long long i = 0; i <= s1; i++)
				ans = max(ans, i*v2 + (n-i*s2)/s1*v1);
			for (long long i = 0; i <= s2; i++)
				ans = max(ans, i*v1 + (n-i*s1)/s2*v2);
		}
		else {
			for (long long i = 0; i*s2 <= n; i++) // 化除法为乘法
				ans = max(ans, i*v2 + (n-i*s2)/s1*v1);
		}
		printf("Case #%d: %lld\n", ++kase, ans);
	}
	return 0;
}
