#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;

struct Seg{
	int L, R;
	bool operator < (const Seg& b) const {
		if (R == b.R)
			return L < b.L;
		else
			return R < b.R;
	}
} s[maxn];

int n;

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) scanf("%d%d", &s[i].L, &s[i].R);
		sort(s, s+n);
		int ans = 0, end = n-1;
		for (int i = 0; i < end; i++) {
			if (s[i].R != s[i+1].R) {
				if (s[i].R < s[i+1].L)
					ans++;
				else
					s[i+1].R = s[i].R+1;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

