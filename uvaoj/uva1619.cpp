#include <cstdio>
#include <stack>
using namespace std;

const int maxn = 100000 + 10;

#define LL long long

int n, s[maxn], L[maxn], R[maxn];
LL sum[maxn];
stack<int> sL, sR;

void init() {
	sum[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s[i]);
		sum[i] = sum[i-1] + s[i];
	}

	s[0] = s[n+1] = -1;
	while(!sL.empty()) sL.pop();
	while(!sR.empty()) sR.pop();

	sL.push(0);
	for (int i = 1; i <= n; i++) {
		while (s[sL.top()] >= s[i]) sL.pop();
		L[i] = sL.top();
		sL.push(i);
	}

	sR.push(n+1);
	for (int i = n; i >= 1; i--) {
		while (s[sR.top()] >= s[i]) sR.pop();
		R[i] = sR.top();
		sR.push(i);
	}
}
int main() {
	int cas = 0;
	while (scanf("%d", &n) != EOF) {
		init();
		int ansL, ansR; LL ans = 0;

		for (int i = 1; i <= n; i++) {
			LL res = (sum[R[i]-1]-sum[L[i]]) * s[i];
			if (res > ans) {
				ans = res;
				ansL = L[i] + 1;
				ansR = R[i] - 1;
			}
			else if (res == ans && R[i]-L[i]-1 < ansR-ansL+1) {
				ansL = L[i] + 1;
				ansR = R[i] - 1;
			}
		}

		if (cas++) printf("\n");
		if (ans == 0)
			printf("0\n1 1\n");
		else
			printf("%lld\n%d %d\n", ans, ansL, ansR);
	}
	return 0;
}
