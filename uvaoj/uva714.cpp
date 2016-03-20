#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 500 + 5;
typedef long long LL;
int m, k, p[maxn];
LL s[maxn], x;

void init() {
	scanf("%d%d", &m, &k);
	s[0] = 0;
	for (int i = 1; i <= m; i++) {
		scanf("%d", &p[i]);
		s[i] = s[i-1] + p[i];
	}
	// for (int i = 0; i < m; i++) printf("%d %d\n", p[i], s[i]);
	x = s[m];
}

int Page(LL a) {
	LL L = 0, R = 0;
	int cnt = 1;
	if (s[1] > a) return false;
	while (R <= m) {
		if (s[R]-s[L] > a) {
			L = R-1; cnt++;
			if (cnt == k) {
				if (s[m]-s[L] > a) return false;
				else return true;
			}
		}
		else if (s[R]-s[L] == a) {
			L = R; R++; cnt++;
			if (cnt == k) {
				if (s[m]-s[L] > a) return false;
				else return true;
			}
		}
		else
			R++;
	}
	return true;
}

void findx() {
	LL L = 0, R = x;
	while (L < R) {
		x = L + (R-L)/2;
		if (Page(x)) R = x;
		else L = x + 1;
	}
	x = R;
	// printf("x is %lld\n", x);
}

void pr() {
	vector<int> v; v.clear();
	LL sum = 0;
	int cnt = k-1;
	for (int i = m; i >= 1; i--) {
		sum += p[i];
		if (sum > x || cnt == i) {
			v.push_back(-1);
			sum = p[i];
			cnt--;
		}
		v.push_back(p[i]);
	}
	int size = v.size() - 1;
	for (int i = size; i >= 0; i--) {
		if (i != size) printf(" ");
		if (v[i] == -1)
			printf("%c", '/');
		else
			printf("%d", v[i]);
	}
	printf("\n");
}

int main() {
	int N; scanf("%d", &N);
	while (N--) {
		init();
		if (k == 1) {
			for (int i = 1; i <= m; i++) {
				if (i != 1) printf(" ");
				printf("%d", p[i]);
			}
			printf("\n");
			continue;
		}
		findx();
		pr();
	}
	return 0;
}
