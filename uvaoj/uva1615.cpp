#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#define LL long long
LL l, d, n;

struct Point{
	LL x, y, L, R;
	Point(){};
	Point(LL a, LL b):x(a), y(b){
		LL des = sqrt(d*d-y*y);
		L = max((LL)0, (LL)ceil(x-des));
		R = min((LL)l, (LL)floor(x+des));
	}
	bool operator < (const Point& b) const {
		return R < b.R;
	}
};

int main() {
	while (scanf("%lld%lld%lld", &l, &d, &n) != EOF) {
		vector<Point> p;
		LL a, b;
		for (int i = 0; i < n; i++) {
			scanf("%lld%lld", &a, &b);
			p.push_back(Point(a, b));
		}
		sort(p.begin(), p.end());

		LL prev = p[0].R, ans = 1;
		for (int i = 0; i < n; i++) {
			if (p[i].L > prev) {
				ans++;
				prev = p[i].R;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
