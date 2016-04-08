#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 5000 + 10;

int n, s[maxn], L[maxn][maxn], R[maxn][maxn];

bool solve() {
	for (int i = 1; i <= n ;i++) {
		L[i][0] = 0;
		for (int j = 1; j < i; j++) {
			if (s[i] >= s[j])
				L[i][j] = L[i][j-1];
			else if (!L[i][j-1] || s[j] < s[L[i][j-1]])
				L[i][j] = j;
			else
				L[i][j] = L[i][j-1];
		}
	}

	for (int i = 1; i <= n ;i++) {
		R[i][n+1] = 0;
		for (int j = n; j > i; j--) {
			if (s[i] <= s[j])
				R[i][j] = R[i][j+1];
			else if (!R[i][j+1] || s[j] > s[R[i][j+1]])
				R[i][j] = j;
			else
				R[i][j] = R[i][j+1];
		}
	}

	for (int q = 2; q <= n; q++) {
		for (int r = q+1; r <= n; r++) {
			if (!L[r][q-1] || !R[q][r+1] || s[q] < s[r]) continue;
			int x = L[r][q-1], y = R[q][r+1];
			if (s[r] < s[x] && s[x] < s[y] && s[y] < s[q]) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &s[i]);
		if (solve())
			printf("YES\n");
		else {
			reverse(s+1, s+n+1);
			if (solve())
				printf("YES\n");
			else
				printf("NO\n");
		}
	}
	return 0;
}
