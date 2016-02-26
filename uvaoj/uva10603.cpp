#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int maxn = 200 + 5;
int vis[maxn][maxn], a, b, c, d, vinit[3];

struct Node {
	int v[3], dist;
	bool operator < (const Node& a) const {
		return dist > a.dist;
	}
};

vector<Node> node;

int bfs() {
	node.clear();
	Node no; no.v[0] = 0; no.v[1] = 0; no.v[2] = c; no.dist = 0;
	node.push_back(no);
	if (c == d) return 0;
	memset(vis, 0, sizeof(vis));
	priority_queue<Node> q; while (!q.empty()) q.pop(); 
	q.push(no);
	vinit[0] = a; vinit[1] = b; vinit[2] = c;
	while (!q.empty()) {
		Node n1 = q.top(); q.pop();
		if (n1.dist) {
			if (n1.v[2] == d || n1.v[0] == d || n1.v[1] == d) return vis[n1.v[0]][n1.v[1]];
//			if (!n1.v[0] && !n1.v[1]) return -1;
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (i != j) {
					if (n1.v[i] && (n1.v[j] < vinit[j])) {
						Node n2;
						memcpy(&n2, &n1, sizeof(n1));
						if (vinit[j] - n1.v[j] >= n1.v[i]) {
							n2.v[j] += n1.v[i];
							n2.dist =  n1.dist + n1.v[i];
							n2.v[i] = 0;
						}
						else if (vinit[j] - n1.v[j] < n1.v[i]) {
							n2.dist = n1.dist + vinit[j]-n1.v[j];
							n2.v[j] = vinit[j];
							n2.v[i] -= (vinit[j]-n1.v[j]);
						}
						if (!n2.v[0] && !n2.v[1]) continue;
						if (!vis[n2.v[0]][n2.v[1]]) {
							node.push_back(n2);
							vis[n2.v[0]][n2.v[1]] = node.size() - 1;
							q.push(n2);
						}
					} 
				}

	}
	return -1;
}

int main() {
	int n; scanf("%d", &n) == 1;
	while (n--) {
		scanf("%d%d%d%d", &a, &b, &c, &d) == 4;
		int ans = bfs();
//		printf("ans is %d\n", ans);
		if (ans < 0) {
//			printf("node's size is %d\n", node.size());
			int minds = d, res = 0;
			for (int i = 0; i < node.size(); i++) {
				int ds1, ds2, ds3;
				ds1 = d - node[i].v[0];
				ds2 = d - node[i].v[1];
				ds3 = d - node[i].v[2];
				if (ds1 > 0 && ds1 < minds) {minds = ds1; res = i;}
				if (ds2 > 0 && ds2 < minds) {minds = ds2; res = i;}
				if (ds3 > 0 && ds3 < minds) {minds = ds3; res = i;}
			}
			printf("%d %d\n", node[res].dist, d-minds);
			continue;
		}
		printf("%d %d\n", node[ans].dist, d);
	}
	return 0;
}
