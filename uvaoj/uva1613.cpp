#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 9999 + 10;

struct Ver{
	int color;
	vector<int> nb;
} ver[maxn];

int n, m, color[maxn], deg[maxn];

int main() {
	int kase = 0;
	while (scanf("%d%d", &n, &m) != EOF) {
		int v1, v2;
		for (int i = 1; i <= n; i++) {ver[i].nb.clear(); ver[i].color = 0;}
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &v1, &v2);
			ver[v1].nb.push_back(v2);
			ver[v2].nb.push_back(v1);
		}
		int maxdeg = 0;
		for (int i = 1; i <= n; i++) {
			deg[i]= ver[i].nb.size();
			maxdeg = max(maxdeg, deg[i]);
		}

		int k;
		if (maxdeg % 2 == 0)
			k = maxdeg + 1;
		else
			k = maxdeg;

		for (int i = 1; i <= n; i++) {
			deg[i]= k - deg[i];
		}

		for (int i = 1; i <= n; i++) {
			memset(color, 0, sizeof(color));
			int pos, mdeg = 20000;
			for (int j = 1; j <= n; j++) {
				if (ver[j].color == 0 && mdeg > deg[j]) {
					mdeg = deg[j];
					pos = j;
				}
			}
			Ver& v = ver[pos];
			for (int j = 0; j < v.nb.size(); j++) {
				if (ver[v.nb[j]].color != 0)
					color[ver[v.nb[j]].color] = 1;
				else
					deg[v.nb[j]]--;
			}
			for (int j = 1; j <= k; j++)
				if (color[j] != 1) {
					v.color = j;
					break;
				}
		}
		if (kase++) printf("\n");

		printf("%d\n", k);
		for (int i = 1; i <= n; i++)
			printf("%d\n", ver[i].color);
	}
	return 0;
}
