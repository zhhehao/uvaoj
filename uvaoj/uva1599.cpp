#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
struct Road {int c, r1, r2;};
struct Room {int dis, ci, rfa;vector<int> vr;};
Road road[200010]; Room room[100010];

void bfs(int r) {
	queue<int> q; q.push(r);
	while (!q.empty()) {
		int id = q.front(); q.pop();
		for (int i = 0; i < room[id].vr.size() ; i++) {
			int rid = room[id].vr[i];
			int ro1 = road[rid].r1;
			int ro2 = road[rid].r2;
			int rc = (ro1 == id) ? ro2 : ro1;
			if (room[rc].dis < 0) {
				room[rc].dis = room[id].dis + 1;
				room[rc].ci = rid;
				room[rc].rfa = id;
				q.push(rc);
			}
			else if (room[rc].dis == room[id].dis + 1) {
				if (road[room[rc].ci].c > road[rid].c) {
					room[rc].ci = rid;
					room[rc].rfa = id;
				}
				else if (road[room[rc].ci].c == road[rid].c) {
					if (road[room[rc].ci].c > road[rid].c){
						room[rc].ci = rid;
						room[rc].rfa = id;
					}
					else if (road[room[rc].ci].c == road[rid].c) {
						int rfa1 = room[rc].rfa;
						int rfa2 = id;
						for (;;) {
							if (rfa1 == rfa2) break;
							if (road[room[rfa1].ci].c == road[room[rfa2].ci].c) {
								rfa1 = room[rfa1].rfa; rfa2 = room[rfa2].rfa;
								continue;
							}
							if (road[room[rfa1].ci].c > road[room[rfa2].ci].c) {
								room[rc].ci = rid;
								room[rc].rfa = id;
								break;
							}
							else
								break;
						}
					}
				}
			}
		}
	}
}

int main() {
	int n, m;
	while (scanf("%d", &n) != EOF) {
		scanf("%d", &m) == 1; int r1, r2, r3;
		for (int i = 1; i <= n; i++)
			room[i].vr.clear();
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &r1, &r2, &r3) == 3;
			road[i].c = r3;	road[i].r1 = r1; road[i].r2 = r2;
			room[r1].dis = -1; room[r1].ci = -1;
			room[r1].rfa = -1; room[r1].vr.push_back(i);
			room[r2].dis = -1; room[r2].ci = -1;
			room[r2].rfa = -1;
			room[r2].vr.push_back(i);
		}
		room[n].dis = 0;
		bfs(n);	
//		printf("%d %d\n", room[1].dis, room[1].csum);
		printf("%d\n", room[1].dis - room[n].dis);
		int dis = room[1].dis, rnum = 1;
		while (dis > 0) {
			dis = room[rnum].dis;
			printf("%d", road[room[rnum].ci].c);
			if (dis > 1) printf(" ");
			rnum = room[rnum].rfa; dis--;
		}
		printf("\n");
	}
	return 0;
}
