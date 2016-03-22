#include <cstdio>
#include <set>
using namespace std;

const int maxn = 1024 + 5;
int n, s[maxn], f[maxn], o[maxn], cnt;
char team[maxn][maxn];
set<int> ss, sf, so;
const int bin[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

void init() {
	for (int i = 1; i <= n; i++)
		scanf("%s", team[i]+1);
	ss.clear(); sf.clear(); so.clear();
	for (int i = 2; i <= n; i++)
		if (team[i][1] == '1') {
			ss.insert(i);
		}
	for (int i = 2; i <= n; i++)
		if (team[i][1] == '0') {
			int ok = 1;
			for (int j = 2; j <= n; j++) {
				if (j == i) continue;
				if (team[i][j] == '1' && ss.count(j)) {
					sf.insert(i);
					ok = 0;
					break;
				}
			}
			if (ok) so.insert(i);
		}
	// printf("%d %d %d\n", ss.size(), sf.size(), so.size());
	cnt = 1;
	while (bin[++cnt] != n) ;
}

void solve() {
	int scnt = 0, fcnt = 0, ocnt = 0;
	set<int>::iterator its, itf;
	for (its = ss.begin(); its != ss.end(); ) {
		int find = 0;
		for (itf = sf.begin(); itf != sf.end(); itf++) {
			if (team[*itf][*its] != '1') continue;
			printf("%d %d\n", *itf, *its);
			f[fcnt++] = *itf;
			ss.erase(its);
			sf.erase(itf);
			find = 1;
			break;
		}
		if (!find) its++;
	}

	if (!so.empty()) {
		its = so.begin();
		printf("1 %d\n", *its);
		so.erase(its);
	}
	else {
		its = sf.begin();
		printf("1 %d\n", *its);
		sf.erase(its);
	}

	for (its = ss.begin(); its != ss.end(); ) {
		int find = 0;
		for (itf = ss.begin(); itf != ss.end(); itf++) {
			if (team[*itf][*its] != '1') continue;
			printf("%d %d\n", *itf, *its);
			s[scnt++] = *itf;
			ss.erase(its);
			ss.erase(itf);
			find = 1;
			break;
		}
		if (!find) its++;
	}

	for (its = ss.begin(); its != ss.end(); its++) so.insert(*its);
	for (its = sf.begin(); its != sf.end(); its++) so.insert(*its);

	ss.clear(); sf.clear();
	for (int i = 0; i < scnt; i++) ss.insert(s[i]);
	for (int i = 0; i < fcnt; i++) sf.insert(f[i]);

	for (its = so.begin(); its != so.end(); ) {
		int find = 0;
		for (itf = so.begin(); itf != so.end(); itf++) {
			if (*its == *itf || team[*itf][*its] != '1') continue;
			printf("%d %d\n", *itf, *its);
			o[ocnt++] = *itf;
			so.erase(its);
			so.erase(itf);
			find = 1;
			break;
		}
		if (!find) its++;
	}

	so.clear();
	for (int i = 0; i < ocnt; i++) so.insert(o[i]);
}

int main() {
	while (scanf("%d", &n) != EOF) {
		init();
		for (int i = 0; i < cnt; i++) solve();
	}
	return 0;
}
