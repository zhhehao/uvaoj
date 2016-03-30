#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 20000;

struct Player{
	int s[8];
};

Player player[maxn];
int n, rank[maxn];

int main() {
	int kase = 0;
	while (scanf("%d", &n) == 1 && n) {
		double s1, s2, s3; int t[3];
		for (int i = 1; i <= n; i++) {
			scanf("%lf%lf%lf", &s1, &s2, &s3);
			t[0] = (int)(round(s1 * 100.0));
			t[1] = (int)(round(s2 * 100.0));
			t[2] = (int)(round(s3 * 100.0));
			for (int j = 0; j < 8; j++) {
				player[i].s[j] = 0;
				for (int k = 0; k < 3; k++) {
					if (j & (1<<k))
						player[i].s[j] += t[k];
				}
			}
			sort(player[i].s, player[i].s+8);
		}
		for (int i = 1; i <= n; i++) scanf("%d", &rank[i]);

		printf("Case %d: ", ++kase);
		int ok = 1;
		int pid = rank[1], psc = player[rank[1]].s[7];
		for (int i = 2; i <= n; i++) {
			int flag = 0;
			for (int j = 7; j >= 0; j--) {
				if (player[rank[i]].s[j] == psc && rank[i] > pid) {
					flag = 1;
					pid = rank[i];
					break;
				}
				if (player[rank[i]].s[j] < psc) {
					flag = 1;
					psc = player[rank[i]].s[j];
					pid = rank[i];
					break;
				}
			}
			if (!flag) {ok = 0; break;}
		}
		if (ok) {
			printf("%.2f\n", psc / 100.0);
		}
		else
			printf("No solution\n");
	}
	return 0;
}
