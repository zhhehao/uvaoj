#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
using namespace std;
const int maxn = 100 + 5;
struct PTi {int p, n;};
int main() {
	int np, nt, nf, kase = 1;
	while (scanf("%d", &np) == 1 && np != 0) {
		int p[maxn], en[maxn], be[maxn];
		vector<int> to[maxn];
		vector<PTi> ti[maxn];
		memset(p, 0, sizeof(p));// 数组初始化
		memset(be, 0, sizeof(be));
		for (int i = 1; i <= np; i++) {scanf("%d", &p[i]) == 1; be[i] = p[i];} // 读入np
		scanf("%d", &nt) == 1; int io; // 读入 nt
		for (int i = 0; i < maxn; i++) {to[i].clear(); ti[i].clear();} // vector初始化
		for (int i = 1; i <= nt; i++) { // 初始化ti to
			map<int, int> mi; mi.clear();
			while (scanf("%d", &io) == 1 && io != 0)
				if (io < 0) {
					int pp = -1 * io; PTi pti;
					if (!mi.count(pp)) { 
						pti.p = pp; pti.n = 1;
						ti[i].push_back(pti);
						mi[pp] = ti[i].size() - 1;
					}
					else 
						ti[i][mi[pp]].n++;
				}
				else to[i].push_back(io);
		}
		scanf("%d", &nf) == 1; // 读入nf
		printf("Case %d:", kase++);
		int fire = 0;
		for (int i = 1; i <= nt; i++) {
			bool ent = true;
			for (int j = 0; j < ti[i].size(); j++) 
				if (p[ti[i][j].p] < ti[i][j].n) {ent = false; break;}
			if (ent) {
				for (int j = 0; j < ti[i].size(); j++)
					p[ti[i][j].p] -= ti[i][j].n;
				for (int k = 0; k < to[i].size(); k++)
					p[to[i][k]]++;
				i = 0; fire++;
				if (fire >= nf) break;
			}
			else 
				continue;
		}
		if (fire >= nf) printf(" still live after %d transitions\n", nf);
		else  printf(" dead after %d transitions\n", fire);
		// 输出剩余的token数目
		printf("Places with tokens:");
		for (int i = 1; i <= np; i++)
			if (p[i] > 0) printf(" %d (%d)", i, p[i]);
		printf("\n\n");
	}
	return 0;
}
