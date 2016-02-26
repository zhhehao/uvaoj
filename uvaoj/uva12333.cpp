#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
using namespace std;

const int maxn = 100000 + 10;

char fi[maxn][42];
int fib[2][maxn];

int main() {
	memset(fi, '\0', sizeof(fi));
	memset(fib, 0, sizeof(fib));
	fi[0][0] = '1';
	fi[1][0] = '1';
	fib[0][0] = 1;
	fib[1][0] = 1;
	int s = 0, e = 1;
	int p, q, r, count;
	for (int i = 2; i < 100000; ++i) {
		p = i%2;
		q = (i+1)%2;
		for (int j = s; j < e; ++j) 
			fib[p][j] = fib[p][j] + fib[q][j];
		for (int j = s; j < e; ++j) {
			if (fib[p][j] >= 10) {
				fib[p][j+1] += 1;
				fib[p][j] -= 10;
			}
		}
		if (fib[p][e]) e++;
		if (e - s > 50) s++;
		r = e - 1;
		count = 0;
		while (r >= 0 && count < 40) {
			fi[i][count++] = fib[p][r--] + '0';
		}
	}
	int t, rev;
	int kase = 1;
	rev = scanf("%d", &t);
	string str;
	getline(cin, str);
	while (t--) {
		getline(cin, str);
		int sn = -1;
		for (int i = 0; i < 100000; ++i) {
			bool found = true;
			for (int j = 0; j < str.size(); ++j) {
				if (fi[i][j] != str[j]) {
					found = false;
					break;
				}
			}
			if (found) {
				sn = i;
				break;
			}
		}
		printf("Case #%d: %d\n", kase++, sn);
	}
	return 0;
}
