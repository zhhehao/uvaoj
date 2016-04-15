#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;

int n, m, pre[maxn], ans[maxn], we[maxn];
set<int> dragon;

void init() {
	scanf("%d%d", &n, &m);
	memset(pre, 0, sizeof(pre));
	memset(ans, 0, sizeof(ans));
	dragon.clear();
}

bool solve() {
	bool err = true;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &we[i]);
		if (we[i] != 0) {
			set<int>::iterator it = dragon.lower_bound(pre[we[i]]);
			if (it != dragon.end() && *it > pre[we[i]]) {
				ans[*it] = we[i];
				dragon.erase(it);
				pre[we[i]] = i;
			}
			else
				err = false;
		}
		else
			dragon.insert(i);
	}
	return err;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		init();
		if (solve()) {
			printf("YES\n");
			int first = 1;
			for (int i = 1; i <= m; i++) {
				if (we[i] == 0) {
					if (first) {
						printf("%d", ans[i]);
						first = 0;
					}
					else
						printf(" %d", ans[i]);
				}
			}
			printf("\n");
		}
		else
			printf("NO\n");
	}
	return 0;
}
