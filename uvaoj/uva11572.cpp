#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;
const int maxn = 1000000 + 10;
set<int> sf;
int se[maxn];

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		sf.clear();
		for (int i = 0; i < n; i++)
			scanf("%d", &se[i]);
		int L = 0, R = 0, ans = 0;
		while (R < n) {
			while (R < n && !sf.count(se[R])) sf.insert(se[R++]);
			ans = max(ans, R-L);
			sf.erase(se[L++]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
