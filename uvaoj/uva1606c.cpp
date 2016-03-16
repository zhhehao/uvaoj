#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn = 1000 + 5;

struct Point{
	int x, y;
	double rad;
	bool operator < (const Point& a) const {
		return rad < a.rad;
	}
};
Point point[maxn], ps[maxn];

bool in(Point& a, Point& b) {
	return a.x * b.y - a.y * b.x >= 0;
}

int n, color[maxn];

void init() {
	for (int i = 0; i < n; i++)
		scanf("%d%d%d", &point[i].x, &point[i].y, &color[i]);
}

void solve() {
	if (n <= 2) {
		printf("2\n");
		return;
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int k = 0;
		for (int j = 0; j < n; j++) {
			if (j == i) continue;
			ps[k].x = point[j].x - point[i].x;
			ps[k].y = point[j].y - point[i].y;
			if (color[j]) {
				ps[k].x = -ps[k].x;
				ps[k].y = -ps[k].y;
			}
			ps[k].rad = atan2(ps[k].y, ps[k].x);
			k++;
		}
		sort(ps, ps+k);
		int f = 0, b = 0, cnt = 2;
		while (f < k) {
			if (f == b) {
				b = (b+1)%k;
				cnt++;
			}
			while (b != f && in(ps[f], ps[b])) {
				b = (b+1)%k;
				cnt++;
			}
			cnt--;
			f++;
			ans = max(ans, cnt);
		}
	}
	printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n) && n) {
		init();
		solve();
	}
	return 0;
}
