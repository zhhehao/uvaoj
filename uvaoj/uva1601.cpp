#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <queue>
using namespace std;
const int maxn = 256 + 5;
struct Node {
	int s[3];
};
int dx[] = {-1, 1, 0, 0, 0};
int dy[] = {0, 0, -1, 1, 0};
int g[3][2], w, h, n, ghost[26][2];
vector<int> nmap[maxn];
set<int> snmap[maxn];
int vis[150][150][150];

int dbfs() {
	Node n1, n2; 
	n1.s[0] = g[0][0]; n2.s[0] = g[0][1];
	n1.s[1] = g[1][0]; n2.s[1] = g[1][1];
	n1.s[2] = g[2][0]; n2.s[2] = g[2][1];
	memset(vis, 0, sizeof(vis));
	vis[n1.s[0]][n1.s[1]][n1.s[2]] = 1;
	vis[n2.s[0]][n2.s[1]][n2.s[2]] = -1;
	queue<Node> qp, qn;
	while (!qp.empty()) qp.pop(); qp.push(n1);
	while (!qn.empty()) qn.pop(); qn.push(n2);
	while (!qp.empty() || !qn.empty()) {
		if (qp.size() <= qn.size()) {
			Node n3 = qp.front(); qp.pop();
			int pos1 = n3.s[0], pos2 = n3.s[1], pos3 = n3.s[2];
			for (int i = 0; i < nmap[pos1].size(); i++)
				for (int j = 0; j < nmap[pos2].size(); j++)
					for(int k = 0; k < nmap[pos3].size(); k++) {
						int p1 = nmap[pos1][i], p2 = nmap[pos2][j], p3 = nmap[pos3][k];
						if (p1 == p2 || p1 == p3 || p2 == p3) continue;
						if (p1 == pos2 && p2 == pos1) continue;
						if (p1 == pos3 && p3 == pos1) continue;
						if (p2 == pos3 && p3 == pos2) continue;
						Node n4 = n3;
						n4.s[0] = p1;
						n4.s[1] = p2;
						n4.s[2] = p3;
						if (vis[p1][p2][p3] < 0)
							return vis[pos1][pos2][pos3] + (-1 * vis[p1][p2][p3])-1;
						if (vis[p1][p2][p3]) continue;
						vis[p1][p2][p3] = vis[pos1][pos2][pos3]+1;
						qp.push(n4);
					}
		}
		else {
			Node n13 = qn.front(); qn.pop();
			int pos1 = n13.s[0], pos2 = n13.s[1], pos3 = n13.s[2];
			for (int i = 0; i < nmap[pos1].size(); i++)
				for (int j = 0; j < nmap[pos2].size(); j++)
					for(int k = 0; k < nmap[pos3].size(); k++) {
						int p1 = nmap[pos1][i], p2 = nmap[pos2][j], p3 = nmap[pos3][k];
						if (p1 == p2 || p1 == p3 || p2 == p3) continue;
						if (p1 == pos2 && p2 == pos1) continue;
						if (p1 == pos3 && p3 == pos1) continue;
						if (p2 == pos3 && p3 == pos2) continue;
						Node n14 = n13;
						n14.s[0] = p1;
						n14.s[1] = p2;
						n14.s[2] = p3;
						if (vis[p1][p2][p3] > 0)
							return (-1*vis[pos1][pos2][pos3]) + vis[p1][p2][p3]-1;
						if (vis[p1][p2][p3] == 0) {
							vis[p1][p2][p3] = vis[pos1][pos2][pos3]-1;
							qn.push(n14);
						}
					}
		}
	}
	return -1;
}

char buf[100];

int main() {
	while (scanf("%d%d%d", &w, &h, &n) == 3 && w) {
		fgets(buf, 100, stdin);
		int mp[h][w]; memset(mp, -1, sizeof(mp));
		memset(g, 0, sizeof(g));
		memset(ghost, -1, sizeof(ghost));
		for (int i = 0; i < maxn; i++) {nmap[i].clear(); snmap[i].clear();}
		int pos = 0;
		for (int i = 0; i < h; i++) {
			fgets(buf, 100, stdin);
//			printf("%s\n", buf);
			for (int j = 0; j < w; j++) {
				if (buf[j] == '#') continue;
				mp[i][j] = pos;
				if (buf[j] >= 'a' && buf[j] <= 'z') ghost[buf[j]-'a'][0] = pos;
				else if (buf[j] >= 'A' && buf[j] <= 'Z') ghost[buf[j]-'A'][1] = pos;
				pos++;
			}
		}
		int gcnt = 0;
		for (int i = 0; i < 26; i++)
			if (ghost[i][0] >= 0) memcpy(g[gcnt++], ghost[i], sizeof(ghost[i]));
//		for (int i = 0; i < h; i++) {
//			for (int j = 0; j < w; j++)
//				printf("%3d", mp[i][j]);
//			printf("\n");
//		}
		for (int i = 1; i < h-1; i++)
			for (int j = 1; j < w-1; j++) {
				if (mp[i][j] < 0) continue;
//				nmap[mp[i][j]].push_back(mp[i][j]);
				for (int k = 0; k < 5; k++) {
					int newx = i + dx[k];
					int newy = j + dy[k];
					if (mp[newx][newy] >= 0 && !snmap[mp[i][j]].count(mp[newx][newy])) {
						snmap[mp[i][j]].insert(mp[newx][newy]);
						nmap[mp[i][j]].push_back(mp[newx][newy]);
					}
				}
			}
//		printf("pos is %d\n", pos);
		if (n == 1) {
			int pos1 = pos, pos2 = pos + 1; 
			g[1][0] = g[1][1] = pos;
			g[2][0] = g[2][1] = pos+1;
			nmap[pos].push_back(pos);
			nmap[pos+1].push_back(pos+1);
		}
		else if (n == 2) {
			g[2][0] = g[2][1] = pos;
			nmap[pos].push_back(pos);
		}
		int ans = dbfs();
		printf("%d\n", ans);	
	}
	return 0;
}
