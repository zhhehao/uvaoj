#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const double EPS = 1e-6;
struct Op {
	int x, y, r, isac, yr;
};

double yin, yout;

bool dfs(Op& op, vector<Op>& v) {
//	printf("dfs\n");
	double yi, yo;
	op.isac = 1;
	if (op.y - op.r <= 0) return false;
	if (op.x - op.r == 0) if (op.y < yin) yin = op.y;
	if (op.x + op.r == 1000) if (op.y < yout) yout = op.y;
	if (op.x - op.r < 0) {
		yi = op.y - sqrt(op.r*op.r - op.x*op.x) + EPS;
//		printf("%.2f %.2f\n", yin, yi);
		if (yi < yin) yin = yi;
	}
	if (op.x + op.r > 1000) {
		yo = op.y - sqrt(op.r*op.r - (1000-op.x)*(1000-op.x))+ EPS;
//		printf("%.2f %.2f\n", yout, yo);
		if (yo < yout) yout = yo;
	}
	for (int i = 0; i < v.size(); i++) {
		if (v[i].isac == 1) continue;
		int dis = (v[i].x-op.x)*(v[i].x-op.x)+(v[i].y-op.y)*(v[i].y-op.y);
//		printf("%d\n", dis);
		if (dis <= (v[i].r+op.r)*(v[i].r+op.r)) {
			if (!dfs(v[i], v)) return false;
		}
	}
	return true;
}

bool cmp(Op& a, Op&b) {
	if (a.yr == b.yr)
		return a.x < b.x;
	return 
		a.yr > b.yr;
}

int main() {
	int n;
	while (scanf("%d", &n) != EOF) {
		vector<Op> v; v.clear(); int x, y, r;
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &x, &y, &r) == 3;
			Op op; op.x = x; op.y = y; op.r = r; op.yr = y + r; op.isac = 0;
			v.push_back(op);
		}
		sort(v.begin(), v.end(), cmp);
//		printf("%d\n", v[0].yr);
		if (v[0].yr < 1000) {
			printf("0.00 1000.00 1000.00 1000.00\n");	
			continue;
		}
		bool isim = false; yin = yout = 1000.0; int ans;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].yr < 1000) break;
			if (v[i].isac == 1) continue;
			if (!dfs(v[i], v)) {isim = true; break;}
		}
		if (isim) {
			printf("IMPOSSIBLE\n"); continue;
		}
		printf("0.00 %.2f 1000.00 %.2f\n", yin, yout);
	}
	return 0;
}
