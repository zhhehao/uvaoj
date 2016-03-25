#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
char s[maxn];
int n, d;
vector<int> v[10];

int getpos(int L, int D) {
	for (int i = 9; i >= 0; i--) {
		if (v[i].size() == 0) continue;
		int pos = upper_bound(v[i].begin(), v[i].end(), L) - v[i].begin();
		if (pos != 0) {
			if (L == v[i][pos-1])
				pos--;
		}
		if (pos == v[i].size()) continue;
		else {
			if ((v[i][pos]-L <= D) && (D <= n-L))
				return v[i][pos];
		}
	}
}

int main() {
	while (scanf("%d%d", &n, &d) == 2 && n) {
		scanf("%s", s+1);
		// printf("%s\n", s+1);
		for (int i = 0; i < 10; i++) v[i].clear();
		for (int i = 1; i <= n; i++) v[s[i]-'0'].push_back(i);
		int L = 1, L1;
		while (d > 0) {
			L1 = getpos(L, d);
			// printf("d is %d, L1 is %d\n", d, L1);
			printf("%c", s[L1]);
			d = d - (L1-L);
			L =  L1 + 1;
			if (n-L+1 == d) {
				L = n+1;
				break;
			}
		}
		if (L <= n)
			printf("%s", s+L);
		printf("\n");
	}
	return 0;
}
