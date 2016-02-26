#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int vis[26][3], ans[10], bw, n;
//int cnt;
int	c[10];
vector<int> g[26];
set<int> sg[26];
char buf[1000];
set<char> sn;
vector<int> vn;

int bandwidth() {
	int band = 0, pos1, pos2;
	for (int i = 0; i < n; i++) {
		pos1 = i;
		for (int j = 0; j < g[c[i]].size(); j++) {
			for (int k = 0; k < n; k++) 
				if (c[k] == g[c[i]][j]) {pos2 = k; break;}
			int sum = fabs(pos1-pos2);
			if (band < sum) band = sum;
		}
	}
	return band;
}


void dfs(int cur) {
//	cnt++;
	if (cur == n) {
		int bw1 = bandwidth();
		if (bw1 < bw) {
			bw = bw1;
			for (int i = 0; i < n; i++) ans[i] = c[i];
		}
	}
	else for (int i = 0; i < n; i++) {
		if (!vis[vn[i]][0]) {
			int ok = 1;
			c[cur] = vn[i];
			if (g[vn[i]].size()-vis[vn[i]][1] > bw) {ok = 0; goto prune;}
			for (int j = 0; j < g[vn[i]].size(); j++)
				for (int k = 0; k < cur; k++)
					if (c[k] == g[vn[i]][j]) {
						int dis = fabs(cur-k);
						if (dis >= bw) {ok = 0; goto prune;}
					}
prune:
			if (ok) {
				for (int j = 0; j < g[vn[i]].size(); j++)
					vis[g[vn[i]][j]][1]++;
				vis[vn[i]][0] = 1;
				dfs(cur+1);
				vis[vn[i]][0] = 0;
				for (int j = 0; j < g[vn[i]].size(); j++)
					vis[g[vn[i]][j]][1]--;
			}
		}
	}
}

int main() {
	while (fgets(buf, 1000, stdin) && buf[0] != '#') {
		for (int i = 0; i < 26; i++) {g[i].clear(); sg[i].clear();}
		sn.clear(); vn.clear();
		memset(vis, 0, sizeof(vis));
		memset(ans, 0, sizeof(ans));
		memset(c, 0, sizeof(c));
		bw = 10; int pos1, pos2; char ch1, ch2;
		for (int i = 0;;) {
			ch1 = buf[i]; i += 2;
			if (!sn.count(ch1)) {sn.insert(ch1); vn.push_back(ch1-'A');}
			pos1 = ch1 - 'A';
			do {
				if (buf[i] == '\n') goto next;
				ch2 = buf[i]; 
				if (!sn.count(ch2)) {sn.insert(ch2); vn.push_back(ch2-'A');}
				pos2 = ch2 - 'A';
				if (pos2 > n) n = pos2;
				if (!sg[pos1].count(pos2)) {
					sg[pos1].insert(pos2);
					g[pos1].push_back(pos2);
				}
				if (!sg[pos2].count(pos1)) {
					sg[pos2].insert(pos1);
					g[pos2].push_back(pos1);
				}
				i++;
			} while (buf[i] != ';');
			i++;
		}
next:
		sort(vn.begin(), vn.end());
		n = sn.size();
//		cnt = 0;
		dfs(0);
		for (int i = 0; i < n; i++)
			printf("%c ", ans[i] + 'A');
		printf("-> %d\n", bw);
//		printf("%d\n", cnt);
	}
	return 0;
}
