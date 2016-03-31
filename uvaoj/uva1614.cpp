#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 100000 + 10;
int n, mark[maxn];

struct Num{
	int i, v;
	bool operator < (const Num& b) const {
		return v > b.v;
	}
} s[maxn];

int main() {
	while (scanf("%d", &n) != EOF) {
		int buf; long long sum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d", &buf);
			sum += buf;
			s[i].i = i;
			s[i].v = buf;
		}
		sort(s, s+n);
		memset(mark, -1, sizeof(mark));

		if (sum%2 != 0)
			printf("No\n");
		else {
			sum /= 2;
			for (int i = 0; i < n; i++) {
				if (sum >= s[i].v) {
					sum -= s[i].v;
					mark[s[i].i] = 1;
				}
				else if (sum == 0) break;
			}
			printf("Yes\n");
			for (int i = 0; i < n; i++) {
				if (i != 0) printf(" ");
				printf("%d", mark[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
