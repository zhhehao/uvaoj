#include <cstdio>
#include <map>
using namespace std;

const int maxn = 200000 + 10;
int n, left[maxn], right[maxn], seq[maxn];

map<int, int> m;

bool nbor(int L0, int R0) {
	if (L0 >= R0) return true;
	int L = L0, R = R0;
	while (L <= R) {
		if ((left[L] < L0) && (right[L] > R0)) {
			return nbor(L0, L-1) && nbor(L+1, R0);
		}
		if ((left[R] < L0) && (right[R] > R0)) {
			return nbor(L0, R-1) && nbor(R+1, R0);
		}
		L++; R--;
	}
	return false;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		m.clear();
		for (int i = 1; i <= n; i++) {
			scanf("%d", &seq[i]);
			if (m.count(seq[i])) {
				right[m[seq[i]]] = i;
				left[i] = m[seq[i]];
				right[i] = n+1;
				m[seq[i]] = i;
			}
			else {
				left[i] = -1;
				right[i] = n+1;
				m[seq[i]] = i;
			}
		}
		if (nbor(1, n)) printf("non-boring\n");
		else printf("boring\n");
	}
	return 0;
}
