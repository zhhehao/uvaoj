#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <set>
using namespace std;
const int maxn = 1000 + 5;
int vis[maxn], g[maxn][maxn];
int v, e, t;
vector<int> city;
map<int, int> mcity;
vector<int> odd;
set<int> sodd;

bool insp(int u) {
	bool nocycle = true;
	vis[u] = -1;
	for (int i = 0; i < city.size(); i++) {
		if (g[u][city[i]]) {
			if (vis[city[i]] < 0) nocycle = false;
			else if (!vis[city[i]])
				if (!insp(city[i])) nocycle = false;
		}
	}

	for (int i = 0; i < city.size(); i++) {
		if (g[city[i]][u]) {
			if (vis[city[i]] < 0) nocycle = false;
			else if (!vis[city[i]])
				if (!insp(city[i])) nocycle = false;
		}
	}
	vis[u] = 1;
	if (!nocycle) {
		if (!sodd.count(u)) {
			sodd.insert(u);
			odd.push_back(u);
		}
	}
	return nocycle;
}

int euler(int u) {
	int ocnt = 0;
	for (int i = 0; i < odd.size(); i++) {
		if (mcity[odd[i]] % 2 != 0) ocnt++;	
	}
//	printf("ocnt is %d, odd size is %d\n", ocnt, odd.size());
	odd.clear();
	return ocnt;
}

int solve() {
	int cnt = 0; odd.clear(); sodd.clear();
	for (int i = 0; i < city.size(); i++) {
		if (!vis[city[i]]) {
			cnt++;
			if (!insp(city[i])) {
				int oddnum = euler(city[i]);
				if (oddnum > 2) 
					cnt += (oddnum / 2 - 1);
			}
				
		}
	}
	return cnt;
}

int main() {
	int kase = 1;
	while (scanf("%d%d%d", &v, &e, &t) == 3 && v) {
		memset(g, 0, sizeof(g)); city.clear(); mcity.clear();
		for (int i = 0; i < e; i++) {
			int a, b;
			scanf("%d%d", &a, &b) == 2;
			g[a][b] = 1;
			g[b][a] = 1;
			if (!mcity.count(a)) {
				city.push_back(a);
				mcity[a] = 1;
			}
			else mcity[a]++;
			if (!mcity.count(b)) {
				city.push_back(b);
				mcity[b] = 1;
			}
			else mcity[b]++;
		}
		memset(vis, 0, sizeof(vis));
		int ans = solve();
		printf("Case %d: %d\n", kase++, (e==0) ? 0 : (ans-1+e)*t);
	}
	return 0;
}
