#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int maxd, ans, n;
int a[20];

int h(int d) {
	int vmax = 0;
	for (int i = 0; i <= d; i++)
		vmax = max(vmax, a[i]);
	return vmax;
}

int dfs(int d) {
//	printf("maxd is %d, d is %d, vsize is %d, n is %d\n", maxd, d, v.size(), n);
	if (a[d] == n) {ans = maxd; return 1;}
	if (d == maxd) return -1; 
	if (h(d)<<(maxd-d) < n) return -1;
	for (int i = d; i >= 0; i--) {
		a[d+1] = a[d] + a[i];
		if (dfs(d+1) > 0) return 1;
		a[d+1] = a[d] - a[i];
		if (dfs(d+1) > 0) return 1;
	}
	return -1;
}

int main() {
	while (scanf("%d", &n) == 1 && n) {
		if (n == 1) {ans = 0; goto end;}
		a[0] = 1;
		for (maxd = 1; ; maxd++)
			if (dfs(0) > 0) break;
end:
		printf("%d\n", ans);
	}
	return 0;
}
