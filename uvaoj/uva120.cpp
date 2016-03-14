#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
const int maxn = 30;
string buf;
int panc[30], spanc[30], pos, cnt;

bool cmp(const int a, const int b) {
	return a > b;
}

inline void flip(int p) {
	int e = cnt - 1;
	while (p < e)
		swap(panc[p++], panc[e--]);
}

void init() {
	cout << buf << endl;
	memset(panc, 0, sizeof(panc));
	memset(spanc, 0, sizeof(spanc));
	stringstream ss(buf);
	int dia;
	cnt = 0;
	while (ss >> dia) panc[cnt++] = dia;
	// printf("cnt is %d\n", cnt);
	flip(0);
	memcpy(spanc, panc, sizeof(panc));
	sort(spanc, spanc+cnt, cmp);
	// for (int i = 0; i < cnt; i++) printf("%d/", spanc[i]);
	// printf("\n");
	pos = 0;
}

inline int issorted() {
	if (memcmp(spanc, panc, sizeof(panc)) == 0)
		return 1;
	else
		return 0;
}

int solve() {
	if (issorted()) {
		printf("0\n");
		return 1;
	}
	if (panc[cnt-1] == spanc[pos]) {
		flip(pos);
		printf("%d ", pos+1);
	}
	else {
		int p = cnt - 1;
		while (panc[p] != spanc[pos]) p--;
		flip(p);
		printf("%d ", p+1);
		flip(pos);
		printf("%d ", pos+1);
	}
	pos++;
	if (solve()) return 1;
}

int main() {
	while (getline(cin, buf)) {
		if (buf[0] == EOF) break;
		init();
		solve();
	}
	return 0;
}
