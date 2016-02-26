#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn = 6;
struct Tree{
	double L, R;	
	Tree(): L(0), R(0) {}
};

double r;
int vis[1<<maxn], n;
//int cnt;
vector<Tree> tree;
vector<double> w, ans;

void dfs(int cur) {
//	cnt++;
	if (cur == 1) {
		int pos = w.size() - 1;
		double sum = tree[pos].L + tree[pos].R;
		if (sum < r) 
			ans.push_back(sum);
	}
	else {
		double w1, w2; int p1, p2;
		for (int i = 0; i < w.size(); i++)
			if (!vis[i]) {
				p1 = i; vis[p1] = 1;
				for (int j = 0; j < w.size(); j++) {
					if (!vis[j]) {
						p2 = j; vis[p2] = 1;
						w1 = w[p1]; w2 = w[p2];
						double d1, d2;
						d1 = w2 / (w1+w2);
						d2 = w1 / (w1+w2);
						Tree t;
						t.L = max(tree[p1].L+d1, tree[p2].L-d2);
						t.R = max(tree[p2].R+d2, tree[p1].R-d1);
						int pos;
						if (t.L+t.R < r) {
							tree.push_back(t);
							w.push_back(w1+w2);
							pos = tree.size() - 1;
							dfs(cur-1);
							w.pop_back();
							tree.pop_back();
							vis[pos] = 0;
						}
						t.L = max(tree[p2].L+d2, tree[p1].L-d1);
						t.R = max(tree[p1].R+d1, tree[p2].R-d2);
						if (t.L+t.R < r) {
							tree.push_back(t);
							w.push_back(w1+w2);
							pos = tree.size() - 1;
							dfs(cur-1);
							w.pop_back();
							tree.pop_back();
							vis[pos] = 0;
						}
						vis[p2] = 0;
					}
				}
				vis[p1] = 0;
			}
	}
}

int main() {
	int T; scanf("%d", &T) == 1;
	while (T--) {
		scanf("%lf%d", &r, &n) == 2;
		w.clear(); tree.clear(); double weight;
		for (int i = 0; i < n; i++) {
			scanf("%lf", &weight) == 1;
			w.push_back(weight);
			tree.push_back(Tree());
		}
		ans.clear();
		memset(vis, 0, sizeof(vis));
//		cnt = 0;
		dfs(n);
		double result = -1;
		for (int i = 0; i < ans.size(); i++) {
			result = max(result, ans[i]);
		}
		printf("%.10lf\n", result);
//		printf("%d\n", cnt);
	}
	return 0;
}
