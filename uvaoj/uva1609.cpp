#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 1024 + 5;
char team[maxn][maxn];
int n, cnt;
const int bin[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
vector<int> win, lose;

void init() {
	cnt = 1; while (bin[++cnt] != n) ;
	for (int i = 1; i <= n; i++)scanf("%s", team[i]+1);
	win.clear(); lose.clear();

	for (int i = 2; i <= n; i++)
		if (team[1][i] == '1') win.push_back(i);
		else lose.push_back(i);
}

void solve() {
	vector<int> win2, lose2, final;

	for (int i = 0; i < lose.size(); i++) {
		int ok = 0;
		for (int j = 0; j < win.size(); j++) {
			if (win[j] > 0 && team[win[j]][lose[i]] == '1') {
				printf("%d %d\n", win[j], lose[i]);
				win2.push_back(win[j]);
				win[j] = 0;
				ok = 1;
				break;
			}
		}
		if (!ok) final.push_back(lose[i]);
	}

	int first = 1;
	for (int i = 0; i < win.size(); i++) {
		if (win[i] > 0) {
			if (first) {
				printf("1 %d\n", win[i]);
				first = 0;
			}
			else final.push_back(win[i]);
		}
	}

	for (int i = 0; i < final.size(); i += 2) {
		printf("%d %d\n", final[i], final[i+1]);
		int keep;
		if (team[final[i]][final[i+1]] == '1') keep = final[i];
		else keep = final[i+1];
		if (team[1][keep] == '1') win2.push_back(keep);
		else lose2.push_back(keep);
	}
	win = win2;
	lose = lose2;
}

int main() {
	// freopen("data.in", "r", stdin);
	// freopen("data.out", "w", stdout);
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 0; i < cnt; i++) solve();
	}
	return 0;
}
